// https://medium.com/p/cbebc9c27a62

use std::thread;

const SIZE: usize = 9;
const SUBGRID_SIZE: usize = 3;

type SudokuGrid = [[u8; SIZE]; SIZE];

fn is_safe(grid: &SudokuGrid, row: usize, col: usize, num: u8) -> bool {
    // Check if it's safe to place 'num' at position (row, col) in the grid
    !used_in_row(grid, row, num) && !used_in_col(grid, col, num) && !used_in_subgrid(grid, row - row % 3, col - col % 3, num)
}

fn used_in_row(grid: &SudokuGrid, row: usize, num: u8) -> bool {
    // Check if 'num' is already used in the same row
    grid[row].iter().any(|&x| x == num)
}

fn used_in_col(grid: &SudokuGrid, col: usize, num: u8) -> bool {
    // Check if 'num' is already used in the same column
    grid.iter().any(|row| row[col] == num)
}

fn used_in_subgrid(grid: &SudokuGrid, start_row: usize, start_col: usize, num: u8) -> bool {
    // Check if 'num' is already used in the 3x3 subgrid
    for row in 0..SUBGRID_SIZE {
        for col in 0..SUBGRID_SIZE {
            if grid[row + start_row][col + start_col] == num {
                return true;
            }
        }
    }
    false
}

fn solve_sudoku(grid: &mut SudokuGrid) -> bool {
    // Find an empty position in the grid
    let mut empty_pos = (SIZE, SIZE);
    for row in 0..SIZE {
        for col in 0..SIZE {
            if grid[row][col] == 0 {
                empty_pos = (row, col);
                break;
            }
        }
        if empty_pos != (SIZE, SIZE) {
            break;
        }
    }

    // If there is no empty position left, the puzzle is solved
    if empty_pos == (SIZE, SIZE) {
        return true;
    }

    let (row, col) = empty_pos;

    // Try filling the empty position with numbers 1 to 9
    for num in 1..=SIZE as u8 {
        if is_safe(grid, row, col, num) {
            grid[row][col] = num;

            // Recursively solve the Sudoku puzzle
            if solve_sudoku(grid) {
                return true;
            }

            // Backtrack if the current configuration doesn't lead to a solution
            grid[row][col] = 0;
        }
    }
    false
}

fn solve_subgrid(grid: &SudokuGrid, row: usize, col: usize) -> SudokuGrid {
    let mut subgrid_solution = [[0; SIZE]; SIZE];

    for i in 0..SUBGRID_SIZE {
        for j in 0..SUBGRID_SIZE {
            subgrid_solution[i + row][j + col] = grid[i + row][j + col];
        }
    }

    solve_sudoku(&mut subgrid_solution);

    subgrid_solution
}

fn combine_solutions(mut sudoku_grid: SudokuGrid, solved_subgrids: Vec<SudokuGrid>) -> SudokuGrid {
    for (idx, subgrid) in solved_subgrids.into_iter().enumerate() {
        let row = (idx / 3) * 3;
        let col = (idx % 3) * 3;
        for i in 0..SUBGRID_SIZE {
            for j in 0..SUBGRID_SIZE {
                sudoku_grid[row + i][col + j] = subgrid[i][j];
            }
        }
    }
    sudoku_grid
}

fn main() {
    let mut sudoku_grid: SudokuGrid = [
        [5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9],
    ];

    // Create a vector to hold the thread handles
    let mut handles = vec![];

    // Iterate over each subgrid and spawn a thread to solve it concurrently
    for row in (0..SIZE).step_by(SUBGRID_SIZE) {
        for col in (0..SIZE).step_by(SUBGRID_SIZE) {
            let subgrid = sudoku_grid.clone(); // Make a clone of the grid for each thread
            let handle = thread::spawn(move || {
                solve_subgrid(&subgrid, row, col)
            });
            handles.push(handle);
        }
    }

    // Join all threads and collect results
    let mut solved_subgrids = vec![];
    for handle in handles {
        let subgrid = handle.join().unwrap(); // Wait for thread to finish and retrieve result
        solved_subgrids.push(subgrid);
    }

    // Combine solutions to form the final Sudoku grid
    let final_solution = combine_solutions(sudoku_grid, solved_subgrids);

    // Print the final solution
    println!("Final Sudoku Solution:");
    for row in final_solution.iter() {
        println!("{:?}", row);
    }
}