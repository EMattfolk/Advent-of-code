use std::collections::HashMap;

fn add_neighbors3(pos: &(i8, i8, i8, i8), neighbors: &mut HashMap<(i8, i8, i8, i8), u8>) {
    for ox in -1..=1 {
        for oy in -1..=1 {
            for oz in -1..=1 {
                let npos = (pos.0 + ox, pos.1 + oy, pos.2 + oz, 0);
                let entry = neighbors.entry(npos).or_insert(0);
                if ox == oy && oy == oz && oz == 0 { continue; }
                *entry += 1;
            }
        }
    }
}

fn add_neighbors4(pos: &(i8, i8, i8, i8), neighbors: &mut HashMap<(i8, i8, i8, i8), u8>) {
    for ox in -1..=1 {
        for oy in -1..=1 {
            for oz in -1..=1 {
                for ow in -1..=1 {
                    let npos = (pos.0 + ox, pos.1 + oy, pos.2 + oz, pos.3 + ow);
                    let entry = neighbors.entry(npos).or_insert(0);
                    if ox == oy && oy == oz && oz == ow && ow == 0 { continue; }
                    *entry += 1;
                }
            }
        }
    }
}

fn run_iters(mut space: HashMap<(i8, i8, i8, i8), bool>, use_fourth: bool) -> u32 {
    let mut neighbors = HashMap::new();

    for _ in 0..6 {

        neighbors.clear();

        for (pos, active) in space.iter() {
            if *active {
                if use_fourth {
                    add_neighbors4(pos, &mut neighbors);
                } else {
                    add_neighbors3(pos, &mut neighbors);
                }
            }
        }

        for (pos, count) in neighbors.iter() {
            let space_entry = space.entry(*pos).or_insert(false);
            if *space_entry {
                *space_entry = *count == 2 || *count == 3;
            } else {
                *space_entry = *count == 3;
            }
        }
    }

    space.iter().map(|(_, active)| *active as u32).sum()
}

pub fn solve(input: String) -> String {
    let mut space = HashMap::new();

    for (i, line) in input.lines().enumerate() {
        for (j, c) in line.chars().enumerate() {
            space.insert((j as i8, i as i8, 0i8, 0i8), c == '#');
        }
    }

    let ans1 = run_iters(space.clone(), false);
    let ans2 = run_iters(space.clone(), true);

    format!("{}, {}", ans1, ans2)
}
