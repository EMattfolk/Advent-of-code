const DIRS: [(i32, i32); 8] = [
    (-1, 0),
    (-1, -1),
    (0,  -1),
    (1,  -1),
    (1,  0),
    (1,  1),
    (0,  1),
    (-1, 1),
];

fn in_bounds(x: i32, y: i32, grid: &Vec<Vec<char>>) -> bool {
    x >= 0 && y >= 0 && (x as usize) < grid[0].len() && (y as usize) < grid.len()
}

fn adjacent(x: usize,
            y: usize,
            matrix: &Vec<Vec<Vec<(usize, usize)>>>,
            grid: &Vec<Vec<char>>) -> usize {
    matrix[y][x].iter()
        .map(|(nx, ny)| grid[*ny][*nx])
        .filter(|c| *c == '#')
        .count()
}

fn adjacent_points(x: i32, y: i32, search: bool, grid: &Vec<Vec<char>>) -> Vec<(usize, usize)> {
    let mut adj = Vec::new();
    for (ox, oy) in &DIRS {
        let (mut nx, mut ny) = (x + ox, y + oy);
        while in_bounds(nx, ny, grid) {
            let (nyu, nxu) = (ny as usize, nx as usize);
            if grid[nyu][nxu] == '#' || grid[nyu][nxu] == 'L' {
                adj.push((nxu, nyu));
                break;
            }
            nx += ox;
            ny += oy;
            if !search { break; }
        }
    }

    adj
}

fn adjacency_matrix(grid: &Vec<Vec<char>>, search: bool) -> Vec<Vec<Vec<(usize, usize)>>> {
    let mut matrix = Vec::new();
    for y in 0..grid.len() {
        let mut row = Vec::new();
        for x in 0..grid[0].len() {
            row.push(adjacent_points(x as i32, y as i32, search, grid));
        }
        matrix.push(row);
    }

    matrix
}

fn find_occupied(mut grid: Vec<Vec<char>>, part2: bool) -> usize {

    let mut new_grid = grid.clone();
    let matrix = adjacency_matrix(&grid, part2);
    let mut changed = true;

    let adj_lim = if part2 { 5 } else { 4 };

    while changed {
        changed = false;

        for y in 0..grid.len() {
            for x in 0..grid[0].len() {
                if grid[y][x] == 'L' && adjacent(x, y, &matrix, &grid) == 0 {
                    new_grid[y][x] = '#';
                    changed = true;
                } else if grid[y][x] == '#' && adjacent(x, y, &matrix, &grid) >= adj_lim {
                    new_grid[y][x] = 'L';
                    changed = true;
                } else {
                    new_grid[y][x] = grid[y][x];
                }
            }
        }

        let temp = grid;
        grid = new_grid;
        new_grid = temp;
    }

    grid.iter()
        .map(|r| r.iter().filter(|c| **c == '#').count())
        .sum()
}

pub fn solve(input: String) -> String {
    let grid: Vec<Vec<char>> = input
        .split_whitespace()
        .map(|l| l.chars().collect())
        .collect();

    let ans1 = find_occupied(grid.clone(), false);
    let ans2 = find_occupied(grid.clone(), true);

    format!("{}, {}", ans1, ans2)
}
