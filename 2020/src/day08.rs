use std::collections::HashSet;

fn run_program(program: &Vec<(&str, i32)>) -> (i32, bool) {
    let mut visited = HashSet::new();
    let mut acc = 0;
    let mut i: i32 = 0;
    while !visited.contains(&i) && (i as usize) < program.len() {
        visited.insert(i);

        let (op, val) = program[i as usize];

        if op == "acc" {
            acc += val;
        } else if op == "jmp" {
            i += val - 1;
        } else if op == "nop" {
            // Do nothing
        }

        i += 1;
    }

    (acc, !visited.contains(&i))
}

pub fn solve(input: String) -> String {
    let mut ans2 = 0;

    let mut program: Vec<(&str, i32)> = input
        .lines()
        .map(|l| l.split_whitespace())
        .map(|mut s| (s.next().unwrap(), s.next().unwrap().parse().unwrap()))
        .collect();

    let (ans1, _) = run_program(&program);

    for i in 0..program.len() {
        let (op, _) = program[i];

        if op == "jmp" {
            program[i].0 = "nop";
            let (acc, terminated) = run_program(&program);
            if terminated {
                ans2 = acc;
                break;
            }
            program[i].0 = "jmp";
        } else if op == "nop" {
            program[i].0 = "jmp";
            let (acc, terminated) = run_program(&program);
            if terminated {
                ans2 = acc;
                break;
            }
            program[i].0 = "nop";
        }
    }


    format!("{}, {}", ans1, ans2)
}
