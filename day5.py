from time import process_time as clock

# Initialize the data
with open("day5.in") as f:
    data = list(f.read().strip())
backup = []
x = [i for i in range(len(data))]
# Function for solving the first problem
def first ():
    st = clock()
    i = 0
    res = len(data)
    while i < len(data) - 1:
        if data[x[i]].upper() == data[x[i+1]].upper() and data[x[i+1]] != data[x[i]]:
            x[i] = x[x[i]-1]
            x[i+1] = x[x[i+1]+1]
            res -= 2
        else:
            temp = i
            i = x[i+1]
            x[i-1] = x[temp]

    global backup
    backup = data.copy()
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    res = len(backup)
    for letter in "abcdefghijklmnopqrstuvwxyz":
        data = [i for i in backup.copy() if i.lower() != letter]
        i = 0
        while i < len(data) - 1:
            if data[i].upper() == data[i+1].upper() and data[i+1] != data[i]:
                del data[i]
                del data[i]
                i -= 1
            else:
                i += 1
        res = min(len(data), res)

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
