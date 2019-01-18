from time import process_time as clock

# Initialize the data
with open("day13.in") as f:
    grid = [list(l) for l in f]

positions = []
velocities = {}
for y in range(len(grid)):
    for x in range(len(grid[y])):
        pos = (x, y)
        if grid[y][x] in [">", "v", "<", "^"]:
            positions.append(pos)
            if grid[y][x] == ">":
                velocities[pos] = (1, 0, 0)
                grid[y][x] = "-"
            if grid[y][x] == "v":
                velocities[pos] = (0, 1, 0)
                grid[y][x] = "|"
            if grid[y][x] == "<":
                velocities[pos] = (-1, 0, 0)
                grid[y][x] = "-"
            if grid[y][x] == "^":
                velocities[pos] = (0, -1, 0)
                grid[y][x] = "|"

def turn (vel):

    if vel[2] % 3 == 0:
        vel = turn_left(vel)
    if vel[2] % 3 == 2:
        vel = turn_right(vel)
    vel = (vel[0], vel[1], vel[2] + 1)

    return vel

def turn_left (vel):
    return (vel[1], -vel[0], vel[2])

def turn_right (vel):
    return (-vel[1], vel[0], vel[2])

def sort (l):
    l = [(y, x) for x, y in l]
    l.sort()
    l = [(y, x) for x, y in l]
    return l

# Function for solving the both problems
def both ():
    st = clock()
    global positions
    running = True
    has_crashed = False
    while running:
        positions = sort(positions)
        to_remove = set()
        for p in range(len(positions)):
            pos = positions[p]
            if pos in to_remove:
                continue
            vel = velocities[pos]
            pos = (pos[0] + vel[0], pos[1] + vel[1])
            positions[p] = pos
            if positions.count(pos) > 1:
                to_remove.add(pos)
                if not has_crashed:
                    first = pos
                    has_crashed = True
                if len(positions) == 3:
                    last = [i for i in positions if i not in to_remove][0]
                    running = False
            if grid[pos[1]][pos[0]] == '/':
                if vel[0]:
                    vel = turn_left(vel)
                else:
                    vel = turn_right(vel)

            elif grid[pos[1]][pos[0]] == '\\':
                if vel[0]:
                    vel = turn_right(vel)
                else:
                    vel = turn_left(vel)

            elif grid[pos[1]][pos[0]] == '+':
                vel = turn(vel)
            
            velocities[pos] = vel
        for r in to_remove:
            positions.remove(r)
            positions.remove(r)

    res = "First: {} Last: {}".format(first, last)

    print(res, "Time:", clock() - st)

# Solve the problems
both()
