from point import Point


def solve(input):
    nums = {}
    for y, l in enumerate(input.split()):
        acc = ""
        for x, c in enumerate(l):
            if c.isdigit():
                acc += c
            elif acc:
                n = int(acc)
                nums.update({(x - 1 - o, y): ((x, y), n) for o in range(len(acc))})
                acc = ""
        if acc:
            n = int(acc)
            nums.update({(x - 1 - o, y): ((x, y), n) for o in range(len(acc))})
            acc = ""

    ans2 = 0
    adj = {}
    for y, l in enumerate(input.split()):
        for x, c in enumerate(l):
            if not c.isdigit() and c != ".":
                around_this = {}
                for offset in [
                    Point(-1, -1),
                    Point(-1, 0),
                    Point(-1, 1),
                    Point(0, -1),
                    Point(0, 1),
                    Point(1, -1),
                    Point(1, 0),
                    Point(1, 1),
                ]:
                    p = tuple(Point(x, y) + offset)
                    if p in nums:
                        adj[nums[p][0]] = nums[p][1]
                        around_this[nums[p][0]] = nums[p][1]
                if c == "*" and len(around_this) == 2:
                    around_this = list(around_this.values())
                    ans2 += around_this[0] * around_this[1]
    # print(input)
    # print(nums)
    # print(adj)

    ans1 = sum(adj.values())
    return (str(ans1), str(ans2))
