from time import process_time as clock

def dist (x1,y1,x2,y2):
    return abs(x1-x2)+abs(y1-y2)
def closest (x,y,l):
    close = [(dist(x,y,*l[0]), l[0])]
    for c in l[1:]:
        if dist(x,y,*c) == close[0][0]:
            close.append((dist(x,y,*c), c))
        elif dist(x,y,*c) < close[0][0]:
            close = [(dist(x,y,*c), c)]
    return close
def distsum(x,y,l):
    return sum([dist(x,y,*i) for i in l])

# Initialize the data
with open("day06.in") as f:
    data = [(int(i), int(j)) for i,j in [l.split(", ") for l in f]] 
minx, miny = 1000, 1000
maxx, maxy = 0, 0
for x,y in data:
    minx = min(minx, x)
    miny = min(miny, y)
    maxx = max(maxx, x)
    maxy = max(maxy, y)
maxx -= minx
maxy -= miny
for i in range(len(data)):
    data[i] = (data[i][0] - minx, data[i][1] - miny)

# Function for solving the first problem
def first ():
    st = clock()
    
    scores = {i:0 for i in data}

    invalid = set()
    for i in range(-1,maxx+1):
        c = closest(i,-1,data)
        if len(c) == 1:
            invalid.add(c[0][1])
        c = closest(i,maxy,data)
        if len(c) == 1:
            invalid.add(c[0][1])
    for i in range(-1,maxy+1):
        c = closest(-1,i,data)
        if len(c) == 1:
            invalid.add(c[0][1])
        c = closest(maxx,i,data)
        if len(c) == 1:
            invalid.add(c[0][1])

    for x in range(maxx):
        for y in range(maxy):
            c = closest(x,y,data)
            if len(c) == 1:
                scores[c[0][1]] += 1

    res = max([scores[i] for i in scores if i not in invalid])
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    res = 0
    thresh = 10000
    xi, xe = 0, maxx
    yi, ye = 0, maxy
    for x in range(xi, xe):
        for y in range(yi, ye):
            if distsum(x,y,data) < thresh:
                res += 1
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
first()
second()
