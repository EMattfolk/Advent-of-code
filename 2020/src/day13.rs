pub fn solve(input: String) -> String {
    let mut lines = input.lines();

    let time: i64 = lines.next().unwrap().parse().unwrap();
    let (mut min, mut minv) = (0, time);

    let mut mult = 1;
    let mut earliest: i64 = 0;
    for (i, rate) in lines.next().unwrap().split(',').enumerate() {
        if rate.chars().next().unwrap() == 'x' {
            continue;
        }

        let rate: i64 = rate.parse().unwrap();
        let wait: i64 = (-time).rem_euclid(rate);

        if wait < minv {
            min = rate;
            minv = wait;
        }

        while (earliest + i as i64) % rate != 0 {
            earliest += mult;
        }

        mult *= rate;
    }

    let ans1 = min * minv;
    let ans2 = earliest;

    format!("{}, {}", ans1, ans2)
}
