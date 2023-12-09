import re
from math import lcm


def solve(input):
    [path, nodes] = input.split("\n\n")
    path = [1 if c == "R" else 0 for c in path]
    nodes = [re.findall(r"[A-Z]+", l) for l in nodes.split("\n")]
    nodes = {a: (b, c) for [a, b, c] in nodes}

    def find_steps(node):
        step = 0
        while not node.endswith("Z"):
            node = nodes[node][path[step % len(path)]]
            step += 1
        return step

    ans1 = find_steps("AAA")

    a_nodes = [
        find_steps(node) for node in nodes if node.endswith("A") and node != "AAA"
    ]

    ans2 = ans1
    for steps in a_nodes:
        ans2 = lcm(steps, ans2)

    return (str(ans1), str(ans2))
