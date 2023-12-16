from copy import deepcopy


def part1(rocks):
    rocks = list(map(list, zip(*rocks)))
    for l in rocks:
        empty = 0
        for i in range(len(l)):
            if l[i] == "O":
                l[i] = "."
                l[empty] = "O"
                empty += 1
            elif l[i] == "#":
                empty = i + 1
    rocks = list(map(list, zip(*rocks)))
    return rocks


def cycle(rocks):
    rocks = list(map(list, zip(*rocks)))
    for l in rocks:
        empty = 0
        for i in range(len(l)):
            if l[i] == "O":
                l[i] = "."
                l[empty] = "O"
                empty += 1
            elif l[i] == "#":
                empty = i + 1
    rocks = list(map(list, zip(*rocks)))
    for l in rocks:
        empty = 0
        for i in range(len(l)):
            if l[i] == "O":
                l[i] = "."
                l[empty] = "O"
                empty += 1
            elif l[i] == "#":
                empty = i + 1
    rocks = list(map(list, zip(*rocks)))
    for l in rocks:
        empty = len(l) - 1
        for i in range(len(l) - 1, -1, -1):
            if l[i] == "O":
                l[i] = "."
                l[empty] = "O"
                empty -= 1
            elif l[i] == "#":
                empty = i - 1
    rocks = list(map(list, zip(*rocks)))
    for l in rocks:
        empty = len(l) - 1
        for i in range(len(l) - 1, -1, -1):
            if l[i] == "O":
                l[i] = "."
                l[empty] = "O"
                empty -= 1
            elif l[i] == "#":
                empty = i - 1
    return rocks


def part2(rocks):
    seen = {}
    repr = tuple(map(tuple, rocks))
    i = 0
    while repr not in seen:
        seen[repr] = i
        rocks = cycle(rocks)
        repr = tuple(map(tuple, rocks))
        i += 1

    start = seen[repr]
    cycle_length = i - seen[repr]
    for _ in range((1000000000 - start) % cycle_length):
        rocks = cycle(rocks)

    return rocks


def score(rocks):
    return sum(i + 1 for i, l in enumerate(reversed(rocks)) for c in l if c == "O")


def solve(input):
    parsed = list(map(list, input.split("\n")))
    ans1 = score(part1(parsed))
    # for l in cycle(cycle(cycle(parsed))):
    #     print("".join(l))
    ans2 = score(part2(parsed))
    return (str(ans1), str(ans2))
