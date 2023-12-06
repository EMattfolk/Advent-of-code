import re
import math


def quadratic_eqn(a, b, c):
    return (
        (-b + (b**2 - 4 * a * c) ** 0.5) / (2 * a),
        (-b - (b**2 - 4 * a * c) ** 0.5) / (2 * a),
    )


def solve(input):
    time, dist = map(lambda l: list(re.findall(r"\d+", l)), input.split("\n"))
    ans1 = 1
    # f(x) =  x^2 - tx + d < 0
    for t, d in zip(time, dist):
        (a, b) = quadratic_eqn(1, -int(t), int(d))
        ans1 *= math.floor(a) - math.ceil(b) + 1
    t = int("".join(time))
    d = int("".join(dist))
    (a, b) = quadratic_eqn(1, -t, d)
    ans2 = math.floor(a) - math.ceil(b) + 1
    return (str(ans1), str(ans2))
