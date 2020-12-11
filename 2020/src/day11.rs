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

fn adjacent(x: i32, y: i32, search: bool, grid: &Vec<Vec<char>>) -> u32 {
    let mut adj = 0;
    for (ox, oy) in &DIRS {
        let (mut nx, mut ny) = (x + ox, y + oy);
        while in_bounds(nx, ny, grid) && grid[ny as usize][nx as usize] != 'L' {
            if grid[ny as usize][nx as usize] == '#' {
                adj += 1;
                break;
            }
            nx += ox;
            ny += oy;
            if !search { break; }
        }
    }

    adj
}

fn find_occupied(mut grid: Vec<Vec<char>>, part2: bool) -> u32 {

    let mut occupied = 0;
    let mut new_grid = grid.clone();
    let mut changed = true;

    let adj_lim = if part2 { 5 } else { 4 };

    while changed {
        changed = false;

        for y in 0..grid.len() {
            let yi = y as i32;
            for x in 0..grid[0].len() {
                let xi = x as i32;
                if grid[y][x] == 'L' && adjacent(xi, yi, part2, &grid) == 0 {
                    new_grid[y][x] = '#';
                    changed = true;
                } else if grid[y][x] == '#' && adjacent(xi, yi, part2, &grid) >= adj_lim {
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

    for r in &grid {
        for c in r {
            if *c == '#' {
                occupied += 1;
            }
        }
    }

    occupied
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
