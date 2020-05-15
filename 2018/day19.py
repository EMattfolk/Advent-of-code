from time import process_time as clock

"""
0  1  2  3  4  5
a  b  c  d  e  f

add 16 to c
set e to 834
add 1 to f
mul f by 22
add 17 to f
add f to e
add a to c
set c to 0
set b to 1
set d to 1
set f to b * d <------
if f != e:           |
add 1 to d           |
if d <= w:           |
goto ----------------|
"""

# This may change with input
RESULT_REG = 3

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
with open("19.txt") as f:
    data = [l.strip() for l in f]
    instr_reg = int(data[0][-1])
    instr_list = [(instruction_names.index(l.split()[0]),) + tuple(int(n) for n in l.split()[1:]) for l in data[1:]]

def factor (n):

    if n == 0:
        return []

    l = []
    c = 0
    while not n % 2:
        c += 1
        n //= 2
    if c: l.append((2, c))
    i = 3
    while i*i <= n:
        c = 0
        while not n % i:
            c += 1
            n //= i
        if c: l.append((i, c))
        i += 2
    if n != 1: l.append((n, 1))
    return l

def div_sum (factors, i=0, n=1):
    if i == len(factors):
        return n
    s = 0
    f, c = factors[i]
    for e in range(c + 1):
        s += div_sum(factors, i+1, n)
        n *= f
    return s

def solve (reg):
    for i in range(20):
        instr = instr_list[reg[instr_reg]]
        instructions[instr[0]](reg, instr[1], instr[2], instr[3])
        reg[instr_reg] += 1

    return div_sum(factor(reg[RESULT_REG]))

# Function for solving the first problem
def first ():
    st = clock()
    res = solve([0] * 6)
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    res = solve([1] + [0] * 5)
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
