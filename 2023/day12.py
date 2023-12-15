from functools import lru_cache


@lru_cache(None)
def matches(row, pattern):
    if row == "":
        return 1 if pattern == () else 0
    if sum(pattern) + len(pattern) - 1 > len(row):
        return 0
    if row.startswith("."):
        return matches(row[1:], pattern)
    elif row.startswith("?"):
        return matches(row[1:], pattern) + matches("#" + row[1:], pattern)
    elif row.startswith("#"):
        if len(pattern) == 0:
            return 0
        p = pattern[0]
        if len(row) < p:
            return 0
        if "." in row[:p]:
            return 0
        if len(row) != p and row[p] == "#":
            return 0
        return matches(row[p + 1 :], pattern[1:])

    assert False


def solve(input):
    input = input.split()
    parsed = []
    for i in range(0, len(input), 2):
        parsed.append((input[i], tuple(map(int, input[i + 1].split(",")))))

    folded = [("?".join([row] * 5), pattern * 5) for row, pattern in parsed]

    # print(parsed)
    ans1 = sum(matches(*i) for i in parsed)
    ans2 = sum(matches(*i) for i in folded)
    return (str(ans1), str(ans2))
