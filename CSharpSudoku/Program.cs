using System;


namespace CSharpSudoku
{
  class Program
  {

    static int[,] board =  {
        {0, 0, 0, 7, 0, 0, 0, 0, 0},  //
        {1, 0, 0, 0, 0, 0, 0, 0, 0},  //
        {0, 0, 0, 4, 3, 0, 2, 0, 0},  //
        {0, 0, 0, 0, 0, 0, 0, 0, 6},  //
        {0, 0, 0, 5, 0, 9, 0, 0, 0},  //
        {0, 0, 0, 0, 0, 0, 4, 1, 8},  //
        {0, 0, 0, 0, 8, 1, 0, 0, 0},  //
        {0, 0, 2, 0, 0, 0, 0, 5, 0},  //
        {0, 4, 0, 0, 0, 0, 3, 0, 0},  //
    };

    static int steps = 0;

    static void PrintBoard(ref int[,] board)
    {
      Console.WriteLine();
      for (int row = 0; row < 9; row++)
      {
        if (row % 3 == 0 && row != 0)
        {
          Console.WriteLine("------+-------+------");
        }
        for (int col = 0; col < 9; col++)
        {
          if (col % 3 == 0 && col != 0)
          {
            Console.Write("| ");
          }
          if (board[row, col] == 0)
          {
            Console.Write("  ");
          }
          else
          {
            Console.Write(board[row, col] + " ");
          }
        }
        Console.WriteLine();
      }
      Console.WriteLine();
    }

    static bool FindEmpty(ref int[,] board, ref int r, ref int c)
    {
      for (int row = 0; row < 9; row++)
      {
        for (int col = 0; col < 9; col++)
        {
          if (board[row, col] == 0)
          {
            r = row;
            c = col;
            return true;
          }
        }
      }
      return false;
    }

    static bool Valid(ref int[,] board, int row, int col, int num)
    {
      // check column
      for (int y = 0; y < 9; y++)
      {
        if (board[y, col] == num)
        {
          return false;
        }
      }

      // check row
      for (int x = 0; x < 9; x++)
      {
        if (board[row, x] == num)
        {
          return false;
        }
      }

      // check box
      int box_y = row / 3 * 3;
      int box_x = col / 3 * 3;
      for (int y = box_y; y < box_y + 3; y++)
      {
        for (int x = box_x; x < box_x + 3; x++)
        {
          if (board[y, x] == num)
          {
            return false;
          }
        }
      }

      return true;
    }

    static bool Solve(ref int[,] board)
    {
      steps++;
      if (steps % 100000 == 0)
      {
        PrintBoard(ref board);
        Console.WriteLine("Combinations tried: " + steps);
      }
      int row = 0, col = 0;
      bool hasEmpty = FindEmpty(ref board, ref row, ref col);

      if (!hasEmpty)
      {
        return true;
      }

      for (int i = 1; i <= 9; i++)
      {
        if (Valid(ref board, row, col, i))
        {
          board[row, col] = i;
          if (Solve(ref board))
          {
            return true;
          }
          board[row, col] = 0;
        }
      }
      return false;
    }

    static void Main()
    {
      Solve(ref board);
      PrintBoard(ref board);
      Console.WriteLine("Solved in " + steps + " steps");
    }
  }
}
