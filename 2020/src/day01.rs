pub fn solve(input: String) -> String {
    let numbers: Vec<u32> = input.split_whitespace().map(|x| x.parse().unwrap()).collect();

    let mut ans1 = 0;
    let mut ans2 = 0;
    for i in 0..numbers.len() {
        for j in i+1..numbers.len() {
            if numbers[i] + numbers[j] == 2020 {
                ans1 = numbers[i] * numbers[j];
            }
            for k in j+1..numbers.len() {
                if numbers[i] + numbers[j] + numbers[k] == 2020 {
                    ans2 = numbers[i] * numbers[j] * numbers[k];
                }
            }
        }
    }

    format!("{}, {}", ans1, ans2)
}
