pub fn solve(input: String) -> String {
    let mut adapters: Vec<_> = input
        .split_whitespace()
        .map(|n| n.parse().unwrap())
        .collect();

    adapters.push(0);
    adapters.sort();
    adapters.push(adapters[adapters.len()-1] + 3);

    let mut ones = 0;
    let mut threes = 0;
    for (a, b) in adapters.iter().zip(&adapters[1..]) {
        match b - a {
            3 => threes += 1,
            1 => ones += 1,
            _ => (),
        }
    }

    let ans1 = ones * threes;

    let mut ways: Vec<u64> = vec![0; adapters.len()];
    ways[0] = 1;

    for i in 0..adapters.len()-1 {
        let mut j = i + 1;
        while j < adapters.len() && adapters[j] - adapters[i] <= 3 {
            ways[j] += ways[i];
            j += 1;
        }
    }

    let ans2 = ways.last().unwrap();

    format!("{}, {}", ans1, ans2)
}
