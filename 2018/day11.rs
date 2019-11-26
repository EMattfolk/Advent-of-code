const SERIAL: i32 = 3613;

fn get_cell (x: i32, y: i32) -> i32
{
    let rackid = x + 11;
    let mut cell: i32 = rackid * (y + 1) + SERIAL;
    cell *= rackid;
    cell = (cell / 100) % 10;
    cell -= 5;

    cell
}

fn get_adjacent_sum (x: i32, y: i32, size: i32, grid: &[[i32; 300]; 300]) -> i32
{
    let mut s: i32 = 0;
    for i in x..(x + size) {
        for j in y..(y + size) {
            s += grid[j as usize][i as usize];
        }
    }

    s
}

fn get_max (size: i32, grid: &[[i32; 300]; 300]) -> (i32, (i32, i32, i32))
{
    let mut pos: (i32, i32, i32) = (0, 0, 0);
    let mut s: i32;
    let mut m: i32 = -1000;
    let mut init_sum: i32 = get_adjacent_sum(0, 0, size, &grid);
    for y in 0..(300 - size) {
        s = init_sum;
        for x in 0..(300 - size) {
            if s > m {
                pos = (x + 1, y + 1, size);
                m = s;
            }
            for i in y..(y + size) {
                s += grid[i as usize][(x + size) as usize] - grid[i as usize][x as usize];
            }
        }
        for i in 0..size {
            init_sum += grid[(y + size) as usize][i as usize] - grid[y as usize][i as usize];
        }
    }

    (m, pos)
}

fn main ()
{
    let mut grid: [[i32; 300]; 300] = [[0; 300]; 300];

    for x in 0..300 {
        for y in 0..300 {
            grid[y][x] = get_cell(x as i32, y as i32);
        }
    }

    let res1: (i32, (i32, i32, i32)) = get_max(3, &grid);
    let mut res2: (i32, (i32, i32, i32)) = (0, (0, 0, 0));
    for size in 1..300 {
        let temp = get_max(size, &grid);
        if temp.0 > res2.0 {
            res2 = temp;
        }
    }

    println!("{},{}", (res1.1).0, (res1.1).1);
    println!("{},{},{}", (res2.1).0, (res2.1).1, (res2.1).2);
}
