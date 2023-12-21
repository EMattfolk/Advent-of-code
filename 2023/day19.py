import json


def solve(input):
    [workflows_string, parts] = input.split("\n\n")

    workflows = {}
    for w in workflows_string.split():
        i = w.index("{")
        name = w[:i]
        instrs = []
        for instr in w[i + 1 : -1].split(","):
            if ":" in instr:
                [cond, dest] = instr.split(":")
                var = cond[0]
                val = int(cond[2:])
                if cond[1] == ">":
                    instrs.append([(lambda x, y: x > y), var, val, dest, ">"])
                else:
                    instrs.append([(lambda x, y: x < y), var, val, dest, "<"])
            else:
                instrs.append([(lambda x, y: True), "s", 0, instr, ""])

        workflows[name] = instrs

    parts = [
        [prop.split("=") for prop in part[1:-1].split(",")]
        for part in parts.split("\n")
    ]
    parts = [{a: int(b) for [a, b] in part} for part in parts]
    # print(workflows)

    ans1 = 0
    for part in parts:
        w = "in"
        while w != "A" and w != "R":
            for [op, var, val, dest, _] in workflows[w]:
                if op(part[var], val):
                    w = dest
                    break
        if w == "A":
            ans1 += sum(part.values())

    def count(part, w):
        if w == "R":
            return 0
        if w == "A":
            r = 1
            for a, b in part.values():
                r *= max(b - a + 1, 0)
            return r
        r = 0
        for [_, var, val, dest, op] in workflows[w]:
            if op == "":
                return r + count(part.copy(), dest)
            elif op == "<":
                (a, b) = part[var]
                p1 = part.copy()
                p1[var] = (a, min(b, val - 1))
                r += count(p1, dest)
                part[var] = (max(a, val), b)
            elif op == ">":
                (a, b) = part[var]
                p1 = part.copy()
                p1[var] = (max(a, val + 1), b)
                r += count(p1, dest)
                part[var] = (a, min(val, b))

    ans2 = count({"x": (1, 4000), "m": (1, 4000), "a": (1, 4000), "s": (1, 4000)}, "in")
    return (str(ans1), str(ans2))
