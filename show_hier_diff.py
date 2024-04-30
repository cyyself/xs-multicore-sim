#!/usr/bin/env python3

import json
from pathlib import Path

def read_hierachy(filename: Path):
    with open(filename, 'r') as f:
        return json.load(f)
    
hier = read_hierachy('vsrc/hier.json')

def find_module_in_hier(hier: dict, module_name = ''):
    # find two instance of the duplicated module in one module
    module_hier = []
    for each_inst in hier['instances']:
        if each_inst['module_name'].startswith(module_name):
            module_hier.append(each_inst)
    if len(module_hier) > 1:
        return module_hier
    else:
        for each_inst in hier['instances']:
            res = find_module_in_hier(each_inst, module_name)
            if len(res) > 0:
                return res
        return []

res = find_module_in_hier(hier, 'XSTile')

def print_diff_module_dfs(hier1: dict, hier2: dict, indent: int):
    space = '\t' * indent
    print("{}{}-{}".format(space, hier1['module_name'], hier2['module_name']))
    for idx in range(len(hier1['instances'])):
        if hier1['instances'][idx]['module_name'] != hier2['instances'][idx]['module_name']:
            print_diff_module_dfs(hier1['instances'][idx], hier2['instances'][idx], indent + 1)

print_diff_module_dfs(res[0], res[1], 0)