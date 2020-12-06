use std::fs;
use std::time::SystemTime;

mod day01;
mod day02;
mod day03;
mod day04;
mod day05;
mod day06;

fn main() {

    let days = 6;

    let day_fns = [
        day01::solve,
        day02::solve,
        day03::solve,
        day04::solve,
        day05::solve,
        day06::solve,
    ];

    for i in 0..days {
        let day = i + 1;
        let day_input = fs::read_to_string(format!("input/day{:02}.txt", day))
            .unwrap()
            .to_string();

        let st = SystemTime::now();
        let ans = day_fns[i](day_input);
        let elapsed = st.elapsed().unwrap().as_nanos() as f64 / 1000000.0;

        println!("Day {:>2}: {:.3}ms - {}", day, elapsed, ans);
    }
}
