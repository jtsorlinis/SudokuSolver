const board = [
  [0, 0, 0, 7, 0, 0, 0, 0, 0],
  [1, 0, 0, 0, 0, 0, 0, 0, 0],
  [0, 0, 0, 4, 3, 0, 2, 0, 0],
  [0, 0, 0, 0, 0, 0, 0, 0, 6],
  [0, 0, 0, 5, 0, 9, 0, 0, 0],
  [0, 0, 0, 0, 0, 0, 4, 1, 8],
  [0, 0, 0, 0, 8, 1, 0, 0, 0],
  [0, 0, 2, 0, 0, 0, 0, 5, 0],
  [0, 4, 0, 0, 0, 0, 3, 0, 0]
]

let steps = 0

const printBoard = (board) => {
  console.log()
  for (let row = 0; row < 9; row++) {
    if (row % 3 === 0 && row !== 0) {
      console.log('---------------------')
    }
    for (let col = 0; col < 9; col++) {
      if (col % 3 === 0 && col !== 0) {
        process.stdout.write('| ')
      }
      process.stdout.write((board[row][col] === 0 ? ' ' : board[row][col]) + ' ')
    }
    console.log()
  }
  console.log()
}

const findEmpty = (board) => {
  for (let row = 0; row < 9; row++) {
    for (let col = 0; col < 9; col++) {
      if (board[row][col] === 0) {
        return [row, col]
      }
    }
  }
  return false
}

const valid = (board, row, col, num) => {
  // check column
  for (let y = 0; y < 9; y++) {
    if (board[y][col] === num) {
      return false
    }
  }

  // check row
  for (let x = 0; x < 9; x++) {
    if (board[row][x] === num) {
      return false
    }
  }

  // check box
  const boxY = ~~(row / 3) * 3
  const boxX = ~~(col / 3) * 3
  for (let y = boxY; y < boxY + 3; y++) {
    for (let x = boxX; x < boxX + 3; x++) {
      if (board[y][x] === num) {
        return false
      }
    }
  }

  return true
}

const solve = (board) => {
  steps++
  if (steps % 100000 === 0) {
    printBoard(board)
    console.log('Combinations tried: ' + steps)
  }

  const firstEmpty = findEmpty(board)
  if (!firstEmpty) {
    return true
  }
  const row = firstEmpty[0]
  const col = firstEmpty[1]
  for (let i = 1; i <= 9; i++) {
    if (valid(board, row, col, i)) {
      board[row][col] = i

      if (solve(board)) {
        return true
      }
      board[row][col] = 0
    }
  }
  return false
}

solve(board)
printBoard(board)
console.log('Solved in ' + steps + ' steps')
