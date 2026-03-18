package main

import "fmt"

// Board is a type alias for sudoku board
type Board = [9][9]int

var board = Board{
	{0, 0, 0, 7, 0, 0, 0, 0, 0}, //
	{1, 0, 0, 0, 0, 0, 0, 0, 0}, //
	{0, 0, 0, 4, 3, 0, 2, 0, 0}, //
	{0, 0, 0, 0, 0, 0, 0, 0, 6}, //
	{0, 0, 0, 5, 0, 9, 0, 0, 0}, //
	{0, 0, 0, 0, 0, 0, 4, 1, 8}, //
	{0, 0, 0, 0, 8, 1, 0, 0, 0}, //
	{0, 0, 2, 0, 0, 0, 0, 5, 0}, //
	{0, 4, 0, 0, 0, 0, 3, 0, 0}, //
}

var steps = 0

func printBoard(board *Board) {
	fmt.Println()
	for row := range 9 {
		if row%3 == 0 && row != 0 {
			fmt.Println("------+-------+------")
		}
		for col := range 9 {
			if col%3 == 0 && col != 0 {
				fmt.Print("| ")
			}
			if board[row][col] == 0 {
				fmt.Print("  ")
			} else {
				fmt.Print(board[row][col], " ")
			}
		}
		fmt.Println()
	}
	fmt.Println()
}

func findEmpty(board *Board) (int, int, bool) {
	for row := range 9 {
		for col := range 9 {
			if board[row][col] == 0 {
				return row, col, true
			}
		}
	}
	return 0, 0, false
}

func valid(board *Board, row int, col int, num int) bool {
	// check column
	for y := range 9 {
		if board[y][col] == num {
			return false
		}
	}

	// check row
	for x := range 9 {
		if board[row][x] == num {
			return false
		}
	}

	// check box
	boxY := row / 3 * 3
	boxX := col / 3 * 3
	for y := boxY; y < boxY+3; y++ {
		for x := boxX; x < boxX+3; x++ {
			if board[y][x] == num {
				return false
			}
		}
	}

	return true
}

func solve(board *Board) bool {
	steps++
	if steps%100000 == 0 {
		printBoard(board)
		fmt.Println("Combinations tried:", steps)
	}

	row, col, hasEmpty := findEmpty(board)
	if !hasEmpty {
		return true
	}

	for i := 1; i <= 9; i++ {
		if valid(board, row, col, i) {
			board[row][col] = i

			if solve(board) {
				return true
			}

			board[row][col] = 0
		}
	}

	return false
}

func main() {
	solve(&board)
	printBoard(&board)
	fmt.Println("Solved in", steps, "steps")
}
