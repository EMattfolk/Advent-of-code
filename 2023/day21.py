from point import Point

# With a little bit of help from:
# https://github.com/villuna/aoc23/wiki/A-Geometric-solution-to-advent-of-code-2023,-day-21


def solve(input):
    garden = [list(l) for l in input.split("\n")]
    size = len(garden)

    for y, l in enumerate(garden):
        for x, c in enumerate(l):
            if c == "S":
                start = Point(x, y)

    def step(plots):
        new_plots = set()
        for p in plots:
            for o in [Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1)]:
                np = p + o
                if (
                    0 <= np.x
                    and np.x < size
                    and 0 <= np.y
                    and np.y < size
                    and garden[np.y][np.x] != "#"
                ):
                    new_plots.add(np)
        return new_plots

    plots = {start}
    for _ in range(64):
        plots = step(plots)

    ans1 = len(plots)

    plots = {start}
    for i in range(140):
        plots = step(plots)
        if i == 138:
            odd = len(plots)

    even = len(plots)
    # print(even, odd)

    target_steps = 26501365

    full_gardens = (target_steps - start.x) // size - 1  # Last is not filled
    to_go = (target_steps - start.x) % size  # 0

    # print(full_gardens, to_go)

    #     #
    #    #E#
    #   #E#E#
    #  #E#E#E#
    #   #E#E#
    #    #E#
    #     #

    ans2 = odd
    for i in range(1, full_gardens + 1):
        if i % 2 == 1:
            ans2 += even * i * 4
        else:
            ans2 += odd * i * 4

    plots = {Point(-1, start.y)}
    for i in range(size):
        plots = step(plots)
    ans2 += len(plots)

    plots = {Point(size, start.y)}
    for i in range(size):
        plots = step(plots)
    ans2 += len(plots)

    plots = {Point(start.x, -1)}
    for i in range(size):
        plots = step(plots)
    ans2 += len(plots)

    plots = {Point(start.x, size)}
    for i in range(size):
        plots = step(plots)
    ans2 += len(plots)

    plots = {Point(0, -1)}
    for i in range(size - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * (full_gardens + 1)

    plots = {Point(size - 1, -1)}
    for i in range(size - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * (full_gardens + 1)

    plots = {Point(0, size)}
    for i in range(size - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * (full_gardens + 1)

    plots = {Point(size - 1, size)}
    for i in range(size - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * (full_gardens + 1)

    plots = {Point(0, -1)}
    for i in range(size * 2 - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * full_gardens

    plots = {Point(size - 1, -1)}
    for i in range(size * 2 - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * full_gardens

    plots = {Point(0, size)}
    for i in range(size * 2 - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * full_gardens

    plots = {Point(size - 1, size)}
    for i in range(size * 2 - start.x - 1):
        plots = step(plots)
    ans2 += len(plots) * full_gardens

    return (str(ans1), str(ans2))
