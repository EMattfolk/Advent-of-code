from time import process_time as clock

# Initialize the data
with open("18.txt") as f:
    grid = [list(l.strip()) for l in f]

size = 50
goal = 1000000000
grid_set = set()
grids = []

def get_adj(x, y):
    x_vals = { x - 1, x, x + 1 } - { -1, size }
    y_vals = { y - 1, y, y + 1 } - { -1, size }
    l = []
    for j in y_vals:
        for i in x_vals:
            if i == x and j == y: continue
            l.append(grid[j][i])
    return l

def grid_str ():
    flat_grid = []
    for l in grid: flat_grid += l
    return "".join(flat_grid)
    
st = clock()
s = grid_str()
while s not in grid_set:

    grid_set.add(s)
    grids.append(s)

    new_grid = [[] for i in range(size)]
    for x in range(size):
        for y in range(size):
            adj = get_adj(x, y)
            new = grid[y][x]
            if new == "." and adj.count("|") >= 3: new = "|"
            elif new == "|" and adj.count("#") >= 3: new = "#" 
            elif new == "#" and (adj.count("#") < 1 or adj.count("|") < 1): new = "." 
            new_grid[y].append(new)

    grid = new_grid
    s = grid_str()

offset = grids.index(s)
cycle_index = (goal - offset) % (len(grids) - offset)

res1 = grids[10].count("#") * grids[10].count("|")
res2 = grids[offset + cycle_index].count("#") * grids[offset + cycle_index].count("|")

print("First:", res1, "Second:", res2, "Time:", clock() - st)
