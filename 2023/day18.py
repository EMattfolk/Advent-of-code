from point import Point


def solve(input):
    input = [l.split() for l in input.split("\n")]
    ans2 = 0

    p = Point(0, 0)
    hole = {p}
    for [c, dist, color] in input:
        if c == "U":
            dir = Point(0, -1)
        elif c == "R":
            dir = Point(1, 0)
        elif c == "D":
            dir = Point(0, 1)
        elif c == "L":
            dir = Point(-1, 0)

        for _ in range(int(dist)):
            p += dir
            hole.add(p)

    xs = [p.x for p in hole]
    ys = [p.y for p in hole]
    min_x, max_x = min(xs), max(xs)
    min_y, max_y = min(ys), max(ys)
    print(len(hole))
    print(min_x, max_x)
    print(min_y, max_y)

    visited = hole.copy()
    for x in range(min_x, max_x + 1):
        for y in range(min_x, max_x + 1):
            inside = True
            fill = set()
            queue = [Point(x, y)]
            while queue:
                p = queue.pop()

                if p in visited:
                    continue

                visited.add(p)
                fill.add(p)

                if p.y < min_y or max_y < p.y or p.x < min_x or max_x < p.x:
                    inside = False
                    continue

                for o in [Point(0, -1), Point(1, 0), Point(0, 1), Point(-1, 0)]:
                    queue.append(p + o)

            if inside:
                hole |= fill

    ans1 = len(hole)

    return (str(ans1), str(ans2))
