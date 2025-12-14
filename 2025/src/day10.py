import numpy as np
import re
import z3

input = open("input/day10.txt").read().strip().split("\n")
# print(input)

ans = 0
for line in input:
    line = line.split(" ")
    buttons = list(map(lambda s: list(map(int, re.findall(r"\d+", s))), line[1:-1]))
    target = list(map(lambda s: list(map(int, re.findall(r"\d+", s))), line[-1:]))[0]
    # print(buttons, target)
    M = [[0] * len(buttons) for _ in range(len(target))]
    for c, b in enumerate(buttons):
        for r in b:
            M[r][c] = 1
    # print(M)
    vars = []
    constraints = []
    for i in range(len(M[0])):
        var = z3.Int("abcdefghijklmnop"[i])
        constraints.append(var >= 0)
        vars.append(var)
    for i in range(len(M)):
        constraints.append(
            sum([vars[j] * M[i][j] for j in range(len(M[i]))]) == target[i]
        )
    # print(constraints, flush=True)
    s = z3.Solver()
    s.add(*constraints)
    s.check()
    model = s.model()
    guess = sum(int(model[vars[i]].as_string()) for i in range(len(model)))
    while True:
        s = z3.Solver()
        s.add(*constraints)
        s.add(sum(vars) < guess)
        if s.check() == z3.sat:
            model = s.model()
            guess = sum(int(model[vars[i]].as_string()) for i in range(len(model)))
        else:
            break

    ans += sum(int(model[vars[i]].as_string()) for i in range(len(model)))
    # z3.solve(*constraints)
    # print(np.linalg.lstsq(M, T))

print(ans)
