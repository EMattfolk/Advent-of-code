from time import process_time as clock

# Initialize the data
with open("12.txt") as f:
    data = [i.split() for i in f]
cells = list(data[0][2])
transforms = { i:j for i,j in zip([a[0] for a in data[2:]], [a[2] for a in data[2:]]) }

def solve (generations):

    cur_cells = cells.copy()
    cur_cells = list("." * 10) + cur_cells + list("." * 900)

    old_state = ""

    for gen in range(generations):

        new_cells = cur_cells.copy() + ["."]
        current = "".join(cur_cells[:5])

        for i in range(2, len(cur_cells) - 3):
            if current in transforms:
                new_cells[i] = transforms[current]
            current = current[1:] + cur_cells[i+3]
        cur_cells = new_cells

        state = "".join(cur_cells).lstrip(".").rstrip(".")
        changed, old_state = state != old_state, state

        if not changed: break

    offset = -10
    res = 0

    if not changed: offset += generations - gen - 1

    for i, pot in enumerate(cur_cells):
        if cur_cells[i] == "#":
            res += i + offset

    return res


# Function for solving the first problem
def first ():
    st = clock()
    res = solve(20)
    print("First:", res, "Time:", clock() - st, flush=True)

# Function for solving the second problem
def second ():
    st = clock()
    res = solve(50000000000)
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
