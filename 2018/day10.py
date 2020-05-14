from time import process_time as clock

# Initialize data
positions = []
velocities = []
with open("10.txt") as f:
    for line in f:
        line = line.split(", ")
        pos = (int(line[0][-6:]), int(line[1][:6]))
        vel = (int(line[1][-2:]), int(line[2][:2]))
        positions.append(pos)
        velocities.append(vel)

# Function for solving both problems
def both ():
    global positions

    st = clock()
    min_y, max_y = -10, 10
    sec = 0
    while max_y - min_y > 10: # The height of the message is 10
        min_y, max_y = positions[0][1], positions[0][1]
        min_x, max_x = positions[0][0], positions[0][0]
        for i in range(len(positions)):
            x, y = positions[i]
            x, y = x + velocities[i][0], y + velocities[i][1]
            positions[i] = (x, y)
            min_y = min(min_y, y)
            max_y = max(max_y, y)
            min_x = min(min_x, x)
            max_x = max(max_x, x)

        sec += 1

    positions = set(positions)
    res = "\n"
    for y in range(min_y, max_y):
        for x in range(min_x, max_x + 1):
            if (x, y) in positions:
                res += "#"
            else:
                res += "."
        res += "\n"

    print("First:", res, "Time:", clock() - st)
    print("Second:", sec, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    both()
