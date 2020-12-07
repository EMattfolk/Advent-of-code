use std::collections::HashMap;
use std::collections::HashSet;
use std::str::SplitWhitespace;

fn bags_inside(current: usize, bags: &Vec<Vec<(usize, usize)>>) -> usize {
    let mut tot = 0;
    for (count, i) in &bags[current] {
        tot += count * (1 + bags_inside(*i, bags));
    }

    tot
}

fn get_color(words: &mut SplitWhitespace) -> String {
    words.next().unwrap().to_owned() + words.next().unwrap()
}

pub fn solve(input: String) -> String {
    let mut colors = HashMap::new();
    let lines: Vec<_> = input.lines().collect();
    let mut outer: Vec<Vec<usize>> = Vec::new();
    let mut inner: Vec<Vec<(usize, usize)>> = Vec::new();

    for line in &lines {
        let mut words = line.split_whitespace();
        colors.insert(get_color(&mut words), colors.len());
        outer.push(Vec::new());
        inner.push(Vec::new());
    }

    for line in &lines {
        let mut words = line.split_whitespace();
        let o = colors[&get_color(&mut words)];

        let mut n = words.nth(2);
        while n.is_some() && n.unwrap() != "no" {
            let i = colors[&get_color(&mut words)];
            let count: usize = n.unwrap().parse().unwrap();
            outer[i].push(o);
            inner[o].push((count, i));
            n = words.nth(1);
        }
    }

    let mut to_visit = vec![colors["shinygold"]];
    let mut visited: HashSet<_> = vec![colors["shinygold"]].into_iter().collect();

    while let Some(current) = to_visit.pop() {
        for o in &outer[current] {
            if !visited.contains(o) {
                visited.insert(*o);
                to_visit.push(*o);
            }
        }
    }

    let ans1 = visited.len() - 1;
    let ans2 = bags_inside(colors["shinygold"], &inner);

    format!("{}, {}", ans1, ans2)
}
