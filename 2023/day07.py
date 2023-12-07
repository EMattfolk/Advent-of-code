import itertools


def ord_card(c):
    match c:
        case "A":
            return 13
        case "K":
            return 12
        case "Q":
            return 11
        case "J":
            return 10
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
    # High card
    if lengths == [1, 1, 1, 1, 1]:
        rank = 0
    # One pair
    elif lengths == [2, 1, 1, 1]:
        rank = 1
    # Two pair
    elif lengths == [2, 2, 1]:
        rank = 2
    # Three of a kind
    elif lengths == [3, 1, 1]:
        rank = 3
    # Full house
    elif lengths == [3, 2]:
        rank = 4
    # Four of a kind
    elif lengths == [4, 1]:
        rank = 5
    # Five of a kind
    elif lengths == [5]:
        rank = 6

    return (rank, tuple(map(ord_card, h)))


def ord_card2(c):
    match c:
        case "A":
            return 13
        case "K":
            return 12
        case "Q":
            return 11
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
        case "J":
            return 0


def ord_hand2(h):
    non_j = [c for c in h if c != "J"]
    j = len([c for c in h if c == "J"])
    groups = [list(i[1]) for i in itertools.groupby(sorted(non_j))]
    lengths = sorted(map(len, groups), reverse=True)
    if lengths == []:
        lengths = [0]
    lengths[0] += j
    # High card
    if lengths == [1, 1, 1, 1, 1]:
        rank = 0
    # One pair
    elif lengths == [2, 1, 1, 1]:
        rank = 1
    # Two pair
    elif lengths == [2, 2, 1]:
        rank = 2
    # Three of a kind
    elif lengths == [3, 1, 1]:
        rank = 3
    # Full house
    elif lengths == [3, 2]:
        rank = 4
    # Four of a kind
    elif lengths == [4, 1]:
        rank = 5
    # Five of a kind
    elif lengths == [5]:
        rank = 6

    return (rank, tuple(map(ord_card2, h)))


# print(ord_hand("aabbacoac"))


def solve(input):
    parsed = list(
        map(lambda x: (x[0], int(x[1])), (l.split() for l in input.split("\n")))
    )
    ans1 = 0
    for i, (_, bid) in enumerate(sorted(parsed, key=lambda x: ord_hand(x[0]))):
        ans1 += (i + 1) * bid

    ans2 = 0
    for i, (_, bid) in enumerate(sorted(parsed, key=lambda x: ord_hand2(x[0]))):
        ans2 += (i + 1) * bid

    return (str(ans1), str(ans2))
