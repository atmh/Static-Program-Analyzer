#!/usr/bin/env python3


from mako.template import Template
import sys
import os


def arg_arg_res(entity_1, entity_2, entity_3, select_entity):
    # print(entity_1, entity_2, entity_3, select_entity)
    if select_entity == 'Stmt':
        return ', '.join(['"1"', '"2"', '"3"'])
    else:
        res = []
        if entity_1 == select_entity:
            res.append('"1"')
        
        if entity_2 == select_entity:
            res.append('"2"')
        
        if entity_3 == select_entity:
            res.append('"3"')

        return ', '.join(res)

    return '""'


if __name__ == "__main__":
    dir_path = os.path.dirname(os.path.realpath(__file__))
    template = Template(filename=f'{dir_path}/SuchThat.mako')

    declarations = 'read r1, r2; print p1, p2; assign a1, a2; call c1, c2; while w1, w2; if i1, i2; stmt s1, s2;'
    # selects = ['r1', 'r2', 'p1', 'p2', 'a1', 'a2', 'c1', 'c2', 'w1', 'w2', 'i1', 'i2']
    selects = [
        {'val': 'r1', 'type': 'read', 'addType': 'read'},
        {'val': 'p1', 'type': 'print', 'addType': 'print'},
        {'val': 'a1', 'type': 'assign', 'addType': 'assign'},
        {'val': 'c1', 'type': 'call', 'addType': 'call'},
        {'val': 'w1', 'type': 'while',  'addType': 'while'},
        {'val': 'i1', 'type': 'if', 'addType': 'if'},
        {'val': 's1', 'type': 'stmt', 'addType': 'read'},
        ]

    add_entity_types = [
        {'addType': 'read'},
        {'addType': 'print'},
        {'addType': 'assign'},
        {'addType': 'call'},
        {'addType': 'while'},
        {'addType': 'if'},
    ]

    args1 = [
        {'val': '_', 'type': 'wildcard'},
        {'val': 1, 'type': 'value'},
        {'val': 2, 'type': 'value'},
        {'val': 3, 'type': 'value'},
    ]

    args2 = args1.copy()

    file_name_map = {
        'Follows': 'Follows',
        # 'Follows*': 'FollowsStar',
        'Parent': 'Parent',
        # 'Parent*': 'ParentStar',
    }

    rls = [
        'Follows', 
        # 'Follows*', 
        'Parent', 
        # 'Parent*'
    ]

    for relation in rls:
        with open(f'{dir_path}/{file_name_map[relation]}SuchThat.cpp', 'w') as f:
            kwargs = {
                'relation': relation,
                'args1': args1,
                'args2': args2,
                'declarations': declarations,
                'selects': selects,
                'add_entity_types': add_entity_types,
                'arg_arg_res': arg_arg_res,
            }
            f.write(template.render(**kwargs))
