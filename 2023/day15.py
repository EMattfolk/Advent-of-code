from collections import defaultdict


def hash(instr):
    v = 0
    for c in instr:
        v = ((v + ord(c)) * 17) % 256

    return v


def solve(input):
    instrs = input.split(",")
    ans1 = sum(map(hash, instrs))

    buckets = defaultdict(list)

    for instr in instrs:
        if instr.endswith("-"):
            to_remove = instr[:-1]
            bucket = buckets[hash(to_remove)]
            r = None
            for i, (name, _) in enumerate(bucket):
                if name == to_remove:
                    r = i
                    break
            if r is not None:
                del bucket[i]
        else:
            to_insert = instr.split("=")
            to_insert[1] = int(to_insert[1])
            to_insert = tuple(to_insert)
            bucket = buckets[hash(to_insert[0])]
            found = False
            for i, (name, _) in enumerate(bucket):
                if name == to_insert[0]:
                    found = True
                    bucket[i] = to_insert
                    break
            if not found:
                bucket.append(to_insert)

    # print(buckets)

    ans2 = 0
    for i, bucket in buckets.items():
        for slot, (_, focus) in enumerate(bucket):
            ans2 += (i + 1) * (slot + 1) * focus
    return (str(ans1), str(ans2))
