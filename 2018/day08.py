from time import process_time as clock

# Initialize the data
with open("day08.in") as f:
    data = [int(i) for i in f.read().strip().split()]

def traverse1 (l):
    length = 0
    score = 0
    if l[0] == 0:
        return sum(l[2:2+l[1]]), 2 + l[1]
    
    for i in range(l[0]):
        res = traverse1(l[2+length:])
        score += res[0]
        length += res[1]

    return score + sum(l[2+length:2+length+l[1]]), 2 + length + l[1]

def traverse2 (l):
    length = 0
    scores = []
    if l[0] == 0:
        return sum(l[2:2+l[1]]), 2 + l[1]

    for i in range(l[0]):
        res = traverse2(l[2+length:])
        scores.append(res[0])
        length += res[1]

    indexes = [ i-1 for i in l[2+length:2+length+l[1]] ]
    score = 0
    for i in indexes:
        if i < l[0]:
            score += scores[i]

    return score, 2 + length + l[1]

# Function for solving the first problem
def first ():
    st = clock()
    res = traverse1(data)[0]
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    res = traverse2(data)[0]
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
