type Board = [[i32; 9]; 9];

fn print_board(board: &Board) {
    println!();
    for row in 0..9 {
        if row % 3 == 0 && row != 0 {
            println!("---------------------")
        }
        for col in 0..9 {
            if col % 3 == 0 && col != 0 {
                print!("| ")
            }
            if board[row][col] == 0 {
                print!("  ")
            } else {
                print!("{} ", board[row][col]);
            }
        }
        println!();
    }
    println!();
}

fn find_empty(board: &Board, r: &mut i32, c: &mut i32) -> bool {
    for row in 0..9 {
        for col in 0..9 {
            if board[row][col] == 0 {
                *r = row as i32;
                *c = col as i32;
                return true;
            }
        }
    }
    return false;
}

fn valid(board: &Board, row: i32, col: i32, num: i32) -> bool {
    // check column
    for y in 0..9 {
        if board[y][col as usize] == num {
            return false;
        }
    }

    // check row
    for x in 0..9 {
        if board[row as usize][x] == num {
            return false;
        }
    }

    // check box
    let box_y = row / 3 * 3;
    let box_x = col / 3 * 3;
    for y in box_y..box_y + 3 {
        for x in box_x..box_x + 3 {
            if board[y as usize][x as usize] == num {
                return false;
            }
        }
    }
    return true;
}

fn solve(board: &mut Board, steps: &mut i32) -> bool {
    *steps += 1;
    if *steps % 100000 == 0 {
        print_board(board);
        println!("Combinations tried: {}", steps);
    }

    let mut row = 0;
    let mut col = 0;
    let first_empty = find_empty(board, &mut row, &mut col);
    if !first_empty {
        return true;
    }

    for i in 1..10 {
        if valid(board, row, col, i) {
            board[row as usize][col as usize] = i;

            if solve(board, steps) {
                return true;
            }
            board[row as usize][col as usize] = 0;
        }
    }

    return false;
}

fn main() {
    let mut steps = 0;
    let mut board: Board = [
        [0, 0, 0, 7, 0, 0, 0, 0, 0], //
        [1, 0, 0, 0, 0, 0, 0, 0, 0], //
        [0, 0, 0, 4, 3, 0, 2, 0, 0], //
        [0, 0, 0, 0, 0, 0, 0, 0, 6], //
        [0, 0, 0, 5, 0, 9, 0, 0, 0], //
        [0, 0, 0, 0, 0, 0, 4, 1, 8], //
        [0, 0, 0, 0, 8, 1, 0, 0, 0], //
        [0, 0, 2, 0, 0, 0, 0, 5, 0], //
        [0, 4, 0, 0, 0, 0, 3, 0, 0], //
    ];
    solve(&mut board, &mut steps);
    print_board(&board);
    println!("Solved in {} steps", steps);
}
