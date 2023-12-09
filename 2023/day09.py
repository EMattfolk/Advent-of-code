from point import Point


def solve(input):
    parsed = [list(map(int, l.split())) for l in input.split("\n")]

    def extrapolate(l):
        lines = [l]
        while any(lines[-1]):
            l = lines[-1]
            res = []
            for i in range(len(l) - 1):
                res.append(l[1 + i] - l[i])
            lines.append(res)

        lines[-1] = [0] + lines[-1] + [0]
        for i in range(len(lines) - 1):
            lines[len(lines) - 2 - i].append(
                lines[len(lines) - 2 - i][-1] + lines[len(lines) - 1 - i][-1]
            )
            lines[len(lines) - 2 - i] = [
                lines[len(lines) - 2 - i][0] - lines[len(lines) - 1 - i][0]
            ] + lines[len(lines) - 2 - i]

        return Point(lines[0][-1], lines[0][0])

    # print(extrapolate(parsed[0]))
    ans = Point(0, 0)
    for i in parsed:
        ans += extrapolate(i)

    ans1 = ans.x
    ans2 = ans.y
    return (str(ans1), str(ans2))
