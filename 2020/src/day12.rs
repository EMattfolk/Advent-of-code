use aoc::Point;

fn update_pos(d: char, v: i32, pos: &mut Point, dir: &mut Point) {
    match d {
        'N' => *pos += Point::new(0, -v),
        'S' => *pos += Point::new(0, v),
        'E' => *pos += Point::new(v, 0),
        'W' => *pos += Point::new(-v, 0),
        'L' => for _ in 0..v/90 { dir.turn_left(); },
        'R' => for _ in 0..v/90 { dir.turn_right(); },
        'F' => *pos += *dir * v,
        _ => {}
    }
}

fn update_pos2(d: char, mut v: i32, pos: &mut Point, dir: &mut Point) {
    match d {
        'N' => *dir += Point::new(0, -v),
        'S' => *dir += Point::new(0, v),
        'E' => *dir += Point::new(v, 0),
        'W' => *dir += Point::new(-v, 0),
        'L' => while v > 0 { dir.turn_left(); v -= 90; },
        'R' => while v > 0 { dir.turn_right(); v -= 90; },
        'F' => *pos += *dir * v,
        _ => {}
    }
}

pub fn solve(input: String) -> String {
    let mut pos = Point::new(0, 0);
    let mut dir = Point::new(1, 0);
    let mut pos2 = Point::new(0, 0);
    let mut waypoint = Point::new(10, -1);

    for line in input.split_whitespace() {
        let d = line.chars().next().unwrap();
        let v = line[1..].parse().unwrap();
        update_pos(d, v, &mut pos, &mut dir);
        update_pos2(d, v, &mut pos2, &mut waypoint);
    }

    let ans1 = pos.x.abs() + pos.y.abs();
    let ans2 = pos2.x.abs() + pos2.y.abs();

    format!("{}, {}", ans1, ans2)
}
