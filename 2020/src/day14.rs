use std::collections::HashMap;

fn write_variable(mut addr: u64, value: u64, depth: usize, var: &Vec<u64>, mem: &mut HashMap<u64, u64>) {
    if depth == var.len() {
        mem.insert(addr, value);
        return;
    }
    addr |= var[depth];
    write_variable(addr, value, depth+1, var, mem);
    addr &= !var[depth];
    write_variable(addr, value, depth+1, var, mem);
}

pub fn solve(input: String) -> String {
    let mut and_mask: u64 = 0b111111111111111111111111111111111111;
    let mut or_mask: u64  = 0b000000000000000000000000000000000000;

    let mut mem = [0; 100000];
    let mut mem2 = HashMap::new();
    let mut variable = Vec::new();

    for l in input.lines() {
        let mut splits = l.split(" = ");
        let addr = splits.next().unwrap();
        let value = splits.next().unwrap();

        if addr.chars().last().unwrap() == ']' {
            let addr: usize = addr[4..addr.len()-1].parse().unwrap();
            let value = value.parse().unwrap();
            mem[addr] = value;
            mem[addr] |= or_mask;
            mem[addr] &= and_mask;
            write_variable(addr as u64 | or_mask, value, 0, &variable, &mut mem2);
        } else {
            and_mask         = 0b111111111111111111111111111111111111;
            or_mask          = 0b000000000000000000000000000000000000;
            let mut pos: u64 = 0b100000000000000000000000000000000000;

            variable.clear();
            for c in value.chars() {
                match c {
                    '1' => or_mask += pos,
                    '0' => and_mask -= pos,
                    _ => variable.push(pos),
                }
                pos >>= 1;
            }
        }
    }

    let ans1: u64 = mem.iter().sum();
    let ans2: u64 = mem2.iter().map(|(_key, value)| value).sum();

    format!("{}, {}", ans1, ans2)
}
