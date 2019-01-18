from time import process_time as clock
from copy import deepcopy
times = {l:60+1+i for i,l in enumerate("ABCDEFGHIJKLMNOPQRSTUVWXYZ")}

# Initialize the data
with open("day7.in") as f:
    dependencies = {i:[] for i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ"}
    for i in f:
        i = i.split()
        dependencies[i[7]].append(i[1])

# Function for solving the first problem
def first ():
    st = clock()
    res = ""
    dep = deepcopy(dependencies)

    while dep:

        toremove = set()

        for key in dep:
            if len(dep[key]) == 0:
                toremove.add(key)

        toremove = sorted(toremove)
        r = toremove[0]
        del dep[r]
        for key in dep:
            if r in dep[key]:
                dep[key].remove(r)

        res += r

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    res = 0
    dep = deepcopy(dependencies)
    he  = [[0,""], [0,""], [0,""], [0,""], [0,""]]
    toremove = set()

    for key in dep:
        if len(dep[key]) == 0:
            toremove.add(key)
            dep[key].append("")

    while True:

        for i in range(5):
            if he[i][0] == 0:
                if he[i][1] != "":
                    r = he[i][1]
                    del dep[r]
                    for key in dep:
                        if r in dep[key]:
                            dep[key].remove(r)
                            if len(dep[key]) == 0:
                                toremove.add(key)
                                dep[key].append("")
                    he[i][1] = ""
                if len(toremove) > 0:
                    he[i][1] = sorted(toremove)[-1]
                    he[i][0] = times[he[i][1]]
                    toremove -= { he[i][1] }

        if not dep: break

        for i in range(5):
            if he[i][0] == 0:
                continue
            he[i][0] -= 1
        
        res += 1


    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
