from time import process_time as clock
from collections import deque

# Initialize the data
with open("20.txt") as f:
    regex = f.read().strip()[1:-1]

grid = [["#"] * 300 for i in range(300)]
direction = { "N":(0,-1), "E":(1,0), "S":(0,1), "W":(-1,0) }


def traverse (pos, path, i=0):
    init = pos
    while i < len(path):
        p = path[i]
        if p == "(":
            i = traverse(pos, path, i+1)
        elif p == ")":
            return i
        elif p == "|":
            pos = init
        else:
            d = direction[p]
            pos = (pos[0] + 2 * d[0], pos[1] + 2 * d[1])
            grid[pos[1] - d[1]][pos[0] - d[0]] = "-"
            grid[pos[1]][pos[0]] = "."
        i += 1


def bfs (y, x):
    # Open nodes
    op = deque([(y, x, 0)])
    # Vistited nodes in set for fast checks
    visited = set()
    # Count the rooms far away
    count = 0

    # Continue while there are still nodes
    while op:

        # Get first node
        current = op.pop()

        # Count rooms larger 1000 or more doors away
        if current[2] % 2 and (current[2] + 1) // 2 >= 1000:
            count += 1

        # We have now visited this node
        visited.add((current[0], current[1]))

        # Add new nodes to be vistited
        for pos in [(current[0] + 1, current[1], current[2] + 1),
                    (current[0] - 1, current[1], current[2] + 1),
                    (current[0], current[1] + 1, current[2] + 1),
                    (current[0], current[1] - 1, current[2] + 1)]:
            unit = grid[pos[0]][pos[1]]
            if ((pos[0], pos[1]) not in visited) and unit != "#":
                op.appendleft(pos)

    return current[2] // 2, count

def output ():
    data = "\n".join(["".join(i) for i in grid])
    with open("day20.out", "w") as f:
        f.write(data)

# Function for solving both problems
def solve ():
    st = clock()
    res = 0
    pos = (150, 150)
    traverse(pos, regex)
    grid[pos[1]][pos[0]] = "X"
    res1, res2 = djik(*pos)
    print("First:", res1, "Second:", res2, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    solve()
    #output()
