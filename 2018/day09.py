from time import process_time as clock

# Initialize the data
with open("09.txt") as f:
    data = f.read().split()
    data = (int(data[0]), int(data[6]))

def solve_linked_list (players, last):
    # id : (next, last)
    board = { 0:[0, 0] }
    scores = [0] * players
    current = 0
    for i in range(last):
        marble = i + 1
        player = i % data[0]
        if marble % 23 == 0:
            for _ in range(7):
                current = board[current][1]
            scores[player] += marble + current
            board[board[current][0]][1] = board[current][1]
            board[board[current][1]][0] = board[current][0]
            current = board[current][0]
        else:
            current = board[current][0]
            board[marble] = [board[current][0], current]
            board[current][0] = marble
            board[board[marble][0]][1] = marble
            current = marble
    res = max(scores)
    return res

def solve_deck (players, last):
    board = [[0]]
    scores = [0] * players
    current = 0
    board_index = 0
    for i in range(last):
        marble = i + 1
        player = i % data[0]
        if marble % 23 == 0:
            if current - 7 < 0:
                board_index = (board_index - 1) % len(board)
            current = (current - 7) % len(board[board_index])
            scores[player] += marble + board[board_index][current]
            del board[board_index][current]
            if current == len(board[board_index]):
                board_index = (board_index + 1) % len(board)
                current = 0
        else:
            current = (current + 1) % len(board[board_index])
            if current == 0:
                if len(board[board_index]) > 90:
                    temp = board[board_index]
                    del board[board_index]
                    board.insert(board_index, temp[len(temp)//2:])
                    board.insert(board_index, temp[:len(temp)//2])
                    board_index += 1
                board_index = (board_index + 1) % len(board)
            current += 1
            board[board_index].insert(current, marble)
    res = max(scores)
    return res

# Function for solving the first problem
def first ():
    st = clock()
    res = solve_deck(data[0], data[1])
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    res = solve_deck(data[0], data[1] * 100)
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
