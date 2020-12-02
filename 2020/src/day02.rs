pub fn solve(input: String) -> String {
    let mut ans1 = 0;
    let mut ans2 = 0;

    let input: Vec<&str> = input.split_whitespace().collect();

    let mut i: usize = 0;
    while i < input.len() {
        let limits: Vec<_> = input[i].split("-").map(|x| x.parse::<usize>().unwrap()).collect();
        let ch = input[i+1].chars().nth(0).unwrap();
        let num_ch = input[i+2].chars().filter(|&x| x == ch).count();

        if limits[0] <= num_ch && num_ch <= limits[1] {
            ans1 += 1;
        }

        let first_char = input[i+2].chars().nth(limits[0]-1).unwrap();
        let second_char = input[i+2].chars().nth(limits[1]-1).unwrap();

        if (ch == first_char || ch == second_char) && first_char != second_char {
            ans2 += 1;
        }

        i += 3;
    }

    format!("{}, {}", ans1, ans2)
}
