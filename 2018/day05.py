from time import process_time as clock

# Initialize the data
with open("05.txt") as f:
    data = list(f.read().strip())

backup = data.copy()

# Function for solving the first problem
def first (silent=False, data=data):
    st = clock()
    i = 0
    res = len(data)
    old_res = 0
    while old_res != res:
        old_res = res

        for i in range(len(data) - 2, -1, -1):
            j = i + 1

            if j >= len(data):
                continue

            if data[i].lower() == data[j].lower() and data[i] != data[j]:
                del data[i]
                del data[i]

        res = len(data)

    if not silent:
        print("First:", res, "Time:", clock() - st)
    else:
        return res

# Function for solving the second problem
def second ():
    st = clock()
    res = len(backup)
    for letter in "abcdefghijklmnopqrstuvwxyz":
        data = [i for i in backup.copy() if i.lower() != letter]
        res = min(res, first(silent=True, data=data))

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
