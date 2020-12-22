use std::collections::{VecDeque, HashSet};
use itertools::Itertools;

fn get_state(player: &VecDeque<usize>) -> String {
    player.iter().join(",")
}

fn recurse_combat(player1: &mut VecDeque<usize>, player2: &mut VecDeque<usize>) -> bool {

    let mut states = HashSet::new();

    while player1.len() > 0 && player2.len() > 0 {

        let state = if player1.len() < player2.len() {
                        get_state(player1)
                    } else {
                        get_state(player2)
                    };

        if states.contains(&state) {
            return true;
        }

        states.insert(state);

        let p1 = player1.pop_front().unwrap();
        let p2 = player2.pop_front().unwrap();

        let cmp =
            if p1 <= player1.len() && p2 <= player2.len() {
                recurse_combat(
                    &mut player1.iter().cloned().take(p1).collect(),
                    &mut player2.iter().cloned().take(p2).collect()
                )
            }
        else {
            p1 > p2
        };

        if cmp {
            player1.push_back(p1);
            player1.push_back(p2);
        } else {
            player2.push_back(p2);
            player2.push_back(p1);
        }
    }

    player1.len() > 0
}

pub fn solve(input: String) -> String {
    let mut lines = input.lines();

    let mut player1 = VecDeque::new();
    let mut player2 = VecDeque::new();

    lines.next();
    loop {
        let line = lines.next().unwrap();
        if line == "" { break; }
        player1.push_back(line.parse().unwrap());
    }

    lines.next();
    while let Some(line) = lines.next() {
        player2.push_back(line.parse().unwrap());
    }


    let mut player12 = player1.clone();
    let mut player22 = player2.clone();

    recurse_combat(&mut player12, &mut player22);

    let winner =
        if player12.len() > 0 {
            &player12
        } else {
            &player22
        };
    let ans2: usize = winner.iter().rev().enumerate().map(|(i, c)| (i + 1) * c).sum();


    while player1.len() > 0 && player2.len() > 0 {
        let p1 = player1.pop_front().unwrap();
        let p2 = player2.pop_front().unwrap();

        if p1 > p2 {
            player1.push_back(p1);
            player1.push_back(p2);
        } else {
            player2.push_back(p2);
            player2.push_back(p1);
        }
    }


    let winner =
        if player1.len() > 0 {
            &player1
        } else {
            &player2
        };

    let ans1: usize = winner.iter().rev().enumerate().map(|(i, c)| (i + 1) * c).sum();

    format!("{}, {}", ans1, ans2)
}
