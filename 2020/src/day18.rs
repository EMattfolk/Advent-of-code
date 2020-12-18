fn plus(a: u64, b: u64) -> u64 {
    a + b
}

fn mult(a: u64, b: u64) -> u64 {
    a * b
}

fn eval_expression(tokens: &mut impl Iterator<Item = char>) -> u64 {
    let tok = tokens.next().unwrap();
    let mut v = 
        if tok == '(' {
            eval_expression(tokens)
        } else {
            tok.to_digit(10).unwrap() as u64
        };

    while let Some(tok) = tokens.next() {
        if tok == ')' { break; }
        let f =
            if tok == '+' {
                plus
            } else {
                mult
            };

        let tok = tokens.next().unwrap();

        if tok == '(' {
            v = f(v, eval_expression(tokens));
        } else {
            v = f(v, tok.to_digit(10).unwrap() as u64);
        }
    }

    v
}

fn find_matching(tokens: &Vec<char>, mut i: usize, dir: bool) -> usize {
    let mut to_find = 1;
    while to_find > 0 {
        if dir { i += 1; } else { i -= 1; };
        match tokens[i] {
            '(' => if dir { to_find += 1; } else { to_find -= 1; },
            ')' => if dir { to_find -= 1; } else { to_find += 1; },
            _ => {},
        }
    }

    i
}

pub fn solve(input: String) -> String {

    let mut ans1 = 0;
    let mut ans2 = 0;
    for line in input.lines() {
        let mut tokens: Vec<_> = line.chars().filter(|c| *c != ' ').collect();

        ans1 += eval_expression(&mut tokens.iter().cloned());

        let mut i = 0;
        while i < tokens.len() {
            if tokens[i] != '+' { i += 1; continue; }

            if tokens[i-1] == ')' {
                tokens.insert(find_matching(&tokens, i-1, false), '(');
            } else {
                tokens.insert(i-1, '(');
            }

            i += 1;

            if tokens[i+1] == '(' {
                tokens.insert(find_matching(&tokens, i+1, true) + 1, ')');
            } else {
                tokens.insert(i+2, ')');
            }

            i += 1;
        }

        ans2 += eval_expression(&mut tokens.iter().cloned());
    }

    format!("{}, {}", ans1, ans2)
}
