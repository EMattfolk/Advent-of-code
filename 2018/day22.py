from time import process_time as clock
from collections import deque
from heapq import heappop as pop, heappush as push

# Initialize the data
with open("22.txt") as f:
    data = [l.split()[1] for l in f]
    depth = int(data[0])
    target = data[1].split(",")
    target = (int(target[0]), int(target[1]))

# Function for solving the first problem
def first ():
    st = clock()
    tx, ty = target
    tx += 1
    ty += 1
    grid = [[0] * tx for _ in range(ty)]
    for y in range(ty):
        for x in range(tx):

            if y == 0:
                geo = x * 16807
            elif x == 0:
                geo = y * 48271
            elif y == ty - 1 and x == tx - 1:
                geo = 0
            else:
                geo = grid[y][x-1] * grid[y-1][x]

            grid[y][x] = (geo + depth) % 20183

    res = 0
    for row in grid:
        for i in row:
            res += i % 3

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    tx, ty = target
    tx += 1
    ty += 1

    padding = 60
    grid = [[0] * (tx + padding) for _ in range(ty + padding)]

    times = {}

    for y in range(ty + padding):
        for x in range(tx + padding):

            if y == 0:
                geo = x * 16807
            elif x == 0:
                geo = y * 48271
            elif y == ty - 1 and x == tx - 1:
                geo = 0
            else:
                geo = grid[y][x-1] * grid[y-1][x]

            grid[y][x] = (geo + depth) % 20183
            times[(x, y)] = [100000000] * 3

    for y in range(ty + padding):
        for x in range(tx + padding):
            grid[y][x] %= 3

    # Rocky  = 0
    # Wet    = 1
    # Narrow = 2

    # Torch        = 0  not wet
    # Climber gear = 1  not narrow
    # Niether      = 2  not rocky

    heuristic = lambda p: abs(p[0] - target[0]) + abs(p[1] - target[1])

    open_nodes = []

    # (heuristic, time, x, y, gear)
    push(open_nodes, (heuristic((0, 0)), 0, 0, 0, 0))

    res = (10000000, (0, 0))

    while open_nodes:

        heu, time, x, y, gear = pop(open_nodes)

        if heu >= times[(x, y)][gear]:
            continue

        times[(x, y)][gear] = heu

        if (x, y) == target:
            if gear != 0:
                time += 7
            if (time, (x, y)) < res:
                res = (time, (x, y))
            continue

        for nx, ny in [(x + 1, y), (x, y + 1), (x - 1, y), (x, y - 1)]:
            if (nx, ny) not in times:
                continue

            terrain = grid[ny][nx]
            if (terrain + 2) % 3 != gear:
                push(open_nodes, (time + 1 + heuristic((nx, ny)), time + 1, nx, ny, gear))

            old_terrain = grid[y][x]
            if old_terrain != terrain:
                new_gear = (gear + 1) % 3
                if (old_terrain + 2) % 3 == new_gear:
                    new_gear = (gear + 2) % 3

                push(open_nodes, (time + 8 + heuristic((nx, ny)), time + 8, nx, ny, new_gear))

    res = res[0]

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
