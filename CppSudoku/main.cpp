#include <cstdint>
#include <cstdio>

using Board = uint8_t[9][9];

static void PrintBoard(Board &board)
{
  std::puts("");
  for (uint8_t row = 0; row < 9; row++)
  {
    if (row % 3 == 0 && row != 0)
    {
      std::puts("------+-------+------");
    }
    for (uint8_t col = 0; col < 9; col++)
    {
      if (col % 3 == 0 && col != 0)
      {
        std::printf("| ");
      }
      if (board[row][col] == 0)
      {
        std::printf("  ");
      }
      else
      {
        std::printf("%u ", static_cast<unsigned int>(board[row][col]));
      }
    }
    std::puts("");
  }
  std::puts("");
}

static bool find_empty(Board &board, uint8_t &r, uint8_t &c)
{
  for (uint8_t row = 0; row < 9; row++)
  {
    for (uint8_t col = 0; col < 9; col++)
    {
      if (board[row][col] == 0)
      {
        r = row;
        c = col;
        return true;
      }
    }
  }
  return false;
}

static bool valid(Board &board, uint8_t row, uint8_t col, uint8_t num)
{
  // check column
  for (uint8_t y = 0; y < 9; y++)
  {
    if (board[y][col] == num)
    {
      return false;
    }
  }

  // check row
  for (uint8_t x = 0; x < 9; x++)
  {
    if (board[row][x] == num)
    {
      return false;
    }
  }

  // check box
  uint8_t box_y = row / 3 * 3;
  uint8_t box_x = col / 3 * 3;
  for (uint8_t y = box_y; y < box_y + 3; y++)
  {
    for (uint8_t x = box_x; x < box_x + 3; x++)
    {
      if (board[y][x] == num)
      {
        return false;
      }
    }
  }

  return true;
}

static bool solve(Board &board, uint32_t &steps)
{
  steps++;
  if (steps % 100000 == 0)
  {
    PrintBoard(board);
    std::printf("Combinations tried: %u\n", static_cast<unsigned int>(steps));
  }
  uint8_t row = 0;
  uint8_t col = 0;
  bool first_empty = find_empty(board, row, col);

  if (!first_empty)
  {
    return true;
  }

  for (uint8_t i = 1; i < 10; i++)
  {
    if (valid(board, row, col, i))
    {
      board[row][col] = i;

      if (solve(board, steps))
      {
        return true;
      }

      board[row][col] = 0;
    }
  }
  return false;
}

int main()
{
  uint32_t steps = 0;
  Board board = {
      {0, 0, 0, 7, 0, 0, 0, 0, 0}, //
      {1, 0, 0, 0, 0, 0, 0, 0, 0}, //
      {0, 0, 0, 4, 3, 0, 2, 0, 0}, //
      {0, 0, 0, 0, 0, 0, 0, 0, 6}, //
      {0, 0, 0, 5, 0, 9, 0, 0, 0}, //
      {0, 0, 0, 0, 0, 0, 4, 1, 8}, //
      {0, 0, 0, 0, 8, 1, 0, 0, 0}, //
      {0, 0, 2, 0, 0, 0, 0, 5, 0}, //
      {0, 4, 0, 0, 0, 0, 3, 0, 0}, //
  };

  solve(board, steps);
  PrintBoard(board);
  std::printf("Solved in %u steps\n", static_cast<unsigned int>(steps));
}
