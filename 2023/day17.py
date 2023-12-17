from heapq import heappush as push, heappop as pop
from collections import defaultdict


def right(dir):
    return (dir[1], dir[0])


def left(dir):
    return (-dir[1], -dir[0])


def solve(input):
    input = [list(map(int, l)) for l in input.split()]

    max_x = len(input[0]) - 1
    max_y = len(input) - 1

    def solve(branches):
        visited = defaultdict(lambda: 99999999999)
        queue = []
        push(queue, (0, ((0, 0), (1, 0), 0)))
        push(queue, (0, ((0, 0), (0, 1), 0)))
        while queue:
            cost, (pos, dir, cons) = pop(queue)

            if pos == (max_x, max_y):
                return cost

            for o in branches(cons, dir):
                new_pos = (pos[0] + o[0], pos[1] + o[1])
                if (
                    new_pos[0] < 0
                    or new_pos[0] > max_x
                    or new_pos[1] < 0
                    or new_pos[1] > max_y
                ):
                    continue
                new_cost = cost + input[new_pos[1]][new_pos[0]]
                new_cons = cons + 1 if o == dir else 1
                new_state = (new_pos, o, new_cons)
                if visited[new_state] > new_cost:
                    visited[new_state] = new_cost
                    push(queue, (new_cost, new_state))

    ans1 = solve(
        lambda cons, dir: [right(dir), left(dir)] + ([dir] if cons < 3 else [])
    )
    ans2 = solve(
        lambda cons, dir: ([right(dir), left(dir)] + ([dir] if cons < 10 else []))
        if cons >= 4
        else [dir]
    )
    return (str(ans1), str(ans2))
