from time import process_time

day = 0

# Initialize the data
with open(f"{day}.txt") as f:
    pass


def first():
    """ Returns the answer to the first problem of the day. """
    res = 0
    return res


def second():
    """ Returns the answer to the second problem of the day. """
    res = 0
    return res


if __name__ == "__main__":

    start = process_time()

    first_ans = first()
    second_ans = second()

    end = process_time()

    print(f"First: {first_ans}")
    print(f"Second: {second_ans}")
    print(f"Time: {end-start}")
