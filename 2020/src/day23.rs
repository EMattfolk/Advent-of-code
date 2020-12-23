fn run_iters(start: usize, iters: usize, list: &mut Vec<(usize, usize)>) {

    let mut current = start;
    for _ in 0..iters {

        let mut to_move = (0, 0, 0);

        to_move.0 = list[current].1;
        to_move.1 = list[to_move.0].1;
        to_move.2 = list[to_move.1].1;

        let mut dest = if current == 0 { list.len() - 1 } else { current - 1 };
        while dest == to_move.0 || dest == to_move.1 || dest == to_move.2 {
            dest = if dest == 0 { list.len() - 1 } else { dest - 1 }
        }

        let new_next = list[to_move.2].1;
        list[current].1 = new_next;
        list[new_next].0 = current;

        let dest_next = list[dest].1;

        list[dest].1 = to_move.0;
        list[to_move.0].0 = dest;

        list[dest_next].0 = to_move.2;
        list[to_move.2].1 = dest_next;

        current = list[current].1;
    }
}

pub fn solve(input: String) -> String {
    let mut cups: Vec<_> = input.chars()
        .take(9)
        .map(|c| c.to_digit(10).unwrap() as usize)
        .collect();
    let mut list = vec![(0, 0); cups.len()];
    for i in 0..cups.len() {
        let pos = cups[i] - 1;
        let prev = if i == 0 { cups.len() - 1 } else { i - 1 };
        let next = (i + 1) % cups.len();
        list[pos] = (cups[prev] - 1, cups[next] - 1);
    }

    run_iters(cups[0] - 1, 100, &mut list);
    let mut ans1 = 0;
    let mut current = list[0].1;
    while current != 0 {
        ans1 *= 10;
        ans1 += current + 1;
        current = list[current].1;
    }

    cups.append(&mut (10..=1000000).collect());
    list = vec![(0, 0); cups.len()];
    for i in 0..cups.len() {
        let pos = cups[i] - 1;
        let prev = if i == 0 { cups.len() - 1 } else { i - 1 };
        let next = (i + 1) % cups.len();
        list[pos] = (cups[prev] - 1, cups[next] - 1);
    }

    run_iters(cups[0] - 1, 10000000, &mut list);

    let ans2 = (list[0].1 + 1) * (list[list[0].1].1 + 1);

    format!("{}, {}", ans1, ans2)
}
