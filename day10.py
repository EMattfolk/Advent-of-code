from time import process_time as clock

# My file got deleted ok

# Function for solving the first problem
def first ():
    st = clock()
    with open("day10.out") as f:
        res = "\n" + f.read() + "\n"
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    res = 10227
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
