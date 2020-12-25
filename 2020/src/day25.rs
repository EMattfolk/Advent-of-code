fn mod_pow(n: u64, mut e: u64, m: u64) -> u64 {
    let mut p = n;
    let mut res = 1;
    while e > 0 {
        if e % 2 == 1 {
            res *= p;
            res %= m;
        }

        p = (p * p) % m;
        e /= 2;
    }

    res
}

pub fn solve(input: String) -> String {
    let pub_keys: Vec<u64> = input
        .split_whitespace()
        .map(|k| k.parse().unwrap())
        .collect();

    let pub1 = pub_keys[0];
    let pub2 = pub_keys[1];

    let subject = 7;
    let m = 20201227;

    let mut loop_size1 = 0;
    let mut value1 = 1;
    while value1 != pub1 {
        value1 *= subject;
        value1 %= m;
        loop_size1 += 1;
    }

    let ans = mod_pow(pub2, loop_size1, m);

    format!("{}", ans)
}
