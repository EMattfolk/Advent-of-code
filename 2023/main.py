from importlib import import_module
from time import process_time

for day in range(1, 26):
    day_string = f"day{day:>02}"
    try:
        m = import_module(day_string)
    except:
        break
    st = process_time()
    res = m.solve(open("input/" + day_string + ".txt").read().rstrip())
    end = process_time()
    print(f"Day {day:>2}: {(end-st)*1000:>8.3f}ms - {res[0]}, {res[1]}")
