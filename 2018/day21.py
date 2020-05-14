from time import process_time as clock

def addr (reg, a, b, c):
    reg[c] = reg[a] + reg[b]

def addi (reg, a, b, c):
    reg[c] = reg[a] + b

def mulr (reg, a, b, c):
    reg[c] = reg[a] * reg[b]

def muli (reg, a, b, c):
    reg[c] = reg[a] * b

def banr (reg, a, b, c):
    reg[c] = reg[a] & reg[b]

def bani (reg, a, b, c):
    reg[c] = reg[a] & b

def borr (reg, a, b, c):
    reg[c] = reg[a] | reg[b]

def bori (reg, a, b, c):
    reg[c] = reg[a] | b

def setr (reg, a, b, c):
    reg[c] = reg[a]

def seti (reg, a, b, c):
    reg[c] = a

def gtir (reg, a, b, c):
    reg[c] = int(a > reg[b])

def gtri (reg, a, b, c):
    reg[c] = int(reg[a] > b)

def gtrr (reg, a, b, c):
    reg[c] = int(reg[a] > reg[b])

def eqir (reg, a, b, c):
    reg[c] = int(a == reg[b])

def eqri (reg, a, b, c):
    reg[c] = int(reg[a] == b)

def eqrr (reg, a, b, c):
    reg[c] = int(reg[a] == reg[b])

instruction_names = ["addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"]
instructions = [addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr]

# Initialize the data
with open("21.txt") as f:
    data = [l.strip() for l in f]
    instr_reg = int(data[0][-1])
    instr_list = [(instruction_names.index(l.split()[0]),) + tuple(int(n) for n in l.split()[1:]) for l in data[1:]]

# Function for solving the first problem
def first ():
    st = clock()
    a, b, c, d, e, f = [0] * 6

    d = 65536 | e
    e = 12670166

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
        e = 12670166

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
