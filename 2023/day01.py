def solve(input):
    def using(f):
        return str(
            sum(
                map(
                    lambda l: int(l[0] + l[-1]),
                    map(f, input.split()),
                )
            )
        )

    def replace(l):
        res = []
        for k, v in {
            "one": "1",
            "two": "2",
            "three": "3",
            "four": "4",
            "five": "5",
            "six": "6",
            "seven": "7",
            "eight": "8",
            "nine": "9",
            "1": "1",
            "2": "2",
            "3": "3",
            "4": "4",
            "5": "5",
            "6": "6",
            "7": "7",
            "8": "8",
            "9": "9",
        }.items():
            i = l.find(k)
            while i != -1:
                res.append((i, v))
                i = l.find(k, i + 1)
        return min(res)[1] + max(res)[1]

    return (
        using(lambda x: list(filter(str.isdigit, x))),
        using(replace),
    )
