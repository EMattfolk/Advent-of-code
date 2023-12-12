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


def solve(input):
    input = input.split()
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

    def fill(x, y):
        p = Point(x, y)
        if p in visited:
            return set()

        failed = False
        v = {p}
        queue = [p]
        while queue:
            p = queue.pop()
            for o in [Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)]:
                np = o + p
                try:
                    input[np.y][np.x]
                    if np not in loop and np not in v:
                        queue.append(np)
                        v.add(np)
                except:
                    failed = True

        for p in v:
            visited.add(p)
        if failed:
            return set()
        else:
            return v

    ans1 = len(loop) // 2
    ans2 = 0
    for y, l in enumerate(input):
        for x, c in enumerate(l):
            ans2 += len(fill(x, y))

    return (str(ans1), str(ans2))
