from time import process_time as clock

# Initialize the data
with open("25.txt") as f:
    points = [tuple(int(i) for i in l.split(",")) for l in f]

def dist (coord1, coord2):
    return sum([abs(i-j) for i, j in zip(coord1, coord2)])

def is_connected (const1, const2):
    for coord1 in const1:
        for coord2 in const2:
            if dist(coord1, coord2) <= 3:
                return True
    return False


# Function for solving the first problem
def first ():
    st = clock()
    constellations = []
    for p in points:
        found = False
        for const in constellations:
            for coord in const:
                if dist(coord, p) <= 3:
                    const.append(p)
                    found = True
                    break
            if found:
                break
        if not found:
            constellations.append([p])

    found = True
    while found:
        found = False
        for i, const1 in enumerate(constellations):
            connections = []
            for j, const2 in enumerate(constellations[i+1:]):
                if is_connected(const1, const2):
                    connections.append(i+j+1)
                    found = True
            if found:
                for r in reversed(connections):
                    const1 += constellations[r]
                    del constellations[r]
                break

    res = len(constellations)

    print("First:", res, "Time:", clock() - st)

# Dummy
def second():
    pass

# Solve the problems
if __name__ == "__main__":
    first()
