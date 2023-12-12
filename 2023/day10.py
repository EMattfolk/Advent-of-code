from point import Point


def offset(c):
    match c:
        case "|":
            return (Point(0, 1), Point(0, -1))
        case "-":
            return (Point(1, 0), Point(-1, 0))
        case "L":
            return (Point(0, -1), Point(1, 0))
        case "J":
            return (Point(0, -1), Point(-1, 0))
        case "7":
            return (Point(0, 1), Point(-1, 0))
        case "F":
            return (Point(0, 1), Point(1, 0))
        case "F":
            return (Point(0, 1), Point(1, 0))
        # Hack
        case "S":
            return (Point(0, 1), Point(-1, 0))


def dir(d):
    return Point(-d.y, d.x)


def solve(input):
    input = [list(l) for l in input.split()]
    for y, l in enumerate(input):
        for x, c in enumerate(l):
            if c == "S":
                start = Point(x, y)
    loop = set()
    queue = [start]
    while queue:
        p = queue.pop()
        if p not in loop:
            loop.add(p)
            c = input[p.y][p.x]
            p1 = p + offset(c)[0]
            p2 = p + offset(c)[1]
            queue.append(p1)
            queue.append(p2)

    visited = loop.copy()

    ans1 = len(loop) // 2
    ans2 = 0
    for y, l in enumerate(input):
        state = "outside"
        for x, c in enumerate(l):
            # input[y][x] = " "
            if Point(x, y) in loop:
                if state == "outside":
                    if c == "|":
                        state = "inside"
                    elif c == "F":
                        state = "down"
                    elif c == "L":
                        state = "up"
                elif state == "inside":
                    if c == "|":
                        state = "outside"
                    elif c == "F":
                        state = "downi"
                    elif c == "L":
                        state = "upi"
                elif state == "up":
                    if c in ["7", "S"]:
                        state = "inside"
                    elif c == "J":
                        state = "outside"
                elif state == "down":
                    if c == "J":
                        state = "inside"
                    elif c in ["7", "S"]:
                        state = "outside"
                elif state == "upi":
                    if c in ["7", "S"]:
                        state = "outside"
                    elif c == "J":
                        state = "inside"
                elif state == "downi":
                    if c == "J":
                        state = "outside"
                    elif c in ["7", "S"]:
                        state = "inside"
            elif state == "inside":
                ans2 += 1

    # for i in loop:
    #    input[i.y][i.x] = "#"

    # for l in input:
    #    print("".join(l))

    return (str(ans1), str(ans2))
