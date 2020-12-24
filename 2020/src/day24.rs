use aoc::Point;
use std::collections::HashMap;

fn get_neighbors(pos: Point) -> [Point; 6] {
    [
        pos + Point::new(1, 0),
        pos + Point::new(-1, 0),
        pos + Point::new(1 - pos.y.rem_euclid(2), 1),
        pos + Point::new(-pos.y.rem_euclid(2), 1),
        pos + Point::new(1 - pos.y.rem_euclid(2), -1),
        pos + Point::new(-pos.y.rem_euclid(2), -1),
    ]
}

fn adjacent(pos: Point, tiles: &HashMap<Point, bool>) -> usize {
    get_neighbors(pos).iter()
        .map(|p| if tiles.contains_key(p) { (!tiles[p]) as usize } else { 0 })
        .sum()
}

pub fn solve(input: String) -> String {
    let mut tiles: HashMap<Point, bool> = HashMap::new();

    for line in input.lines() {

        let mut chars = line.chars();
        let mut pos = Point::new(0, 0);

        while let Some(c) = chars.next() {
            if c == 'e' {
                pos.x += 1;
            } else if c == 'w' {
                pos.x -= 1;
            } else if let Some(d) = chars.next() {
                if c == 's' {
                    if d == 'e' {
                        pos += Point::new(1 - pos.y.rem_euclid(2), 1);
                    } else {
                        pos += Point::new(-pos.y.rem_euclid(2), 1);
                    }
                } else {
                    if d == 'e' {
                        pos += Point::new(1 - pos.y.rem_euclid(2), -1);
                    } else {
                        pos += Point::new(-pos.y.rem_euclid(2), -1);
                    }
                }
            }
        }

        tiles.entry(pos).and_modify(|e| *e = !*e).or_insert(false);
    }

    let ans1: u32 = tiles.iter().map(|(_, v)| (!v) as u32).sum();

    for k in tiles.keys().cloned().collect::<Vec<_>>() {
        for n in &get_neighbors(k) {
            tiles.entry(*n).or_insert(true);
        }
    }

    let mut new_tiles = HashMap::new();
    for _ in 0..100 {

        new_tiles.clear();

        for (k, w) in tiles.iter() {
            let adj = adjacent(*k, &tiles);
            let new_w = if *w {
                adj != 2
            } else {
                adj == 0 || adj > 2
            };

            if !new_w {
                new_tiles.insert(*k, false);
                for n in &get_neighbors(*k) {
                    new_tiles.entry(*n).or_insert(true);
                }
            }
        }

        let temp = tiles;
        tiles = new_tiles;
        new_tiles = temp;
    }

    let ans2: u32 = tiles.iter().map(|(_, v)| (!v) as u32).sum();

    format!("{}, {}", ans1, ans2)
}
