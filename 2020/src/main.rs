use std::fs::read_to_string;
use std::time::SystemTime;
use std::thread;

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
mod day19;
mod day20;
mod day21;
mod day22;
mod day23;
mod day24;
mod day25;

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
        day19::solve,
        day20::solve,
        day21::solve,
        day22::solve,
        day23::solve,
        day24::solve,
        day25::solve,
    ];

    let mut threads = Vec::new();

    for i in 0..day_fns.len() {
        threads.push(thread::spawn(move || {
            let day = i + 1;
            let day_input = read_to_string(format!("input/day{:02}.txt", day))
                .unwrap()
                .to_string();

            let st = SystemTime::now();
            let ans = day_fns[i](day_input);
            let elapsed = st.elapsed().unwrap().as_nanos() as f64 / 1000000.0;

            (ans, elapsed)
        }));
    }

    for (i, t) in threads.into_iter().enumerate() {
        let (ans, elapsed) = t.join().unwrap();
        println!("Day {:>2}: {:8.3}ms - {}", i + 1, elapsed, ans);
    }
}
