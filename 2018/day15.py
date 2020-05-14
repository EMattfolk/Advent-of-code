from time import process_time as clock
from copy import deepcopy as cp
from collections import deque

# Initialize the data
with open("15.txt") as f:
    grid = [list(l.strip()) for l in f]
    backup = grid

# Helper functions
def neigh (y, x):
    return [(y - 1, x), (y, x - 1), (y, x + 1), (y + 1, x)]

def neigh_units (y, x):
    return [grid[j][i] for j,i in neigh(y, x)]

# Breadth first search (I think
def step (y, x):

    # Open nodes
    op = deque([(y, x)])
    # Vistited nodes in set for fast checks
    visited = set()
    # Dict used to determine path
    came_from = {}

    # Continue while there are still nodes
    while op:

        # Get first node
        current = op.pop()
        # We have now visited this node
        visited.add(current)

        # If we are at the end we reconstruct the path
        # and return the first step
        if grid[current[0]][current[1]] == "@":

            while came_from[current] != (y, x):
                current = came_from[current]

            return current

        # Add new nodes to be vistited
        for pos in neigh(current[0], current[1]):
            unit = grid[pos[0]][pos[1]]
            if ((pos not in visited) and (pos not in op)) and (unit == "." or unit == "@"):
                op.appendleft(pos)
                came_from[pos] = current

    return None

# Function for solving the problem
def solve (elf_dmg=3, ignore_losses=True):

    # Get a new fresh grid
    global grid
    grid = cp(backup)

    # Units saved as (y, x, hp, type)
    elves = []
    goblins = []
    for y, row in enumerate(grid):
        for x, obj in enumerate(grid[y]):
            if obj == "E":
                elves += [(y, x, 200, "e")]
            elif obj == "G":
                goblins += [(y, x, 200, "g")]

    # Main loop
    turn = 0
    while elves and goblins:

        turn += 1

        ei = 0
        gi = 0
        elves.sort()
        goblins.sort()

        while ei != len(elves) or gi != len(goblins):

            # If no units are left we break and
            # remove the turn since it is not complete
            if len(elves) == 0 or len(goblins) == 0:
                turn -= 1
                break

            # Assign the unit to move
            if ei == len(elves):
                curr = goblins[gi]
            elif gi == len(goblins):
                curr = elves[ei]
            else:
                if goblins[gi] < elves[ei]:
                    curr = goblins[gi]
                else:
                    curr = elves[ei]

            # Set current enemy
            en = "G" if curr[3] == "e" else "E"
            enemies = goblins if en == "G" else elves

            search = en not in neigh_units(curr[0], curr[1])

            # Search if no enemies are near
            if search:

                # Set potential tiles
                for e in enemies:
                    for y, x in neigh(e[0], e[1]):
                        if grid[y][x] == ".":
                            grid[y][x] = "@"

                # Find the next position for the unit
                new_pos = step(curr[0], curr[1])

                # Undo potential tiles
                for e in enemies:
                    for y, x in neigh(e[0], e[1]):
                        if grid[y][x] == "@":
                            grid[y][x] = "."

                # Update unit and grid with new positions
                if new_pos != None:
                    grid[new_pos[0]][new_pos[1]] = grid[curr[0]][curr[1]]
                    grid[curr[0]][curr[1]] = "."
                    curr = (new_pos[0], new_pos[1], curr[2], curr[3])

            # Attack

            # Find targets
            targets = []
            for pos, unit in zip(neigh(curr[0], curr[1]), neigh_units(curr[0], curr[1])):
                if unit == en:
                    for i,e in enumerate(enemies):
                        if e[0] == pos[0] and e[1] == pos[1]:
                            targets.append([i, e])

            # Attack if we have a target
            if targets:

                # Get target to attack
                target = targets[0]
                for t in targets[1:]:
                    if t[1][2] < target[1][2]:
                        target = t

                # Apply damage
                dmg = elf_dmg if curr[3] == "e" else 3
                target[1] = (target[1][0], target[1][1], target[1][2]-dmg, target[1][3])
                if target[1][2] <= 0:
                    grid[target[1][0]][target[1][1]] = "."
                    if en == "G":
                        if target[0] < gi: gi -= 1
                        del goblins[target[0]]
                    else:
                        if target[0] < ei: ei -= 1
                        del elves[target[0]]
                        if not ignore_losses:
                            return 0
                else:
                    if en == "G":
                        goblins[target[0]] = target[1]
                    else:
                        elves[target[0]] = target[1]

            # Update indexes and unit in list
            if curr[3] == "e":
                elves[ei] = curr
                ei += 1
            else:
                goblins[gi] = curr
                gi += 1

    score = sum([hp for y, x, hp, t in elves + goblins]) * turn

    return score

# Function for solving the first problem
def first ():
    st = clock()
    res = solve()
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    dmg = 3
    res = False
    while not res:
        dmg += 1
        res = solve(dmg, False)
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
