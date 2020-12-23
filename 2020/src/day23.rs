pub fn solve(input: String) -> String {
    let ans1 = 0;
    let ans2 = 0;

    let mut cups: Vec<_> = input.chars()
        .take(9)
        .map(|c| c.to_digit(10).unwrap() as usize)
        .collect();
    let mut held = Vec::with_capacity(3);

    let mut current = 0;

    for _ in 0..100 {
        for __ in 0..3 {
            if current == cups.len() - 1 {
                held.push(cups.remove(0));
                current -= 1;
            } else {
                held.push(cups.remove(current + 1));
            }
        }

        let mut dest = cups[current] - 1;
        let mut found = true;
        while found {
            found = false;
            if dest == 0 {
                dest = 9;
                found = true;
            } else if held.contains(&dest) {
                dest -= 1;
                found = true;
            }
        }

        current = cups[current];
        let pos = cups.iter().position(|n| *n == dest).unwrap();
        for __ in 0..3 {
            cups.insert(pos + 1, held.pop().unwrap());
        }

        current = cups.iter().position(|n| *n == current).unwrap();
        current = (current + 1) % cups.len();
    }

    println!("{:?}", cups);

    format!("{}, {}", ans1, ans2)
}
