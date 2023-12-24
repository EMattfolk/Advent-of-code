import re
from collections import defaultdict
from functools import lru_cache


def solve(input):
    input = [list(map(int, re.findall(r"\d+", l))) for l in input.split("\n")]
    blocks = [(block[:3], block[3:]) for block in input]
    blocks.sort(key=lambda b: b[0][2])

    stack = []

    for b1, b2 in blocks:
        supports = []
        bestz = None
        for i in range(len(stack)):
            (_, (s1, s2)) = stack[i]
            xr = set(range(b1[0], b2[0] + 1)) & set(range(s1[0], s2[0] + 1))
            yr = set(range(b1[1], b2[1] + 1)) & set(range(s1[1], s2[1] + 1))
            if xr and yr:
                if bestz is None:
                    supports = [i]
                    bestz = s2[2]
                elif s2[2] > bestz:
                    supports = [i]
                    bestz = s2[2]
                elif s2[2] == bestz:
                    supports.append(i)

        if supports:
            goal_z = stack[supports[0]][1][1][2] + 1
        else:
            goal_z = 1

        z_diff = b2[2] - b1[2]
        b1 = (b1[0], b1[1], goal_z)
        b2 = (b2[0], b2[1], goal_z + z_diff)
        stack.append((supports, (b1, b2)))

    # print(stack)
    s = set()
    for supports, _ in stack:
        if len(supports) == 1:
            s |= set(supports)

    ans1 = len(stack) - len(s)

    fall_map = defaultdict(list)
    for i, (supports, _) in enumerate(stack):
        for support in supports:
            fall_map[support].append(i)

    def below(i):
        disintegrated = {i}
        to_disintegrate = [i]
        while to_disintegrate:
            dis = to_disintegrate.pop()
            for n in fall_map[dis]:
                if (
                    len(set(stack[n][0]) - disintegrated) == 0
                    and n not in disintegrated
                ):
                    disintegrated.add(n)
                    to_disintegrate.append(n)

        return len(disintegrated) - 1

    ans2 = sum(below(i) for i in range(len(stack)))

    return (str(ans1), str(ans2))
