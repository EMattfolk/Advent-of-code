from time import process_time as clock

# Initialize the data
with open("25.txt") as f:
    points = { tuple(int(i) for i in l.split(",")): False for l in f }

adjacent_offsets = []
for x in range(-3, 4):
    ax = abs(x)
    for y in range(-3+ax, 4-ax):
        ay = ax + abs(y)
        for z in range(-3+ay, 4-ay):
            az = ay + abs(z)
            for w in range(-3+az, 4-az):
                adjacent_offsets.append((x, y, z, w))


def dist (coord1, coord2):
    return sum([abs(i-j) for i, j in zip(coord1, coord2)])

def is_connected (const1, const2):
    for coord1 in const1:
        for coord2 in const2:
            if dist(coord1, coord2) <= 3:
                return True
    return False


def discover(points, point):
    if points[point]:
        return

    points[point] = True

    for offsets in adjacent_offsets:
        p = tuple(pi + o for pi, o in zip(point, offsets))
        if p in points:
            discover(points, p)


# Function for solving the first problem
def first ():
    st = clock()

    res = 0
    for point in points:
        if not points[point]:
            discover(points, point)
            res += 1

    print("First:", res, "Time:", clock() - st)

# Dummy
def second():
    pass

# Solve the problems
if __name__ == "__main__":
    first()
