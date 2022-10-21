import os


def run_first():
    root = "/home/center/Delta-Marabou/resources/nnet/coav"
    properties = "/home/center/Delta-Marabou/resources/properties/builtin_property.txt"
    for path, dir_names, file_names in os.walk(root):
        for file in file_names:
            if file.endswith(".nnet"):
                file_path = os.path.join(path, file)
                command = f"/home/center/Delta-Marabou/build/Marabou {file_path} {properties} > {file_path + '.1.log'}"
                print(f"Running {command}")
                os.system(command)


def run_second():
    root = "/home/center/Delta-Marabou/resources/nnet/acasxu/test"
    properties = "/home/center/Delta-Marabou/resources/properties/acas_property_1.txt"
    for path, dir_names, file_names in os.walk(root):
        for file in file_names:
            if file.endswith(".nnet"):
                file_path = os.path.join(path, file)
                file_search_tree = file_path + ".searchTree"
                command = f"/home/center/Delta-Marabou/build/Marabou {file_path} {properties} --search-tree-file {file_search_tree} --incremental-verification > {file_path + '.5.log'}"
                print(f"{command}")
                os.system(command)


def compare():
    root = "/home/center/Delta-Marabou/resources/nnet/coav"
    for path, dir_names, file_names in os.walk(root):
        for file in file_names:
            if file.endswith(".nnet"):
                log1 = os.path.join(path, file + ".1.log")
                log2 = os.path.join(path, file + ".2.log")
                if os.path.exists(log1) and os.path.exists(log2):
                    file1 = open(log1)
                    res1 = file1.readlines()[-1]
                    file2 = open(log2)
                    res2 = file2.readlines()[-1]
                    if res1 != res2:
                        print(file)


if __name__ == "__main__":
    # run_first()
    run_second()
    # compare()
