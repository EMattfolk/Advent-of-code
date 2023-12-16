from point import Point


def bounce(dir, tile):
    match tile:
        case ".":
            return [dir]
        case "|":
            if dir[0] != 0:
                return [(0, 1), (0, -1)]
            else:
                return [dir]
        case "-":
            if dir[1] != 0:
                return [(1, 0), (-1, 0)]
            else:
                return [dir]
        case "/":
            if dir == (1, 0):
                return [(0, -1)]
            elif dir == (-1, 0):
                return [(0, 1)]
            elif dir == (0, 1):
                return [(-1, 0)]
            elif dir == (0, -1):
                return [(1, 0)]
        case "\\":
            if dir == (1, 0):
                return [(0, 1)]
            elif dir == (-1, 0):
                return [(0, -1)]
            elif dir == (0, 1):
                return [(1, 0)]
            elif dir == (0, -1):
                return [(-1, 0)]


def solve(input):
    input = input.split()
    tiles = {}
    for y, line in enumerate(input):
        for x, c in enumerate(line):
            tiles[(x, y)] = c

    max_x = len(input[0]) - 1
    max_y = len(input) - 1

    def solve(init_p, init_dir):
        visited = {init_p + init_dir}
        queue = [init_p + init_dir]
        while queue:
            px, py, dirx, diry = queue.pop()
            tile = input[py][px]
            for o in bounce((dirx, diry), tile):
                v = (px + o[0], py + o[1]) + o
                if (
                    v not in visited
                    and 0 <= v[0]
                    and v[0] <= max_x
                    and 0 <= v[1]
                    and v[1] <= max_y
                ):
                    visited.add(v)
                    queue.append(v)

        return len(set((px, py) for px, py, _, _ in visited))

    ans1 = solve((0, 0), (1, 0))

    ans2 = 0

    for x in range(0, max_x + 1):
        ans2 = max(solve((x, 0), (0, 1)), ans2)
        ans2 = max(solve((x, max_y), (0, -1)), ans2)

    for y in range(0, max_y + 1):
        ans2 = max(solve((0, y), (1, 0)), ans2)
        ans2 = max(solve((max_x, y), (-1, 0)), ans2)

    return (str(ans1), str(ans2))
