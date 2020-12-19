use regex::Regex;
use itertools::Itertools;

#[derive(Clone)]
struct Rule {
    rules: Vec<Vec<usize>>,
    term: Option<char>,
}

impl Rule {
    fn new() -> Self {
        Self{ rules: Vec::new(), term: None }
    }
}

fn create_regex(i: usize, rules: &Vec<Rule>) -> String {
    if let Some(c) = rules[i].term {
        return c.to_string();
    }

    format!("({})", rules[i].rules.iter()
        .map(|p| p.iter()
            .map(|r| create_regex(*r, rules))
            .join("")
            )
        .join("|")
        )
}

fn create_regex2(i: usize, rules: &Vec<Rule>) -> String {

    if i == 8 {
        return format!("{}+", create_regex(42, rules));
    } else if i == 11 {
        let r42 = create_regex(42, rules);
        let r31 = create_regex(31, rules);
        return format!("({0}({0}({0}({0}({0}({0}({0}{1})?{1})?{1})?{1})?{1})?{1})?{1})", r42, r31);
    }

    if let Some(c) = rules[i].term {
        return c.to_string();
    }

    let mut res = "(".to_string();
    for (i, p) in rules[i].rules.iter().enumerate() {
        if i != 0 {
            res += "|";
        }
        for r in p {
            res += &create_regex2(*r, rules);
        }
    }

    res + ")"
}

pub fn solve(input: String) -> String {
    let mut rules = vec![Rule::new(); 200];

    let mut lines = input.lines();
    loop {
        let line = lines.next().unwrap();
        if line == "" { break; }

        let mut split = line.split(": ");
        let n: usize = split.next().unwrap().parse().unwrap();
        let r = split.next().unwrap();

        if r.chars().next().unwrap() == '"' {
            rules[n] = Rule{ rules: Vec::new(), term: Some(r.chars().nth(1).unwrap()) };
        } else {
            rules[n] = Rule{
                rules: r.split('|')
                        .map(|p| p.split_whitespace()
                                  .map(|x| x.parse().unwrap())
                                  .collect())
                        .collect(),
                term: None
            };
        }
    }

    let test_lines: Vec<_> = lines.collect();

    let re_string = format!("^{}$", create_regex(0, &rules));
    let re1 = Regex::new(&re_string).unwrap();

    let ans1: u32 = test_lines.iter().map(|l| re1.is_match(l) as u32).sum();

    let re_string = format!("^{}$", create_regex2(0, &rules));
    let re2 = Regex::new(&re_string).unwrap();

    let ans2: u32 = test_lines.iter().map(|l| re2.is_match(l) as u32).sum();

    format!("{}, {}", ans1, ans2)
}
