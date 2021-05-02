def print_board(board):
    print()
    for row in range(9):
        if(row % 3 == 0 and row != 0):
            print("---------------------")
        for col in range(9):
            if(col % 3 == 0 and col != 0):
                print("|", end=" ")
            print(board[row][col] if board[row][col] != 0 else " ", end=" ")
        print()
    print()


# Find an empty square on the board
def find_empty(board):
    for row in range(9):
        for col in range(9):
            if board[row][col] == 0:
                return (row, col)
    return False


def valid(board, row, col, num):
    # check column
    for y in range(9):
        if board[y][col] == num:
            return False

    # check row
    for x in range(9):
        if board[row][x] == num:
            return False

    # check box
    box_y = row // 3 * 3
    box_x = col // 3 * 3
    for y in range(box_y, box_y+3):
        for x in range(box_x, box_x+3):
            if board[y][x] == num:
                return False

    # value is valid
    return True


def solve(board):
    global steps
    steps += 1
    if steps % 100000 == 0:
        print_board(board)
        print("Combinations Tried: " + str(steps))

    # get the first empty spot on the board
    first_empty = find_empty(board)

    # if there are none, we are done
    if not first_empty:
        return True
    row, col = first_empty

    # loop through each number 1-9
    for i in range(1, 10):
        # if it is valid put it in
        if valid(board, row, col, i):
            board[row][col] = i

            # recursively call solve until we hit a deadend
            if solve(board):
                return True

            # set the last value back to blank and try again
            board[row][col] = 0
    return False


steps = 0

board = [
        [0, 0, 0, 7, 0, 0, 0, 0, 0],
        [1, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 4, 3, 0, 2, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 6],
        [0, 0, 0, 5, 0, 9, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 4, 1, 8],
        [0, 0, 0, 0, 8, 1, 0, 0, 0],
        [0, 0, 2, 0, 0, 0, 0, 5, 0],
        [0, 4, 0, 0, 0, 0, 3, 0, 0],
]


def main():

    solve(board)
    print_board(board)
    print("Solved in " + str(steps) + " steps")


if __name__ == "__main__":
    main()
