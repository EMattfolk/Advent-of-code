import re
from collections import deque
import math


def solve(input):
    input = [(l[0], re.findall(r"\w+", l)) for l in input.split("\n")]

    nodes = {}

    for first, node in input:
        name, *connected = node
        if first == "&":
            nodes[name] = {"t": first, "inputs": {}, "connected": connected}
        elif first == "%":
            nodes[name] = {"t": first, "input": False, "connected": connected}
        elif first == "b":
            nodes[name] = {"t": first, "connected": connected}
        else:
            assert False

    for _, node in input:
        name, *connected = node
        for conn in connected:
            if conn not in nodes:
                nodes[conn] = {"t": "s", "input": False}
            if nodes[conn]["t"] == "&":
                nodes[conn]["inputs"][name] = False

    interesting = {"nx": [], "zp": [], "bz": [], "dj": []}

    def press(n):
        high, low = 0, 0
        queue = deque([("button", "broadcaster", False)])
        while queue:
            sender, node_name, pulse = queue.pop()
            # print(sender, "-high->" if pulse else "-low->", node_name)
            if sender in interesting and not pulse:
                interesting[sender].append(n)

            if pulse:
                high += 1
            else:
                low += 1

            node = nodes[node_name]
            if node["t"] == "b":
                for conn in node["connected"]:
                    queue.appendleft((node_name, conn, pulse))
            elif node["t"] == "%" and not pulse:
                node["input"] = not node["input"]
                for conn in node["connected"]:
                    queue.appendleft((node_name, conn, node["input"]))
            elif node["t"] == "&":
                node["inputs"][sender] = pulse
                out = not all(node["inputs"].values())
                for conn in node["connected"]:
                    queue.appendleft((node_name, conn, out))
            elif node["t"] == "s" and not pulse:
                node["input"] = True

        return high, low

    high = 0
    low = 0
    for i in range(1, 1001):
        h, l = press(i)
        high += h
        low += l
    ans1 = high * low

    i = 1001
    while not all(interesting.values()):
        press(i)
        i += 1

    ans2 = 1
    for v in interesting.values():
        ans2 = math.lcm(v[0], ans2)

    return (str(ans1), str(ans2))
