from time import process_time as clock

"""

This problem has different registers depending on the solver.
Only 3 registers has to be changed for any specific user.

0 1 2 3 4 5
a b c d e f

Start:
set b to 0
set e to 0

Loop1:
set d to 65536 | e
set e to 12670166
Loop2:
set c to d & 255
add c to e
set e to e & 16777215
mul 65899 to e
set e to e & 16777215

if 256 > d:
    if e == a:
        break
    goto Loop1
else:
    set d to d // 256
    goto Loop2







    set c to 0
    Loop3:
    set f to c+1
    mul f by 256
    if f > d:
        set d to c
        goto Loop2
    else:
        add 1 to c
        goto Loop3
"""

# Initialize the data
# Not the most robust solution, but should work in most cases
with open("21.txt") as f:
    initial_value = max(int(l.split()[1]) for l in f)

# Function for solving the first problem
def first ():
    st = clock()
    a, b, c, d, e, f = [0] * 6

    d = 65536 | e
    e = initial_value

    while True:

        c = 255 & d
        e += c
        e *= 65899
        e &= 16777215

        if 256 > d:
            break
        else:
            d //= 256

    res = e

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    a, b, c, d, e, f = [0] * 6

    found = set()

    while True:

        d = 65536 | e
        e = initial_value

        while True:

            c = 255 & d
            e += c
            e *= 65899
            e &= 16777215

            if 256 > d:
                break
            else:
                d //= 256

        if e not in found:
            found.add(e)
            res = e
        else:
            break

    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
