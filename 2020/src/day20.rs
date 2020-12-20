use std::collections::HashSet;

const TILE_SIZE: usize = 10;
const TILE_SIZE_I: i32 = TILE_SIZE as i32;
const SEA_SIZE: usize = (TILE_SIZE - 2) * GRID_SIZE;
const TRANSFORMS: [Transform; 8] = [
    Transform{
        offset: (0, 0),
        matrix: ((1, 0), (0, 1))
    },
    Transform{
        offset: (TILE_SIZE_I - 1, 0),
        matrix: ((-1, 0), (0, 1))
    },
    Transform{
        offset: (0, TILE_SIZE_I - 1),
        matrix: ((1, 0), (0, -1))
    },
    Transform{
        offset: (TILE_SIZE_I - 1, TILE_SIZE_I - 1),
        matrix: ((-1, 0), (0, -1))
    },
    Transform{
        offset: (0, 0),
        matrix: ((0, 1), (1, 0))
    },
    Transform{
        offset: (TILE_SIZE_I - 1, 0),
        matrix: ((0, -1), (1, 0))
    },
    Transform{
        offset: (0, TILE_SIZE_I - 1),
        matrix: ((0, 1), (-1, 0))
    },
    Transform{
        offset: (TILE_SIZE_I - 1, TILE_SIZE_I - 1),
        matrix: ((0, -1), (-1, 0))
    }
];
const GRID_SIZE: usize = 12;

#[derive(Clone)]
struct Tile {
    id: u32,
    grid: Vec<Vec<char>>,
    transform: Transform,
}

impl Tile {

    fn new() -> Self {
        Self{ id: 0, grid: Vec::new(), transform: TRANSFORMS[0] }
    }

    fn get(&self, x: usize, y: usize) -> char {
        let (tx, ty) = self.transform.transform(x, y);
        self.grid[ty][tx]
    }

    //fn show(&self) {
    //    for i in 0..self.grid.len() {
    //        for j in 0..self.grid.len() {
    //            print!("{}", self.get(j, i));
    //        }
    //        println!();
    //    }
    //}
}

#[derive(Clone, Copy)]
struct Transform {
    offset: (i32, i32),
    matrix: ((i32, i32), (i32, i32)),
}

impl Transform {
    fn transform(self, x: usize, y: usize) -> (usize, usize) {
        let (tx, ty) =
        (self.offset.0 + (x as i32) * (self.matrix.0).0 + (y as i32) * (self.matrix.0).1,
         self.offset.1 + (x as i32) * (self.matrix.1).0 + (y as i32) * (self.matrix.1).1);

        (tx as usize, ty as usize)
    }
}

fn fill_grid(grid: &mut Vec<Vec<Tile>>, tiles: &mut Vec<Tile>, x: usize, y: usize) -> bool {
    if x == 0 && y == GRID_SIZE {
        return true;
    }

    let nx = (x + 1) % GRID_SIZE;
    let ny = y + (x + 1) / GRID_SIZE;

    for i in (0..tiles.len()).rev() {
        'tloop: for t in &TRANSFORMS {
            tiles[i].transform = *t;

            if x > 0 {
                for k in 0..TILE_SIZE - 1 {
                    if grid[y][x-1].get(TILE_SIZE - 1, k) != tiles[i].get(0, k) {
                        continue 'tloop;
                    }
                }
            }

            if y > 0 {
                for k in 0..TILE_SIZE - 1 {
                    if grid[y-1][x].get(k, TILE_SIZE - 1) != tiles[i].get(k, 0) {
                        continue 'tloop;
                    }
                }
            }

            grid[y].push(tiles.remove(i));
            if fill_grid(grid, tiles, nx, ny) {
                return true;
            }
            tiles.insert(i, grid[y].pop().unwrap());
        }
    }

    return false;
}

pub fn solve(input: String) -> String {
    let mut tiles = Vec::new();

    let mut lines = input.lines();

    while let Some(head) = lines.next() {
        let id = head[5..head.len()-1].parse().unwrap();
        let mut grid = vec![Vec::with_capacity(TILE_SIZE); TILE_SIZE];
        for i in 0..TILE_SIZE {
            let line = lines.next().unwrap();
            for c in line.chars() {
                grid[i].push(c);
            }
        }

        tiles.push(Tile{id: id, grid: grid, transform: TRANSFORMS[0]});
        lines.next();
    }

    //for t in &TRANSFORMS {
    //    tiles[0].transform = *t;
    //    tiles[0].show();
    //    println!();
    //}

    let mut grid = vec![Vec::with_capacity(GRID_SIZE); GRID_SIZE];

    fill_grid(&mut grid, &mut tiles, 0, 0);

    let ans1 = (grid[0][0].id as u64)
             * (grid[0][11].id as u64)
             * (grid[11][0].id as u64) 
             * (grid[11][11].id as u64);

    let mut sea = Tile::new();

    for y in 0..SEA_SIZE {
        let gy = y / (TILE_SIZE - 2);
        let ty = (y % (TILE_SIZE - 2)) + 1;
        sea.grid.push(Vec::with_capacity(SEA_SIZE));
        for x in 0..SEA_SIZE {
            let gx = x / (TILE_SIZE - 2);
            let tx = (x % (TILE_SIZE - 2)) + 1;
            sea.grid[y].push(grid[gy][gx].get(tx, ty));
        }
    }

    let mut sea_transforms: Vec<_> = TRANSFORMS.iter().cloned().collect();
    for mut t in sea_transforms.iter_mut() {
        if t.offset.0 > 0 {
            t.offset.0 = (SEA_SIZE - 1) as i32;
        }
        if t.offset.1 > 0 {
            t.offset.1 = (SEA_SIZE - 1) as i32;
        }
    }

    let mut ans2 = 0;

    for t in sea_transforms.iter() {
        sea.transform = *t;
        let mut found = HashSet::new();
        for y in 0..SEA_SIZE - 2 {
            for x in 0..SEA_SIZE - 19 {
                if sea.get(x + 0,  y + 1) == '#' &&
                   sea.get(x + 1,  y + 2) == '#' &&
                   sea.get(x + 4,  y + 2) == '#' &&
                   sea.get(x + 5,  y + 1) == '#' &&
                   sea.get(x + 6,  y + 1) == '#' &&
                   sea.get(x + 7,  y + 2) == '#' &&
                   sea.get(x + 10, y + 2) == '#' &&
                   sea.get(x + 11, y + 1) == '#' &&
                   sea.get(x + 12, y + 1) == '#' &&
                   sea.get(x + 13, y + 2) == '#' &&
                   sea.get(x + 16, y + 2) == '#' &&
                   sea.get(x + 17, y + 1) == '#' &&
                   sea.get(x + 18, y + 0) == '#' &&
                   sea.get(x + 18, y + 1) == '#' &&
                   sea.get(x + 19, y + 1) == '#' {
                       found.insert((x + 0,  y + 1));
                       found.insert((x + 1,  y + 2));
                       found.insert((x + 4,  y + 2));
                       found.insert((x + 5,  y + 1));
                       found.insert((x + 6,  y + 1));
                       found.insert((x + 7,  y + 2));
                       found.insert((x + 10, y + 2));
                       found.insert((x + 11, y + 1));
                       found.insert((x + 12, y + 1));
                       found.insert((x + 13, y + 2));
                       found.insert((x + 16, y + 2));
                       found.insert((x + 17, y + 1));
                       found.insert((x + 18, y + 0));
                       found.insert((x + 18, y + 1));
                       found.insert((x + 19, y + 1));
                }
            }
        }

        if found.len() > 0 {
            let tot: usize = sea.grid.iter()
                .map(|r| r.iter().filter(|c| **c == '#').count())
                .sum();
            ans2 = tot - found.len();
            break;
        }
    }

    format!("{}, {}", ans1, ans2)
}
