from collections import defaultdict


def solve(input):
    parsed1 = [
        (int(l.split(": ")[0].split()[1]), l.split(": ")[1]) for l in input.split("\n")
    ]
    ans1 = 0
    ans2 = 0
    for n, l in parsed1:
        isOk = True
        m = defaultdict(int)
        for g in l.replace(";", ",").split(", "):
            count, color = g.split()
            m[color] = max(m[color], int(count))
            if color == "red" and int(count) > 12:
                isOk = False
            elif color == "green" and int(count) > 13:
                isOk = False
            elif color == "blue" and int(count) > 14:
                isOk = False
        if isOk:
            ans1 += n
        ans2 += m["red"] * m["green"] * m["blue"]

    return (str(ans1), str(ans2))
