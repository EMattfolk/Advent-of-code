from time import process_time as clock

# Initialize the data
with open("02.txt") as f:
    data = [l.strip() for l in f]

# Function for solving the first problem
def first ():
    st = clock()
    two = 0
    three = 0
    for line in data:
        two_found = False
        three_found = False
        letters = {}
        for char in line:
            if char not in letters:
                letters[char] = 1
            else:
                letters[char] += 1
        for key in letters:
            if letters[key] == 2:
                two_found = True
            elif letters[key] == 3:
                three_found = True
        if three_found: three += 1
        if two_found: two += 1

    res = three * two

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    for i, base in enumerate(data):
        found = False
        for cand in data[i+1:]:
            error = None
            for index in range(len(cand)):
                if base[index] != cand[index]:
                    if error:
                        error = None
                        break
                    else:
                        error = (index,)
            if error:
                found = True
                break
        if found:
            res = base[:error[0]] + base[error[0] + 1:]
            break

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
