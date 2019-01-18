from time import process_time as clock

# Initialize the data
with open("day04.in") as f:
    data = [l.split() for l in f]
    for d in data:
        date = d[0]
        time = d[1]
        del d[1]
        d[0] = tuple(int(i) for i in date[1:].split("-")) + tuple(int(i) for i in time[:-1].split(":"))
        if d[1][0] == "G":
            del d[1]
            del d[2]
            del d[2]
        else:
            d[1] = d[1][0]
            del d[2]
    data.sort()
    for i, d in enumerate(data):
        data[i] = (d[0][3], d[0][4], d[1])

    guards = {}

# Function for solving the first problem
def first ():
    st = clock()

    minute = [0]*60
    i = 0
    while i < len(data):
        label = data[i][2]
        if label[0] == "#":
            if label not in guards:
                guards[label] = minute.copy()
            cur_guard = label
        elif label == "f":
            sta = data[i][1]
            i += 1
            end = data[i][1]
            for j in range(sta, end):
                guards[cur_guard][j] += 1

        i += 1

    m = (0,"#0")
    for k in guards:
        s = sum(guards[k])
        if s > m[0]:
            m = (s, k)

    res = guards[m[1]].index(max(guards[m[1]])) * int(m[1][1:])

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()

    m = (0,"#0")
    for k in guards:
        s = max(guards[k])
        if s > m[0]:
            m = (s, k)

    res = guards[m[1]].index(m[0]) * int(m[1][1:])

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
