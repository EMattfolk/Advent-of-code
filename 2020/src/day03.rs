pub fn solve(input: String) -> String {
    let mut ans1 = 0;
    let mut ans2: u64 = 1;

    let grid: Vec<Vec<char>> = input
        .split_whitespace()
        .map(|x| x.chars().collect())
        .collect();

    let height = grid.len();
    let width = grid[0].len();

    for mut slope in 0..4 {
        slope = slope * 2 + 1;
        let mut trees = 0;
        for i in 0..height {
            if grid[i][(i * slope) % width] == '#' {
                trees += 1;
            }
        }

        if slope == 3 {
            ans1 = trees;
        }

        ans2 *= trees;
    }

    let mut trees = 0;
    for i in 0..height/2 {
        if grid[i * 2][i % width] == '#' {
            trees += 1;
        }
    }

    ans2 *= trees;

    format!("{}, {}", ans1, ans2)
}
