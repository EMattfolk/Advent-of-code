use std::cmp::max;
use std::collections::HashSet;

pub fn solve(input: String) -> String {
    let mut ans1 = 0;
    let mut ans2 = 0;

    let mut seen = HashSet::new();
    for line in input.split_whitespace() {
        let mut id = 0;
        let mut pos = 512;
        for c in line.chars() {
            if c == 'B' || c == 'R' {
                id += pos;
            }
            pos /= 2;
        }

        ans1 = max(id, ans1);
        seen.insert(id);
    }

    for i in (0..=ans1).rev() {
        if !seen.contains(&i) && seen.contains(&(i+1)) && seen.contains(&(i-1)) {
            ans2 = i;
            break;
        }
    }

    format!("{}, {}", ans1, ans2)
}
