import re


def overlap(first, second):
    (a, b) = first
    (c, d) = second
    if c <= a and b <= d:
        return ([], [(a, b)])
    elif b < c or a > d:
        return ([(a, b)], [])
    elif a <= c and d <= b:
        non = []
        if a != c:
            non.append((a, c - 1))
        if d != b:
            non.append((d + 1, b))
        return (non, [(c, d)])
    elif a <= c and c <= b and b <= d:
        non = []
        if a != c:
            non.append((a, c - 1))
        return (non, [(c, b)])
    elif c <= a and a <= d and d <= b:
        non = []
        if d != b:
            non.append((d + 1, b))
        return (non, [(a, d)])
    else:
        assert False


# print(overlap((4, 8), (-1, 2)))


def solve(input):
    seeds, *maps = [list(map(int, re.findall(r"\d+", l))) for l in input.split("\n\n")]

    def to_ranges(l):
        match l:
            case [a, b, c, *rest]:
                return [[a, b, c]] + to_ranges(rest)
            case []:
                return []

    def to_seed_ranges1(l):
        match l:
            case [a, *rest]:
                return [(a, a)] + to_seed_ranges1(rest)
            case []:
                return []

    def to_seed_ranges2(l):
        match l:
            case [a, b, *rest]:
                return [(a, a + b - 1)] + to_seed_ranges2(rest)
            case []:
                return []

    def through(maps, seeds):
        match maps:
            case [m, *rest]:
                restSeeds = seeds
                newSeeds = []
                for [dst, src, size] in m:
                    seeds = restSeeds
                    restSeeds = []
                    r = (src, src + size - 1)
                    for seed in seeds:
                        non, ov = overlap(seed, r)
                        restSeeds += non
                        if ov:
                            [(a, b)] = ov
                            newSeeds.append((a - src + dst, b - src + dst))
                return through(rest, newSeeds + restSeeds)
            case []:
                return seeds

    maps = list(map(to_ranges, maps))
    # print(to_seed_ranges1(seeds), maps)
    ans1 = min(through(maps, to_seed_ranges1(seeds)))[0]
    ans2 = min(through(maps, to_seed_ranges2(seeds)))[0]
    return (str(ans1), str(ans2))
