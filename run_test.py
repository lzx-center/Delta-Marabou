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
    root = "/home/center/Delta-Marabou/resources/nnet/coav"
    properties = "/home/center/Delta-Marabou/resources/properties/builtin_property.txt"
    for path, dir_names, file_names in os.walk(root):
        for file in file_names:
            if file.endswith(".nnet"):
                file_path = os.path.join(path, file)
                file_search_tree = file_path + ".searchTree"
                command = f"/home/center/Delta-Marabou/build/Marabou {file_path} {properties} --search-tree-file {file_search_tree} --incremental-verification > {file_path + '.2.log'}"
                print(f"{command}")
                # os.system(command)


if __name__ == "__main__":
    run_second()
