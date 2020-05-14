from time import process_time as clock

# Helper function that repeats a list
def repeat (l):
    while True:
        for i in l:
            yield i

# Initialize the data
with open("01.txt") as f:
    data = [int(i) for i in f.read().strip().split("\n")]

# Function for solving the first problem
def first ():
    st = clock()
    res = sum(data)
    print("First:", res, "Time:", clock() - st)

# Function for solving the first problem
def second ():
    st = clock()
    res = 0
    sums = set()
    it = repeat(data)
    while res not in sums:
        sums.add(res)
        res += next(it)
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
