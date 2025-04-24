from importlib import import_module
from time import process_time
from multiprocessing import Pool


def solve_day(day):
    day_string = f"day{day:>02}"
    try:
        m = import_module(day_string)
    except:
        return ""
    st = process_time()
    res = m.solve(open("input/" + day_string + ".txt").read().rstrip())
    end = process_time()
    return f"Day {day:>2}: {(end-st)*1000:>8.3f}ms - {res[0]}, {res[1]}\n"


with Pool(12) as p:
    for res in p.imap(solve_day, range(1, 26)):
        print(res, end="")
