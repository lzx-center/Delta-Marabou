"""
1: Header text. This can be any number of lines so long as they begin with "//"
2: Four values: Number of layers, number of inputs, number of outputs, and maximum layer size
3: A sequence of values describing the network layer sizes. Begin with the input size, then the size of the first layer, second layer, and so on until the output layer size
4: A flag that is no longer used, can be ignored
5: Minimum values of inputs (used to keep inputs within expected range)
6: Maximum values of inputs (used to keep inputs within expected range)
7: Mean values of inputs and one value for all outputs (used for normalization)
8: Range values of inputs and one value for all outputs (used for normalization)
9+: Begin defining the weight matrix for the first layer, followed by the bias vector. The weights and biases for the second layer follow after, until the weights and biases for the output layer are defined.
"""
import os
import random


class testGenerator:
    def __init__(self):
        self.layers, self.inputs, self.outputs, self.maximum_layer_size = 2, 2, 3, 2
        self.layer_nums = [self.inputs, 2, self.outputs]
        assert self.layers == len(self.layer_nums) - 1

        self.min_val_for_input, self.max_val_for_input = -1.0, 1.0
        self.mean_val_for_input, self.one_val_for_output = 0.0, 0.0
        self.range_val_for_input, self.range_for_output = 1.0, 1.0

        self.matrix = [([[-1.0 for _ in range(self.layer_nums[i])] for _ in range(self.layer_nums[i + 1])],
                        [0 for _ in range(self.layer_nums[i + 1])]) for i in range(len(self.layer_nums) - 1)]


def generator(file_path, property_path=None):
    layers, inputs, outputs, maximum_layer_size = 2, 2, 1, 2
    layer_nums = [inputs, 2, outputs]

    min_val_for_input, max_val_for_input = -1.0, 1.0
    mean_val_for_input, one_val_for_output = 0.0, 0.0
    range_val_for_input, range_for_output = 1.0, 1.0

    with open(file_path, "w+") as f:

        def printf(*arg, **kwargs):
            print(*arg, **kwargs, file=f)

        print("//auto generated", file=f)
        print(f"{layers},{inputs},{outputs},{maximum_layer_size},", file=f)
        for layer_num in layer_nums:
            print(layer_num, end=",", file=f)
        print(file=f)
        print("0,", file=f)
        # line 5
        for i in range(inputs):
            print(min_val_for_input, end=",", file=f)
        print(file=f)
        # line 6
        for i in range(inputs):
            printf(max_val_for_input, end=",")
        printf()
        # line 7
        for i in range(inputs):
            printf(mean_val_for_input, end=",")
        printf(f"{one_val_for_output},")
        # line 8
        for i in range(inputs):
            printf(range_val_for_input, end=",")
        printf(f"{range_for_output},")
        # matrix
        for i in range(len(layer_nums) - 1):
            for h in range(layer_nums[i + 1]):
                for l in range(layer_nums[i]):
                    printf(random.uniform(-1, 1), end=",")
                printf()
            for h in range(layer_nums[i + 1]):
                printf("0.0,")
            bound = random.uniform(-2, 2)
            with open(property_path, "w+") as t:
                def printt(*arg, **kwargs):
                    print(*arg, **kwargs, file=t)

                printt(f"y0 >= {bound}")
    command = f"/home/center/Delta-Marabou/build/Marabou {file_path} {property_path} > ./test.log"
    print(command)
    os.system(command)
    with open("./test.log") as f:
        for line in f.readlines():
            if "Search Tree" in line:
                size = int(line.split(" ")[-1].strip("\n"))
                print(size)
                return size


def modify(file_path, save_to):
    with open(file_path) as f:
        with open(save_to, "w+") as s:
            lines = f.readlines()
            for line in lines[:8]:
                print(line, end="", file=s)
            for line in lines[8:]:
                nums = line.strip("\n").split(",")[:-1]
                for num in nums:
                    # if len(nums) != 1:
                    num = float(num) + random.uniform(-0.7, 0.7)
                    # print('%.4f' % num, end=",", file=s)
                    print(num, end=",", file=s)
                print(file=s)
    command = f"/home/center/Delta-Marabou/build/Marabou {save_to} {'/home/center/Delta-Marabou/resources/nnet/testp.txt'} > ./test.log"
    os.system(command)
    with open("./test.log") as f:
        lines = f.readlines()
        size = 0
        for line in lines:
            if "Search Tree" in line:
                size = int(line.split(" ")[-1].strip("\n"))
        if size > 1:
            for line in lines:
                if "unsat" in line:
                    print("modify unsat")
                    command = f"/home/center/Delta-Marabou/build/Marabou {save_to} " \
                              "/home/center/Delta-Marabou/resources/nnet/testp.txt " \
                              "--search-tree-file-path /home/center/Delta-Marabou/resources/nnet/test1.nnet.searchTree" \
                              " --incremental-verification" \
                              " > ./test2.log "
                    os.system(command)
                    with open("./test2.log") as s:
                        lines = s.readlines()
                        for line in lines:
                            if "unsat" in line:
                                print("after unsat")
                                return size
                    break
        return 0


if __name__ == "__main__":
    net_path = "/home/center/Delta-Marabou/resources/nnet/test1.nnet"
    prop_path = "/home/center/Delta-Marabou/resources/nnet/testp.txt"

    while True:
        size = modify(net_path, net_path.replace("test1.nnet", "test1.modify.nnet"))
        if size > 1:
            break
    # while True:
    #     size = generator(net_path, prop_path)
    #     if 6 <= size <= 6:
    #         command = f"cp {net_path} {net_path.strip('.nnet')}_{size}.1.nnet"
    #         os.system(command)
    #         command = f"cp {prop_path} {prop_path.strip('.txt')}_{size}.1.txt"
    #         os.system(command)
    #         break
