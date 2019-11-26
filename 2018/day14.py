from time import process_time as clock

rec = 320851

st = clock()
scores = [3, 7, 1, 0, 1, 0]
seq = "371010"
target = str(rec)
curr1 = 4
curr2 = 3
res2 = False
while not res2:
    s = scores[curr1] + scores[curr2]
    for d in str(s):
        scores.append(int(d))
        seq = seq[1:] + d
        if seq == target:
            res2 = len(scores) - len(seq)
    curr1 = (curr1 + scores[curr1] + 1) % len(scores)
    curr2 = (curr2 + scores[curr2] + 1) % len(scores)

res1 = "".join([str(i) for i in scores[rec:rec+10]])
print("First:", res1, "Time:", clock() - st)
print("Second:", res2, "Time:", clock() - st)
