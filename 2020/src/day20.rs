use std::collections::{HashSet, HashMap};

type Adjacent = HashMap<(u32, Transform),
                        (HashSet<(u32, Transform)>, HashSet<(u32, Transform)>)>;

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

#[derive(Clone, Default)]
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

#[derive(Clone, Copy, Hash, PartialEq, Eq, Default)]
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

fn fill_grid(grid: &mut Vec<Vec<Tile>>, tiles: &mut HashMap<u32, Tile>, adjacent: &Adjacent, x: usize, y: usize) -> bool {
    if x == 0 && y == GRID_SIZE {
        return true;
    }

    let nx = (x + 1) % GRID_SIZE;
    let ny = y + (x + 1) / GRID_SIZE;

    let it: Vec<_> =
        if x == 0 && y == 0 {
            adjacent.keys().collect()
        } else if x == 0 {
            let above = &grid[y-1][x];
            (adjacent[&(above.id, above.transform)].0).iter().collect()
        } else if y == 0 {
            let beside = &grid[y][x-1];
            (adjacent[&(beside.id, beside.transform)].1).iter().collect()
        } else {
            let above = &grid[y-1][x];
            let beside = &grid[y][x-1];
            (adjacent[&(beside.id, beside.transform)].1)
               .intersection(&adjacent[&(above.id, above.transform)].0).collect()
        };

    for (id, t) in it {
        let mut tile = tiles.remove(id).unwrap();
        tile.transform = *t;
        grid[y].push(tile);
        if fill_grid(grid, tiles, adjacent, nx, ny) {
            return true;
        }
        tiles.insert(*id, grid[y].pop().unwrap());
    }

    return false;
}

pub fn solve(input: String) -> String {
    let mut tiles: HashMap<u32, Tile> = HashMap::new();
    let mut ids = Vec::new();

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

        tiles.insert(id, Tile{id: id, grid: grid, transform: TRANSFORMS[0]});
        ids.push(id);
        lines.next();
    }

    let mut adjacent: Adjacent = HashMap::new();

    for i in 0..ids.len() {
        for tr1 in &TRANSFORMS {
            tiles.entry(ids[i]).or_default().transform = *tr1;
            let mut lower = HashSet::new();
            let mut beside = HashSet::new();
            for j in 0..ids.len() {
                if i == j { continue; }

                for tr2 in &TRANSFORMS {
                    tiles.entry(ids[j]).or_default().transform = *tr2;

                    let t1 = &tiles[&ids[i]];
                    let t2 = &tiles[&ids[j]];

                    let mut ok = true;
                    for k in 0..TILE_SIZE {
                        if t1.get(k, TILE_SIZE - 1) != t2.get(k, 0) {
                            ok = false;
                            break;
                        }
                    }

                    if ok {
                        lower.insert((t2.id, *tr2));
                    }

                    ok = true;
                    for k in 0..TILE_SIZE {
                        if t1.get(TILE_SIZE - 1, k) != t2.get(0, k) {
                            ok = false;
                            break;
                        }
                    }

                    if ok {
                        beside.insert((t2.id, *tr2));
                    }
                }
            }
            adjacent.insert((tiles[&ids[i]].id, *tr1), (lower, beside));
        }
    }

    //for t in &TRANSFORMS {
    //    tiles[0].transform = *t;
    //    tiles[0].show();
    //    println!();
    //}

    let mut grid = vec![Vec::with_capacity(GRID_SIZE); GRID_SIZE];

    fill_grid(&mut grid, &mut tiles, &adjacent, 0, 0);

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
