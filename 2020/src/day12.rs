use std::ops::Add;
use std::ops::Mul;
use std::ops::AddAssign;

#[derive(Debug, Hash, Copy, Clone, PartialEq)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Point {
        Point{ x: x, y: y }
    }

    fn turn_left(&mut self) {
        let temp = self.x;
        self.x = self.y;
        self.y = -temp;
    }

    fn turn_right(&mut self) {
        let temp = self.x;
        self.x = -self.y;
        self.y = temp;
    }
}

impl Add for Point {
    type Output = Self;

    fn add(self, other: Self) -> Self {
        Self {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

impl AddAssign for Point {
    fn add_assign(&mut self, other: Self) {
        self.x += other.x;
        self.y += other.y;
    }
}

impl Mul<i32> for Point {
    type Output = Self;

    fn mul(self, other: i32) -> Self {
        Self {
            x: self.x * other,
            y: self.y * other,
        }
    }
}

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
