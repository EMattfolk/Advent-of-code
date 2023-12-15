from point import Point


def solve(input):
    input = input.split("\n")

    expand_col = set()
    for x, col in enumerate(zip(*input)):
        if all(c == "." for c in col):
            expand_col.add(x)

    expand_row = set()
    for y, row in enumerate(input):
        if all(c == "." for c in row):
            expand_row.add(y)

    def solve(dist):
        points = []
        actual_y = 0
        for y, l in enumerate(input):
            actual_x = 0
            for x, c in enumerate(l):
                if c == "#":
                    points.append(Point(actual_x, actual_y))

                actual_x += dist if x in expand_col else 1
            actual_y += dist if y in expand_row else 1

        return sum(
            abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y)
            for i in range(len(points))
            for j in range(i + 1, len(points))
        )

    ans1 = solve(2)
    ans2 = solve(1000000)

    return (str(ans1), str(ans2))
