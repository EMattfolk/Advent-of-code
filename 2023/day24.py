import re
import numpy as np

# dx(x - x0) = dy(y - y0)
# dx / dy (x - x0) + y0 = y

# t dx (x - x0) + t dy (y - y0)

test_start = 200000000000000
test_end = 400000000000000


def solve(input):
    ans1 = 0
    ans2 = 0
    lines = list(
        map(lambda l: list(map(int, re.findall(r"-?\d+", l))), input.split("\n"))
    )

    for i, [x0, y0, z0, dx0, dy0, dz0] in enumerate(lines):
        for [x1, y1, z1, dx1, dy1, dz1] in lines[i + 1 :]:
            try:
                a = np.matrix([[dx0, -dx1], [dy0, -dy1]])
                b = np.matrix([[x1 - x0], [y1 - y0]])
                res = (a.T * a).I * a.T * b
            except:
                continue
            s = res[0, 0]
            t = res[1, 0]
            x = x0 + s * dx0
            y = y0 + s * dy0
            if (
                s >= 0
                and t >= 0
                and test_start <= x
                and x <= test_end
                and test_start <= y
                and y <= test_end
            ):
                # print(s, t, x, y)
                ans1 += 1

    print(*sorted(lines), sep="\n", flush=True)

    return (str(ans1), str(ans2))
