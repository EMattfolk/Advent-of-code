import itertools


def lengths_to_rank(lengths):
    match lengths:
        # High card
        case [1, 1, 1, 1, 1]:
            return 0
        # One pair
        case [2, 1, 1, 1]:
            return 1
        # Two pair
        case [2, 2, 1]:
            return 2
        # Three of a kind
        case [3, 1, 1]:
            return 3
        # Full house
        case [3, 2]:
            return 4
        # Four of a kind
        case [4, 1]:
            return 5
        # Five of a kind
        case [5]:
            return 6


def ord_card(c, j):
    match c:
        case "A":
            return 13
        case "K":
            return 12
        case "Q":
            return 11
        case "J":
            return j
        case "T":
            return 9
        case "9":
            return 8
        case "8":
            return 7
        case "7":
            return 6
        case "6":
            return 5
        case "5":
            return 4
        case "4":
            return 3
        case "3":
            return 2
        case "2":
            return 1


def ord_hand(h):
    groups = [list(i[1]) for i in itertools.groupby(sorted(h))]
    lengths = sorted(map(len, groups), reverse=True)

    return (lengths_to_rank(lengths), tuple(map(lambda c: ord_card(c, 10), h)))


def ord_hand2(h):
    non_j = [c for c in h if c != "J"]
    j = len([c for c in h if c == "J"])
    groups = [list(i[1]) for i in itertools.groupby(sorted(non_j))]
    lengths = sorted(map(len, groups), reverse=True)
    if lengths == []:
        lengths = [0]
    lengths[0] += j

    return (lengths_to_rank(lengths), tuple(map(lambda c: ord_card(c, 0), h)))


# print(ord_hand("aabbacoac"))


def solve(input):
    parsed = list(
        map(lambda x: (x[0], int(x[1])), (l.split() for l in input.split("\n")))
    )

    def s(ord):
        return sum(
            (i + 1) * bid
            for i, (_, bid) in enumerate(sorted(parsed, key=lambda x: ord(x[0])))
        )

    ans1 = s(ord_hand)
    ans2 = s(ord_hand2)

    return (str(ans1), str(ans2))
