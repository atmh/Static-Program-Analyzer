#!/usr/bin/env python3

import argparse
import os
from lxml import etree


def is_correct(file_name):
    root = etree.parse(file_name).getroot()

    if root.find('.//exception') is not None:
        print("Exception found!")
        return False

    if root.find('.//failed') is not None:
        print("Incorrect test case found")
        return False

    if root.find('.//timeout') is not None:
        print("Timeout found")
        return False

    return True


def run(dir, args):
    files = []
    dirs = []
    for filename in os.listdir(dir):
        file_path = os.path.join(dir, filename)
        if os.path.isdir(file_path):
            dirs.append((file_path, filename))
        else:
            files.append((file_path, filename))

    # run through files
    for query_file_path, query_filename in files:
        # don't run stress tests on debug as it will timeout
        if (args.build_type.lower() != "release" or args.platform == "windows") and "stress" in query_file_path:
            continue

        idx = query_filename.find('_queries')
        if idx == -1:  # not found
            continue

        test_case_name = query_filename[:idx]

        # find the matching source
        for source_file_path, source_filename in files:
            if '_source' not in source_filename:
                continue

            if not source_filename.startswith(test_case_name + '_source'):
                continue

            print(f'Running with source_file = {source_file_path}, query_file = {query_file_path}')
            if args.platform == 'windows':
                os.system(f'{dir_path}/../Code07/build/src/autotester/Debug/autotester.exe {source_file_path} {query_file_path} {dir_path}/out.xml')
            else:
                os.system(f'{dir_path}/../Code07/build/src/autotester/autotester {source_file_path} {query_file_path} {dir_path}/out.xml')

            if not is_correct(f'{dir_path}/out.xml'):
                print(f'Error: source_file = {source_file_path}, query_file = {query_file_path}')
                exit(1)


    # recurse through directories
    for d, _ in dirs:
        run(d, args)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--build_type', help='Release or debug', default='debug')
    parser.add_argument('--platform', help='windows or not', default='ubuntu')
    args = parser.parse_args()

    # build the binary
    dir_path = os.path.dirname(os.path.realpath(__file__))
    # build with 1 core for easy debug
    CMAKE_OPTS = "-DCMAKE_BUILD_TYPE=Release" if args.build_type.lower() == "release" and args.platform != "windows" else "-DCMAKE_BUILD_TYPE=Debug"

    if args.platform != "windows":
        os.system(f"cd {dir_path}/../Code07 && cmake -Bbuild -S. {CMAKE_OPTS} && cmake --build build --target autotester -j$(nproc)")
    else:
        os.system(f"cd {dir_path}/../Code07 && cmake -Bbuild -S. {CMAKE_OPTS} && cmake --build build --target autotester -j4")

    run(dir_path, args)

    print("All Tests Complete")
