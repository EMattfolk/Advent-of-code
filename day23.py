from time import process_time as clock

# Initialize the data
with open("day23.in") as f:
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
    for n in nano:#(n[0] + n[3], n[1], n[2]), (n[0], n[1] + n[3], n[2]), (n[0], n[1], n[2] + n[3]), (n[0] - n[3], n[1], n[2]), (n[0], n[1] - n[3], n[2]), (n[0], n[1], n[2] - n[3])
        for p in [(n[0] + n[3]//2, n[1] + n[3]//2, n[2]), (n[0] + n[3]//2, n[1], n[2] + n[3]//2), (n[0], n[1] + n[3]//2, n[2] + n[3]//2), ]:
            c = 0
            for n1 in nano:
                if dist(*p, *n1[:3]) <= n1[3]:
                    c += 1
            if c > max_connections[0]:
                max_connections = (c, p)
            if c == max_connections[0]:
                if sum([abs(i) for i in p]) < sum([abs(i) for i in max_connections[1]]):
                    max_connections = (c, p)

    res = sum([abs(i) for i in max_connections[1]])

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
