use std::collections::HashMap;
use std::cmp::{min, max};

pub fn solve(input: String) -> String {
    let mut lines = input.lines();

    let mut fields = HashMap::new();
    while let Some(line) = lines.next() {
        if line == "" { break; }

        let mut splits = line.split(": ");
        let name = splits.next().unwrap();
        let intervals: Vec<(i32, i32)> = splits
            .next()
            .unwrap()
            .split(" or ")
            .map(|i| i.split('-').map(|n| n.parse().unwrap()))
            .map(|mut i| (i.next().unwrap(), i.next().unwrap()))
            .collect();
        fields.insert(name, intervals);
    }

    let i_min = fields.iter()
        .map(|(_k, v)| min(v[0].0, v[1].0))
        .min()
        .unwrap();

    let i_max = fields.iter()
        .map(|(_k, v)| max(v[0].1, v[1].1))
        .max()
        .unwrap();

    let interval = (i_min, i_max);

    lines.next();
    let ticket: Vec<i32> = lines.next().unwrap()
            .split(',')
            .map(|n| n.parse().unwrap())
            .collect();

    lines.next();
    lines.next();

    let nearby: Vec<Vec<i32>> = lines
        .map(|l| l
            .split(',')
            .map(|n| n.parse().unwrap())
            .collect())
        .collect();


    let ans1: i32 = nearby
        .iter()
        .map(|l| l
            .iter()
            .filter(|n| !(interval.0 <= **n && **n <= interval.1))
            .sum::<i32>())
        .sum();

    let nearby: Vec<Vec<i32>> = nearby
        .into_iter()
        .filter(|l| !l.iter().any(|n| !(interval.0 <= *n && *n <= interval.1)))
        .collect();

    let mut name_of_field = HashMap::new();
    for (name, intervals) in fields.iter() {
        let (t11, t12, t21, t22) = (intervals[0].0, intervals[0].1, intervals[1].0, intervals[1].1);
        for i in 0..ticket.len() {
            let mut ok = true;
            for t in nearby.iter() {
                if !((t11 <= t[i] && t[i] <= t12) || (t21 <= t[i] && t[i] <= t22)) {
                    ok = false;
                    break;
                }
            }

            if ok {
                (*name_of_field.entry(name).or_insert(Vec::new())).push(i);
            }
        }
    }

    let mut name_of_field: Vec<_> = name_of_field.into_iter().collect();
    name_of_field.sort_by(|a, b| a.1.len().cmp(&b.1.len()));
    for i in 0..name_of_field.len() {
        let to_remove = (name_of_field[i].1)[0];
        for j in i + 1..name_of_field.len() {
            let pos = (name_of_field[j].1).iter().position(|n| *n == to_remove);
            match pos {
                Some(p) => name_of_field[j].1.remove(p),
                _ => 0,
            };
        }
    }

    let mut ans2: u64 = 1;
    for (name, possible) in name_of_field.iter() {
        if &name[0..3] == "dep" {
            ans2 *= ticket[possible[0]] as u64;
        }
    }

    format!("{}, {}", ans1, ans2)
}
