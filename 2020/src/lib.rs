use std::ops::Add;
use std::ops::Mul;
use std::ops::AddAssign;

#[derive(Debug, Hash, Copy, Clone, PartialEq, Eq)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

impl Point {
    pub fn new(x: i32, y: i32) -> Point {
        Point{ x: x, y: y }
    }

    pub fn turn_left(&mut self) {
        let temp = self.x;
        self.x = self.y;
        self.y = -temp;
    }

    pub fn turn_right(&mut self) {
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
