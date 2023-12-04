from functools import lru_cache


def solve(input):
    parsed = []
    for l in input.split("\n"):
        [a, b] = l.split(": ")[1].split(" | ")
        parsed.append(len(set(a.split()).intersection(set(b.split()))))

    cards = [1] * len(parsed)

    ans1 = 0
    for i, won in enumerate(parsed):
        if won:
            ans1 += 2 ** (won - 1)
        for j in range(won):
            cards[i + j + 1] += cards[i]

    ans2 = sum(cards)

    return (str(ans1), str(ans2))
