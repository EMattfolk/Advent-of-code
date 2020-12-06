use std::collections::HashMap;

pub fn solve(input: String) -> String {
    let mut ans1 = 0;
    let mut ans2 = 0;

    let mut seen: HashMap<char, u32> = HashMap::new();
    let mut lines = 0;
    for line in input.lines().chain(vec![""]) {
        if line.len() == 0 {
            ans1 += seen.len();

            for (_key, &val) in seen.iter() {
                if val == lines {
                    ans2 += 1;
                }
            }

            seen.clear();
            lines = 0;
        } else {
            lines += 1;
        }

        for c in line.chars() {
            let count = seen.entry(c).or_insert(0);
            *count += 1;
        }

    }

    ans1 += seen.len();

    format!("{}, {}", ans1, ans2)
}
