from time import process_time as clock

# Initialize the data
with open("day16.in") as f:
    f = [l for l in f]
    data_first = []
    data_second = []
    i = 0
    while i < len(f):
        if f[i][0] == "B":
            temp = [] # Change to tuples?
            temp.append([int(f[i][n]) for n in [9, 12, 15, 18]])
            i += 1
            temp.append([int(n) for n in f[i].split()])
            i += 1
            temp.append([int(f[i][n]) for n in [9, 12, 15, 18]])
            i += 2
            data_first.append(temp)
        else:
            data_second.append([int(n) for n in f[i].split()])
            i += 1

            
def addr (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] + new[b]
    return new

def addi (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] + b
    return new

def mulr (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] * new[b]
    return new

def muli (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] * b
    return new

def banr (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] & new[b]
    return new

def bani (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] & b
    return new

def borr (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] | new[b]
    return new

def bori (reg, a, b, c):
    new = reg[:]
    new[c] = new[a] | b
    return new

def setr (reg, a, b, c):
    new = reg[:]
    new[c] = new[a]
    return new

def seti (reg, a, b, c):
    new = reg[:]
    new[c] = a
    return new

def gtir (reg, a, b, c):
    new = reg[:]
    new[c] = int(a > new[b])
    return new

def gtri (reg, a, b, c):
    new = reg[:]
    new[c] = int(new[a] > b)
    return new

def gtrr (reg, a, b, c):
    new = reg[:]
    new[c] = int(new[a] > new[b])
    return new

def eqir (reg, a, b, c):
    new = reg[:]
    new[c] = int(a == new[b])
    return new

def eqri (reg, a, b, c):
    new = reg[:]
    new[c] = int(new[a] == b)
    return new

def eqrr (reg, a, b, c):
    new = reg[:]
    new[c] = int(new[a] == new[b])
    return new

instruction = [None] * 16
instructions = [addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr]

# Function for solving the first problem
def first ():
    st = clock()
    valids = []
    to_remove = set()
    res = 0

    for bef, inp, out in data_first:
        valid = []
        for instr in instructions:
            if instr(bef, inp[1], inp[2], inp[3]) == out:
                valid.append(instr)
        if len(valid) > 1:
            if len(valid) >= 3:
                res += 1
            valids.append((inp[0], valid))
        elif len(valid) == 1:
            instruction[inp[0]] = valid[0]
            to_remove.add(valid[0])

    while to_remove:
        new_remove = set()
        for i in range(len(valids) - 1, -1, -1):
            deleted = False
            for j in range(len(valids[i][1]) - 1, -1, -1):
                if valids[i][1][j] in to_remove:
                    if valids[i][0] == instruction.index(valids[i][1][j]):
                        del valids[i]
                        deleted = True
                        break
                    else:
                        del valids[i][1][j]

            if not deleted:
                if len(valids[i][1]) == 1:
                    instruction[valids[i][0]] = valids[i][1][0]
                    new_remove.add(valids[i][1][0])
                    del valids[i]

        to_remove = new_remove

    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    reg = [0, 0, 0, 0]
    for inp in data_second:
        reg = instruction[inp[0]](reg, inp[1], inp[2], inp[3])
    res = reg[0]
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
