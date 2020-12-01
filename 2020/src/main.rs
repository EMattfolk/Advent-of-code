use std::fs;

mod day01;

fn main() {
    let day_input = fs::read_to_string("input/day01.txt").unwrap().to_string();

    println!("{}", day01::solve(day_input));
}
