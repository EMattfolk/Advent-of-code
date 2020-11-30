use std::fs;

mod day01;

fn main() {
    let day_input = fs::read_to_string("input/day01.txt").unwrap().to_string();

    for word in day_input.split_whitespace() {
        println!("'{}'", word);
    }

    println!("{}", day01::solve());
}
