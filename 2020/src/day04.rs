extern crate regex;
use regex::Regex;

use std::collections::HashMap;

pub fn solve(mut input: String) -> String {
    let mut ans1 = 0;
    let mut ans2 = 0;

    let required = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"];
    let regexes = [
        Regex::new(r"^\d{4}$").unwrap(),
        Regex::new(r"^\d{4}$").unwrap(),
        Regex::new(r"^\d{4}$").unwrap(),
        Regex::new(r"^(\d*)(cm|in)$").unwrap(),
        Regex::new(r"^#[0-9a-f]{6}$").unwrap(),
        Regex::new(r"^(amb|blu|brn|gry|grn|hzl|oth)$").unwrap(),
        Regex::new(r"^\d{9}$").unwrap(),
    ];

    let mut fields: HashMap<&str, &str> = HashMap::new();

    input += "\n";
    for line in input.lines() {
        if line.len() == 0 {
            let mut ok = true;
            for r in &required {
                if !fields.contains_key(r) {
                    ok = false;
                    break;
                }
            }

            if ok {
                ans1 += 1;

                for i in 0..required.len() {
                    let key = required[i];
                    let value = fields[key];
                    if !regexes[i].is_match(value) {
                        ok = false;
                        break;
                    }
                    if i == 0 {
                        let n: u32 = value.parse().unwrap();
                        if n < 1920 || n > 2002 {
                            ok = false;
                            break;
                        }
                    } else if i == 1 {
                        let n: u32 = value.parse().unwrap();
                        if n < 2010 || n > 2020 {
                            ok = false;
                            break;
                        }
                    } else if i == 2 {
                        let n: u32 = value.parse().unwrap();
                        if n < 2020 || n > 2030 {
                            ok = false;
                            break;
                        }
                    } else if i == 3 {
                        let cap = regexes[i].captures(value).unwrap();
                        let n: u32 = cap[1].parse().unwrap();
                        if (&cap[2] == "cm" && (n < 150 || n > 193)) || (&cap[2] == "in" && (n < 59 || n > 76)) {
                            ok = false;
                            break;
                        }
                    }
                }

                if ok {
                    ans2 += 1;
                }
            }

            fields.clear();
        }
        let kv_pairs = line
            .split_whitespace()
            .map(|x| x.split(":").collect())
            .map(|x: Vec<_>| (x[0], x[1]));

        for (key, value) in kv_pairs {
            fields.insert(key, value);
        }
    }

    format!("{}, {}", ans1, ans2)
}
