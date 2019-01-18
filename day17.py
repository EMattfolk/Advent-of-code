from time import process_time as clock

# Initialize the data
with open("day17.in") as f:
    data = [tuple(i.split("=") for i in l.split(", ")) for l in f]
    clay = set()
    for d in data:
        if d[0][0] == "x":
            x = int(d[0][1])
            y0, y1 = [int(i) for i in d[1][1].split("..")]
            clay = clay.union({ (x, y) for y in range(y0, y1 + 1) })
        else:
            y = int(d[0][1])
            x0, x1 = [int(i) for i in d[1][1].split("..")]
            clay = clay.union({ (x, y) for x in range(x0, x1 + 1) })

clay_length = len(clay)
visited = set()

def print_section (x, y, size=50):
    grid = [[" "] * size for i in range(size)]
    offset = size//2
    for j in range(-offset, offset):
        for i in range(-offset, offset):
            coord = (x+i, y+j)
            if coord in clay:
                grid[j + offset][i + offset] = "#"
            elif coord in visited:
                grid[j + offset][i + offset] = "|"
            if (x, y) == coord:
                grid[j + offset][i + offset] = "*"
    print("\n".join(["".join(i) for i in grid]))

def output ():
    maxy, miny, maxx = -1000, 1000, -1000
    for x, y in clay:
        maxy = max(maxy, y)
        maxx = max(maxx, x)
        miny = min(miny, y)
    grid = [[" "] * maxx for i in range(maxy)]
    for j in range(maxy):
        for i in range(maxx):
            coord = (i, j)
            if coord in clay:
                grid[j][i] = "#"
            elif coord in visited:
                grid[j][i] = "|"
            if (x, y) == coord:
                grid[j][i] = "*"
    return grid

def write_out ():
    out = "\n".join(["".join(i) for i in output()])
    with open("day17.out", "w") as f:
        f.write(out)

# Function for solving the first problem
def first ():
    st = clock()

    maxy, miny, maxx = -1000, 1000, -1000
    for x, y in clay:
        maxy = max(maxy, y)
        maxx = max(maxx, x)
        miny = min(miny, y)

    starts = [ ((500, 0), 1) ]
    invalid = set()

    while True:

        settled = False

        last_turn = (0, 0)

        pos, v = starts[-1]

        prev_touch = True

        pot_new = False

        while pos[1] <= maxy:

            visited.add(pos)

            if (pos[0], pos[1] + 1) not in clay:
                pos = (pos[0], pos[1] + 1)
                prev_touch = False
                continue

            if prev_touch == False:
                prev_touch = True
                if not pot_new: 
                    pot_new = [(pos, v), (pos, -v)]
                    #print_section(*pos)
                    #input()

            if (pos, v) in invalid:
                pot_new = None
                break

            if (pos[0] + v, pos[1]) in clay:

                if last_turn[1] == pos[1]:
                    settled = True
                    for x in range(min(last_turn[0], pos[0]), max(last_turn[0], pos[0]) + 1):
                        clay.add((x, pos[1]))
                    break

                last_turn = pos
                v = -v
                continue

            pos = (pos[0] + v, pos[1])

        if not settled:
            invalid.add(starts.pop())
            if pot_new:
                for n in pot_new:
                    if n in invalid: continue
                    starts.append(n)

        if not starts:
            # Get what was missing for some reason
            grid = output()
            for j in range(1, maxy):
                for i in range(1, maxx-1):
                    coord = (i, j)
                    if grid[j][i] == "|" and grid[j-1][i] == "|":
                        if grid[j][i-1] == "|" and grid[j][i+1] == " ":
                            starts.append((coord, 1))
                        elif grid[j][i-1] == " " and grid[j][i+1] == "|":
                            starts.append((coord, -1))
            if not starts:
                break

    res = len([i for i in visited if i[1] >= miny])
    print("First:", res, "Time:", clock() - st)
    output()

# Function for solving the second problem
def second ():
    st = clock()
    res = len(clay) - clay_length
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
write_out()
