from time import process_time as clock

# Initialize the data
with open("day03.in") as f:
    data = [l.split() for l in f]
    for i in range(len(data)):
        del data[i][0]
        del data[i][0]
        data[i][0] = tuple(int(j) for j in data[i][0][:-1].split(","))
        data[i][1] = tuple(int(j) for j in data[i][1].split("x"))
    grid = [[0 for j in range(1000)] for i in range(1000)]

# Function for solving the first problem
def first ():
    st = clock()
    res = 0
    for sq in data:
        x_offset, y_offset = sq[0]
        for x in range(sq[1][0]):
            for y in range(sq[1][1]):
                if grid[y_offset + y][x_offset + x] == 0:
                    grid[y_offset + y][x_offset + x] = 1
                elif grid[y_offset + y][x_offset + x] == 1:
                    grid[y_offset + y][x_offset + x] = 2
                    res += 1

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    for i, sq in enumerate(data):
        i += 1
        x_offset, y_offset = sq[0]
        found = True
        for x in range(sq[1][0]):
            for y in range(sq[1][1]):
                if grid[y_offset + y][x_offset + x] == 2:
                    found = False
        if found:
            res = i
            break

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
