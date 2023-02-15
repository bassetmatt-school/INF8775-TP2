import torch
import math
import copy

# if torch.cuda.is_available():
#     import cupy as np
# else:
#     import numpy as np
import numpy as np
import matplotlib.pyplot as plt

def load_file(file:str) :
    with open(file) as f:
        data = f.read().replace('\t',' ').splitlines()
        N = int(data[0])
        oneLineMatrix = " ".join(data[1:]).split(' ')
        matrix = np.array(list(map(int, oneLineMatrix))).reshape(N, 2)
    return N, matrix

file = "data/hard_N52"
n, m = load_file(file)
# # print(n)
# print(m)
# plt.scatter(m[:,0], m[:,1], color="green", s=1)
# plt.show()


def euclidianDist(a, b):
    sq = (a[0] - b[0])**2 + (a[1] - b[1])**2
    return np.sqrt(sq)

def greeddyTSP(T:np.array):
    result = [0]
    cityList = copy.deepcopy(T)
    print(cityList)
    idx = 0
    i = 0
    while True:
        city = cityList[idx]
        cityList = np.delete(cityList, idx, axis = 0)
        if (cityList.size == 0 or i == 5) :
            return result
        distances = np.array([euclidianDist(c, city) for c in cityList])
        # print(distances)
        idx = np.argmin(distances)
        # print(x)
        y = np.argmin(np.array([euclidianDist(c, cityList[idx]) for c in T]))

        # print(y)
        result.append(y)
        # print(f"{i = :2d} | Distances : {distances}")
        # print(f"   argmin in {idx = :2d}, city in {cityList[idx]}, global index {y = :2d}")
        # print(f"{abs(T - cityList[idx]) = }")
        i += 1
        

indexes = greeddyTSP(m)