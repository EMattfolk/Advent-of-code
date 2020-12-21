use std::collections::{HashMap, HashSet};
use itertools::Itertools;

pub fn solve(input: String) -> String {
    let mut ans1 = 0;

    let mut counts = HashMap::new();
    let mut allergens: HashMap<&str, HashSet<&str>> = HashMap::new();

    for line in input.lines() {
        let mut splits = line.split(" (contains ");
        let ingredients: HashSet<_> = splits
            .next()
            .unwrap()
            .split_whitespace()
            .map(|i| {
                *counts.entry(i).or_insert(0) += 1;
                ans1 += 1;
                i
            })
            .collect();
        let aller = splits
            .next()
            .map(|s| &s[0..s.len()-1])
            .unwrap()
            .split(", ");

        for a in aller {
            allergens.entry(a)
                .and_modify(|e| *e = e.intersection(&ingredients).cloned().collect())
                .or_insert(ingredients.clone());
        }
    }

    let mut allergen_names = Vec::new();
    for k in allergens.keys() {
        allergen_names.push((*k, ""));
    }

    let mut found = true;
    while found {
        found = false;
        for (name, allergen) in allergen_names.iter_mut() {
            let entry = allergens.entry(name).or_insert(HashSet::new());
            if entry.len() == 1 {
                *allergen = entry.drain().next().unwrap();
                for (_, val) in allergens.iter_mut() {
                    found |= val.remove(allergen);
                }
            }
        }
    }

    allergen_names.sort_by(|(n1, _), (n2, _)| n1.cmp(n2));

    for (_n, a) in allergen_names.iter() {
        ans1 -= counts[a];
    }

    let ans2 = allergen_names.iter().map(|(_, a)| a).join(",");

    format!("{}, {}", ans1, ans2)
}
