from time import process_time as clock

# Initialize the data
with open("23.txt") as f:
    data = [l.split(",") for l in f]
    nano = []
    for d in data:
        x = int(d[0][5:])
        y = int(d[1])
        z = int(d[2][:-1])
        r = int(d[3][3:])
        nano.append((x, y, z, r))

def dist (x1, y1, z1, x2, y2, z2):
    return abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)

# Function for solving the first problem
def first ():
    st = clock()
    max_r = 0
    max_pos = (0, 0, 0)
    for n in nano:
        if max_r < n[3]:
            max_r = n[3]
            max_pos = (n[0], n[1], n[2])
    res = 0
    for n in nano:
        if dist(*max_pos, n[0], n[1], n[2]) <= max_r:
            res += 1

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    max_connections = (0, (0,0,0))
    for x, y, z, r in nano:
        candidates = [
            # Nodes / pointy bits
            (x + r, y, z),
            (x, y + r, z),
            (x, y, z + r),
            (x - r, y, z),
            (x, y - r, z),
            (x, y, z - r),
        ]

        for p in candidates:
            c = 0
            for n1 in nano:
                if dist(*p, *n1[:3]) <= n1[3]:
                    c += 1
            if c > max_connections[0]:
                max_connections = (c, p)
            if c == max_connections[0]:
                if sum([abs(i) for i in p]) < sum([abs(i) for i in max_connections[1]]):
                    max_connections = (c, p)

    # Binary search for the point closest to (0, 0, 0) using one
    # point in the area with most nanobots within range.
    changed = True
    step = 80000000
    while changed:
        changed = False
        for xo in range(-1, 2):
            for yo in range(-1, 2):
                for zo in range(-1, 2):
                    p = max_connections[1]
                    p = tuple(pi + step * o for pi, o in zip(p, (xo, yo, zo)))

                    c = 0
                    for n1 in nano:
                        if dist(*p, *n1[:3]) <= n1[3]:
                            c += 1
                    if c > max_connections[0]:
                        max_connections = (c, p)
                        changed = True
                    if c == max_connections[0]:
                        if sum([abs(i) for i in p]) < sum([abs(i) for i in max_connections[1]]):
                            max_connections = (c, p)
                            changed = True

        if not changed and step > 1:
            step //= 2
            changed = True

    res = sum([abs(i) for i in max_connections[1]])

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
