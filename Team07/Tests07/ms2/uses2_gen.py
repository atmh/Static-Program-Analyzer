#!/usr/bin/env python3

if __name__ == "__main__":
    variables = ['a', 'b', 'c', 'gloria', 'sasha']
    synonyms = ['v', 'a', 'pn', 's', 'c', 'p', 'if', 'w']
    selects = ['v', 'v2', 'a', 'a2', 'pn', 'pn2', 's', 's2', 'c', 'c2', 'p', 'p2', 'if', 'if2', 'w', 'w2']
    declarations = 'variable v, v2; assign a, a2; print pn, pn2; stmt s, s2; call c, c2; procedure p, p2; if if, if2; while w, w2;'
    val_strs = ['"Barbie"', '"Ken"', '"Ruth"'] + [str(x) for x in range(1, 35)]
    var_strs = ['"a"', '"b"', '"c"', '"gloria"', '"sasha"']

    query_idx = 0

    # wildcard wildcard
    for synonym in selects:
        query_idx += 1
        print(query_idx)
        print(declarations)
        print(f'Select {synonym} such that Uses(_, _)')
        print('SemanticError')
        print('5000')


    # wildcard synonym
    for synonym in selects:
        query_idx += 1
        print(query_idx)
        print(declarations)
        print(f'Select {synonym} such that Uses(_, v2)')
        print('SemanticError')
        print('5000')

        for s2 in synonyms:
            query_idx += 1
            print(query_idx)
            print(declarations)
            print(f'Select {synonym} such that Uses(_, {s2})')
            print('SemanticError')
            print('5000')


    # wildcard value
    for synonym in selects:
        for var in variables:
            query_idx += 1
            print(query_idx)
            print(declarations)
            print(f'Select {synonym} such that Uses(_, "{var}")')
            print('SemanticError')
            print('5000')


    # synonym wildcard
    for synonym in selects:
        for s2 in synonyms:
            query_idx += 1
            print(query_idx)
            print(declarations)
            print(f'Select {synonym} such that Uses({s2}, _)')
            print('none' if s2 in ['a', 'pn', 'if', 'w', 'p', 'c'] else 'SemanticError')
            print('5000')


    # synonym synonym
    for synonym in selects:
        for s2 in synonyms:
            for s3 in synonyms:
                query_idx += 1
                print(query_idx)
                print(declarations)
                print(f'Select {synonym} such that Uses({s2}, {s3})')
                print('none' if s2 in ['a', 'pn', 'if', 'w', 'p', 'c'] and s3 in ['v'] else 'SemanticError')
                print('5000')


    # synonym value
    for synonym in selects:
        for s2 in synonyms:
            for s3 in variables:
                query_idx += 1
                print(query_idx)
                print(declarations)
                print(f'Select {synonym} such that Uses({s2}, "{s3}")')
                print('none' if s2 in ['a', 'pn', 'if', 'w', 'p', 'c'] else 'SemanticError')
                print('5000')


    # value wildcard
    for synonym in selects:
        for val in val_strs:
            query_idx += 1
            print(query_idx)
            print(declarations)
            print(f'Select {synonym} such that Uses({val}, _)')
            print('none')
            print('5000')


    # value synonym
    for synonym in selects:
        for val in val_strs:
            for s3 in synonyms:
                query_idx += 1
                print(query_idx)
                print(declarations)
                print(f'Select {synonym} such that Uses({val}, {s3})')
                print('none' if s3 in ['v'] else 'SemanticError')
                print('5000')


    # value value
    for synonym in selects:
        for val in val_strs:
            for var in var_strs:
                query_idx += 1
                print(query_idx)
                print(declarations)
                print(f'Select {synonym} such that Uses({val}, {var})')
                print('none')
                print('5000')
