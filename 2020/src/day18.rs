fn plus(a: u64, b: u64) -> u64 {
    a + b
}

fn mult(a: u64, b: u64) -> u64 {
    a * b
}

fn eval_expression(tokens: &Vec<&str>, mut i: usize) -> (usize, u64) {
    let mut v = 
        if tokens[i] == "(" {
            let res = eval_expression(tokens, i+1);
            i = res.0;
            res.1
        } else {
            i += 1;
            tokens[i-1].parse().unwrap()
        };

    while i < tokens.len() && tokens[i] != ")" {
        let f =
            if tokens[i] == "+" {
                plus
            } else {
                mult
            };

        i += 1;

        if tokens[i] == "(" {
            let res = eval_expression(tokens, i+1);
            i = res.0;
            v = f(v, res.1);
        } else {
            v = f(v, tokens[i].parse().unwrap());
            i += 1;
        }
    }

    return (i+1, v);
}

fn find_matching(tokens: &Vec<&str>, mut i: usize, dir: bool) -> usize {
    let mut to_find = 1;
    while to_find > 0 {
        if dir { i += 1; } else { i -= 1; };
        match tokens[i] {
            "(" => if dir { to_find += 1; } else { to_find -= 1; },
            ")" => if dir { to_find -= 1; } else { to_find += 1; },
            _ => {},
        }
    }

    i
}

pub fn solve(input: String) -> String {

    let mut ans1 = 0;
    let mut ans2 = 0;
    for line in input.lines() {
        let line = line.replace("(", "( ").replace(")", " )");
        let mut tokens = line.split_whitespace().collect();

        ans1 += eval_expression(&tokens, 0).1;

        let mut i = 0;
        while i < tokens.len() {
            if tokens[i] != "+" { i += 1; continue; }

            if tokens[i-1] == ")" {
                tokens.insert(find_matching(&tokens, i-1, false), "(");
            } else {
                tokens.insert(i-1, "(");
            }

            i += 1;

            if tokens[i+1] == "(" {
                tokens.insert(find_matching(&tokens, i+1, true) + 1, ")");
            } else {
                tokens.insert(i+2, ")");
            }

            i += 1;
        }

        ans2 += eval_expression(&tokens, 0).1;
    }

    format!("{}, {}", ans1, ans2)
}
