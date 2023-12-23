from point import Point


def negate(dir):
    if dir == "R":
        return "L"
    elif dir == "L":
        return "R"
    elif dir == "U":
        return "D"
    elif dir == "D":
        return "U"


def step(p, dir, next_dir):
    # if (p[1] == dir and p[0] == next_dir) or (
    #    p[1] == negate(dir) and p[0] == negate(next_dir)
    # ):
    #    return p[0] + negate(p[1])
    # if (p[0] == dir and p[1] == next_dir) or (
    #    p[0] == negate(dir) and p[1] == negate(next_dir)
    # ):
    #    return negate(p[0]) + p[1]

    match [p, dir, next_dir]:
        # R
        # Inner
        case ["UR", "R", "U"]:
            return "UL"
        case ["DR", "R", "D"]:
            return "DL"
        # Outer
        case ["UL", "R", "D"]:
            return "UR"
        case ["DL", "R", "U"]:
            return "DR"

        # L
        # Inner
        case ["UL", "L", "U"]:
            return "UR"
        case ["DL", "L", "D"]:
            return "DR"
        # Outer
        case ["UR", "L", "D"]:
            return "UL"
        case ["DR", "L", "U"]:
            return "DL"

        # U
        # Inner
        case ["UR", "U", "R"]:
            return "DR"
        case ["UL", "U", "L"]:
            return "DL"
        # Outer
        case ["DR", "U", "L"]:
            return "UR"
        case ["DL", "U", "R"]:
            return "UL"

        # D
        # Inner
        case ["DR", "D", "R"]:
            return "UR"
        case ["DL", "D", "L"]:
            return "UL"
        # Outer
        case ["UR", "D", "L"]:
            return "DR"
        case ["UL", "D", "R"]:
            return "DL"

    return p


def dir_value(c):
    if c == "U":
        return Point(0, 0)
    elif c == "D":
        return Point(0, 1)
    elif c == "L":
        return Point(0, 0)
    elif c == "R":
        return Point(1, 0)


def transition(state, new_state):
    return (
        dir_value(new_state[0])
        + dir_value(new_state[1])
        - dir_value(state[0])
        - dir_value(state[1])
    )


def solve(input):
    input = [l.split() for l in input.split("\n")]

    def solve(steps):
        next = [steps[(i + 1) % len(steps)][0] for i in range(len(steps))]

        p = Point(0, 0)
        hole = [p]
        state = "UL"
        # print(state, p)
        for [c, dist], n in zip(steps, next):
            if c == "U":
                dir = Point(0, -1)
            elif c == "R":
                dir = Point(1, 0)
            elif c == "D":
                dir = Point(0, 1)
            elif c == "L":
                dir = Point(-1, 0)

            new_state = step(state, c, n)
            p += transition(state, new_state)
            state = new_state

            p += dir.scale(int(dist))
            hole.append(p)

            # print(state, p)

        ans = 0
        for i in range(len(hole)):
            ans += (
                hole[i].x * hole[(i + 1) % len(hole)].y
                - hole[(i + 1) % len(hole)].x * hole[i].y
            )
        ans //= 2
        return ans

    ans1 = solve([[a, b] for [a, b, _] in input])
    ans2 = solve(
        [["RDLU"[int(color[-2])], int(color[2:-2], 16)] for [_, _, color] in input]
    )

    return (str(ans1), str(ans2))
