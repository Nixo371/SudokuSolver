# Sudoku Solver

In `src/main.cpp` in the function call `sudoku.solve_backtracking(0, 0, false);`, the 3rd parameter is the debug mode. `true` will print out the board state after every iteration.
I thought about adding in the cool ANSI color escape sequences to visually see what it's working on and what it's done so far but not yet.

If you want to try it out, you need to feed it a file name with sudokus in this format:
`......162...12....5.....3.....6..51....5872.6.......3.6...3.7....2....58..89.6...`
Check out [QQWing](https://qqwing.com/generate.html) with the `Output format` set to `One line` to generate your own. (You can also download the command line tool from there if you want to do more than a couple) 

It will output at the end the total time and the time/puzzle
Also a file will be created (***or overwritten***) called [filename]_out with detailed timings for each puzzle (if you care about that).
First number is the total time for the puzzle, 2nd is the cumulative time the `check_valid` function took.
