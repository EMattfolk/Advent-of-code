from time import process_time as clock
from collections import deque

# Initialize the data
with open("day22.in") as f:
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

    padding = 20 
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
            times[(x,y)] = (100000000, set())
    
    for y in range(ty + padding):
        for x in range(tx + padding):
            grid[y][x] %= 3

    # Rocky  = 0
    # Wet    = 1
    # Narrow = 2

    # Torch        = 0  not wet
    # Climber gear = 1  not narrow
    # Niether      = 2  not rocky

    times[(0, 0)] = (0, set())
    times[target] = (sum(target) * 8, set())
    # (x, y, gear, time)
    open_nodes = deque([(0, 0, 0, 0)])
    
    while open_nodes:

        x, y, gear, time = open_nodes.pop()

        if time > times[target][0]: continue

        if (x, y) == target:
            if gear != 0:
                time += 7
            if times[target][0] > time:
                times[target] = (time, {(gear, time)})
            continue

        if time > times[(x, y)][0] + 6: continue
        if time <= times[(x, y)][0] + 6 and time >= times[(x, y)][0]:
            if (gear, time) not in times[(x, y)][1]:
                times[(x, y)][1].add((gear, time))
            else:
                continue
        else: times[(x, y)] = (time, {(gear, time)})

        for nx, ny in [(x + 1, y), (x, y + 1), (x - 1, y), (x, y - 1)]:
            if nx < 0 or nx >= tx + padding or ny < 0 or ny >= ty + padding: continue

            terrain = grid[ny][nx]
            if (terrain + 2) % 3 != gear:
                open_nodes.appendleft((nx, ny, gear, time + 1))

            old_terrain = grid[y][x]
            if old_terrain != terrain:
                new_gear = (gear + 1) % 3
                if (old_terrain + 2) % 3 == new_gear:
                    new_gear = (gear + 2) % 3

                open_nodes.appendleft((nx, ny, new_gear, time + 8))


    res = times[target][0]

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
