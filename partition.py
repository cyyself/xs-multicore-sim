#!/usr/bin/env python3

import json
from pathlib import Path
import os
import argparse
from sv_util import *

def read_hierachy(filename: Path):
    with open(filename, 'r') as f:
        return json.load(f)

def find_module_path_in_hierachy(hier, module_name: str,
                                 current_inst_path: list[str] = [],
                                 current_module_path: list[str] = []):
    current_inst_path = current_inst_path + [hier['instance_name']]
    current_module_path = current_module_path + [hier['module_name']]
    if hier['module_name'] == module_name:
        # inst_path should be first element to be sorted
        return [[current_inst_path, current_module_path]]
    else:
        res = []
        for child in hier['instances']:
            path = find_module_path_in_hierachy(child, module_name,
                                                current_inst_path,
                                                current_module_path)
            res += path
        return res

class module_def:
    def __init__(self, mf: module_file, count: int = 0):
        self.mf = mf
        self.count = count
        # count is how many target module instance in this module
        # we should do dfs and add each instance which has path to target to the count

def write_to_file(filename: Path, content: str):
    if os.path.exists(filename):
        with open(filename, 'r') as f:
            if f.read() == content:
                return
    with open(filename, 'w') as f:
        f.write(content)

def do_partition(vsrc_path: Path, partitioned_path: Path, target_module: str, io_format: str = '{}_{}_', header_path: str = '', mask_io: list[str] = []):
    # read modules
    modules: dict[module_def] = dict()
    for file in os.listdir(vsrc_path):
        if file.endswith(".sv"):
            with open(vsrc_path / Path(file), "r") as f:
                lines = [x.rstrip() for x in f.readlines()]
                modules[file[:-3]] = module_def(module_file.from_list_str(lines))
                assert(modules[file[:-3]].mf is not None)
                outstr = modules[file[:-3]].mf.__str__()
                assert(outstr == '\n'.join(lines))
    # read hierachy
    hier_path = vsrc_path / Path('hier.json')
    hier = read_hierachy(hier_path)
    # read all io for target
    target_def: module_def = modules[target_module].mf.get_module_def()
    target_io = target_def.io_list
    target_io_dir = dict() # True for input, False for output
    for io in target_io:
        target_io_dir[io.name] = io.iotype == 'input'
    def do_partition_dfs(hier: dict, target_module: str):
        nonlocal target_io
        nonlocal modules
        assert(hier['module_name'] != target_module)
        curr_module = modules[hier['module_name']]
        assert(curr_module is not None)
        # Does not support a corner case if there is a path some module appear twice or more
        # This cycle can be false positive if we use parameter to limit the depth
        for each_inst in hier['instances']:
            if each_inst['module_name'] == target_module:
                curr_inst = curr_module.mf.find_inst(each_inst['instance_name'])
                assert(curr_inst is not None)
                name_prefix = io_format.format(target_module, curr_module.count)
                # add io to module
                for io in target_io:
                    reversed = module_io_def('output' if io.iotype == 'input' else 'input', io.width, io.name_indent, name_prefix+io.name, io.annotation)
                    curr_module.mf.add_io_def(reversed)
                # add assign to these signals
                assign_to_add = []
                for io in curr_inst.io_list:
                    assert(io.name in target_io_dir)
                    if target_io_dir[io.name]:
                        assign_to_add.append((name_prefix + io.name, "({})".format(io.expr)))
                    else:
                        assign_to_add.append((io.expr, "({})".format(name_prefix + io.name)))
                curr_module.mf.add_assign(assign_to_add)
                # remove inst
                curr_module.mf.remove_inst(each_inst['instance_name'])
                # add to count
                curr_module.count += 1
            else:
                if each_inst['module_name'] not in modules:
                    continue
                inner_module = modules[each_inst['module_name']]
                curr_inst = curr_module.mf.find_inst(each_inst['instance_name'])
                assert(curr_inst is not None)
                # Check if visited
                if inner_module.count == 0:
                    do_partition_dfs(each_inst, target_module)
                if inner_module.count > 0:
                    # add io to current module
                    for inner_idx in range(0, inner_module.count):
                        prefix_outer = io_format.format(target_module, curr_module.count)
                        prefix_inner = io_format.format(target_module, inner_idx)
                        # add io to module
                        for io in target_io:
                            reversed = module_io_def('output' if io.iotype == 'input' else 'input', io.width, io.name_indent, prefix_outer+io.name, io.annotation)
                            curr_module.mf.add_io_def(reversed)
                        # add io to current inst
                        expr_indent = curr_inst.io_list[0].expr_indent
                        for io in target_io:
                            curr_inst.io_list.append(inst_io_def(prefix_inner + io.name, prefix_outer + io.name, expr_indent))
                    curr_module.count += 1
        if curr_module.count == 0:
            curr_module.count = -1 # mark as visited but no path
    do_partition_dfs(hier, target_module)
    if header_path != '':
        write_to_file(header_path + "/module_{}_io.h".format(target_module),
                      target_def.gen_io_struct_header(hier['module_name'], modules[hier['module_name']].count, io_format, set(mask_io)) + "\n")
        write_to_file(header_path + "/module_{}_io.cpp".format(target_module),
                      target_def.gen_io_struct_c(hier['module_name'], modules[hier['module_name']].count, io_format, set(mask_io)) + "\n")
    for module_name, module in modules.items():
        content_to_write = module.mf.__str__() + "\n"
        write_to_file(partitioned_path / Path(module_name + '.sv'), content_to_write)

parser = argparse.ArgumentParser(description='Partition Verilog by Module Name')
parser.add_argument("-t", "--target", type=str, help="Target module name", required=True)
parser.add_argument("-d", "--directory", type=str, help="Header and C save path", required=False, default='')
parser.add_argument("-m", "--mask", type=str, help="Mask io on target module when do peek or poke", required=False, action="extend", default=[], nargs='*')
args = parser.parse_args()
do_partition(Path('vsrc'), Path('partitioned'), args.target, '{}_{}_', args.directory, args.mask)
