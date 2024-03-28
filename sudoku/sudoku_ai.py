import numpy as np
import random
# python3 -m pip install --upgrade pip
# pip install ortools

'''
Import CP-SAT solver from Google's OR-Tools
for constraint programming, used for efficiently solving combinatorial problems like Sudoku.
'''
from ortools.sat.python import cp_model

'''
Constraint Programming (CP):
This is a method used to solve combinatorial problems like Sudoku.
Instead of searching through all possible combinations of numbers,
CP uses mathematical constraints (rules) to eliminate impossible configurations,
thereby reducing the search space.
In Sudoku, constraints can include rules like
"each number 1 through 9 must appear exactly once in each row, column, and 3x3 grid."

OR-Tools' CP-SAT Solver:
This is a solver within Google's OR-Tools
designed specifically for Constraint Programming. 
The "SAT" in CP-SAT stands for "Boolean Satisfiability Problem,"
which is a type of constraint satisfaction problem.
The CP-SAT solver is highly efficient and can solve large,
complex problems by breaking them down into smaller constraints
and finding solutions that satisfy all the constraints simultaneously.
'''

class Sudoku:
    def __init__(self):
        self.grid = np.zeros((9, 9), dtype=int)

    def solve(self, grid=None):
        if grid is None:
            grid = self.grid
        model = cp_model.CpModel()

        # Create a 9x9 matrix of integer variables with values in [1, 9].
        cells = [[model.NewIntVar(1, 9, f'cell_{i}_{j}') for j in range(9)] for i in range(9)]

        # Shuffle numbers to introduce variability in potential solutions
        numbers = list(range(1, 10))
        random.shuffle(numbers)

        # Apply shuffled numbers to domain
        for i in range(9):
            for j in range(9):
                if grid[i][j] != 0:
                    # Map the pre-filled number to its position in the shuffled list
                    shuffled_num = numbers.index(grid[i][j]) + 1
                    model.Add(cells[i][j] == shuffled_num)

        # All different constraint for rows and columns
        for i in range(9):
            model.AddAllDifferent(cells[i])  # Rows
            model.AddAllDifferent([cells[j][i] for j in range(9)])  # Columns

        # All different constraint for 3x3 subgrids
        for i in range(0, 9, 3):
            for j in range(0, 9, 3):
                subgrid = [cells[i + di][j + dj] for di in range(3) for dj in range(3)]
                model.AddAllDifferent(subgrid)

        # Solve the model
        solver = cp_model.CpSolver()
        status = solver.Solve(model)

        # If a solution is found, map shuffled numbers back to their original values
        if status == cp_model.FEASIBLE or status == cp_model.OPTIMAL:
            for i in range(9):
                for j in range(9):
                    original_num = numbers[solver.Value(cells[i][j]) - 1]
                    self.grid[i][j] = original_num
            return True
        return False

    def is_valid(self, row, col, num, grid):
        # This function remains unchanged, but is not used in the new solve method
        if num in grid[row]:  # Check row
            return False
        if num in grid[:, col]:  # Check column
            return False
        x0, y0 = (col // 3) * 3, (row // 3) * 3
        if num in grid[y0:y0+3, x0:x0+3]:  # Check square
            return False
        return True

    def generate_puzzle(self, level=50):
        # First, clear the grid
        self.grid = np.zeros((9, 9), dtype=int)
        
        # Fill the grid with a random solution
        if not self.solve():
            raise Exception("Failed to generate a Sudoku puzzle")

        # Now remove a number of digits to create a puzzle
        attempts = level
        while attempts > 0:
            row, col = random.randint(0, 8), random.randint(0, 8)
            if self.grid[row][col] != 0:  # Only remove if the cell is not already empty
                self.grid[row][col] = 0  # Remove a number to create a puzzle
                attempts -= 1

        return self.grid  # Return only the puzzle

# Usage example
sudoku = Sudoku()
puzzle = sudoku.generate_puzzle(level=50)  # Generate a puzzle
print("-" * 21)  # Print the top border of the Sudoku
for i, row in enumerate(puzzle):
    for j, num in enumerate(row):
        # Print number or dot for empty space; add vertical separators
        print(num if num != 0 else '.', end=' ')
        if j == 2 or j == 5:  # Add vertical dividers after the 3rd and 6th column
            print("|", end=' ')
    print()  # Move to the next line
    if i == 2 or i == 5:  # Add horizontal dividers after the 3rd and 6th row
        print("-" * 21)
print("-" * 21)  # Print the bottom border of the Sudoku

sudoku.solve()  # Solve the puzzle
print("Solved Puzzle:")
print("-" * 21)  # Print the top border of the Sudoku
for i, row in enumerate(sudoku.grid):
    for j, num in enumerate(row):
        # Print number or dot for empty space; add vertical separators
        print(num if num != 0 else '.', end=' ')
        if j == 2 or j == 5:  # Add vertical dividers after the 3rd and 6th column
            print("|", end=' ')
    print()  # Move to the next line
    if i == 2 or i == 5:  # Add horizontal dividers after the 3rd and 6th row
        print("-" * 21)
print("-" * 21)  # Print the bottom border of the Sudoku