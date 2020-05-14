from time import process_time as clock
sta = clock()

# Initialize the data
serial = 3613

def get_cell (x,y):
    rackid = x + 10
    cell = rackid * y + serial
    cell *= rackid
    cell = (cell // 100) % 10
    cell -= 5
    return cell

grid = [[get_cell(x,y) for x in range(1, 302)] for y in range(1, 302)]

def get_adjacent_sum (x,y,size):
    s = 0
    for i in range(x, x + size):
        for j in range(y, y + size):
            s += grid[j][i]
    return s

def get_max (size):
    pos = (0, 0)
    s = 0
    m = -1000
    init_sum = get_adjacent_sum(0, 0, size)
    for y in range(301 - size):
        s = init_sum
        for x in range(301 - size):
            if s > m:
                pos = (x + 1, y + 1, size)
                m = s
            for i in range(y, y+size):
                s += grid[i][x+size] - grid[i][x]

        for i in range(size):
            init_sum += grid[y+size][i] - grid[y][i]

    return m, pos

# Function for solving the first problem
def first ():
    st = clock()

    res = get_max(3)
    res = "{},{}".format(res[1][0], res[1][1])

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()

    res = (-1000, (0,0,0))
    for size in range(1, 30):
        temp = get_max(size)
        if temp[0] > res[0]:
            res = temp
    res = "{},{},{}".format(res[1][0], res[1][1], res[1][2])

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
