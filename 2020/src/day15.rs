pub fn solve(input: String) -> String {
    let mut starting: Vec<_> = input
        .split(',')
        .map(|n| n.trim_end_matches(char::is_whitespace).parse().unwrap())
        .collect();

    let mut seen = vec![-1; 30000000];
    let mut spoken = vec![false; 30000000];
    let mut turn = 0;
    let mut last = 0;
    let mut last_spoken = false;

    while turn < 2020 {
        let current =
            if !starting.is_empty() {
                starting.remove(0)
            } else if !last_spoken {
                0
            } else {
                turn - 1 - seen[last as usize]
            };

        seen[last as usize] = turn - 1;

        last_spoken = spoken[current as usize];
        spoken[current as usize] = true;

        last = current;
        turn += 1;
    }

    let ans1 = last;

    while turn < 30000000 {
        let current =
            if !last_spoken {
                0
            } else {
                turn - 1 - seen[last as usize]
            };

        seen[last as usize] = turn - 1;

        last_spoken = spoken[current as usize];
        spoken[current as usize] = true;

        last = current;
        turn += 1;
    }

    let ans2 = last;

    format!("{}, {}", ans1, ans2)
}
