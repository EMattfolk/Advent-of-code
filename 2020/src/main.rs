use std::fs;
use std::time::SystemTime;

mod day01;
mod day02;
mod day03;
mod day04;
mod day05;
mod day06;
mod day07;
mod day08;
mod day09;
mod day10;
mod day11;
mod day12;
mod day13;
mod day14;
mod day15;
mod day16;
mod day17;
mod day18;

fn main() {

    let day_fns = [
        day01::solve,
        day02::solve,
        day03::solve,
        day04::solve,
        day05::solve,
        day06::solve,
        day07::solve,
        day08::solve,
        day09::solve,
        day10::solve,
        day11::solve,
        day12::solve,
        day13::solve,
        day14::solve,
        day15::solve,
        day16::solve,
        day17::solve,
        day18::solve,
    ];

    for i in 0..day_fns.len() {
        let day = i + 1;
        let day_input = fs::read_to_string(format!("input/day{:02}.txt", day))
            .unwrap()
            .to_string();

        let st = SystemTime::now();
        let ans = day_fns[i](day_input);
        let elapsed = st.elapsed().unwrap().as_nanos() as f64 / 1000000.0;

        println!("Day {:>2}: {:8.3}ms - {}", day, elapsed, ans);
    }
}
