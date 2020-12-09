pub fn solve(input: String) -> String {
    let mut ans1 = 0;

    let numbers: Vec<u64> = input
        .split_whitespace()
        .map(|n| n.parse().unwrap())
        .collect();

    for i in 25..numbers.len() {
        let mut found = false;
        'outer: for j in i-25..i {
            for k in j+1..i {
                if numbers[j] + numbers[k] == numbers[i] {
                    found = true;
                    break 'outer;
                }
            }
        }
        if !found {
            ans1 = numbers[i];
            break;
        }
    }

    let mut cum_sum: Vec<u64> = vec![0];
    for n in &numbers {
        cum_sum.push(n + cum_sum[cum_sum.len() - 1]);
    }

    let mut i = 0;
    let mut j = 2;
    while cum_sum[j] - cum_sum[i] != ans1 {
        if cum_sum[j] - cum_sum[i] < ans1 {
            j += 1;
        } else {
            i += 1;
        }
    }

    let ans2 = numbers[i..j].iter().max().unwrap()
               + numbers[i..j].iter().min().unwrap();

    format!("{}, {}", ans1, ans2)
}
