/*
 * Prime counting?
 * Or composite number counting.
 *
 * set b 84    <--- ans1 = (84 - 2) * (84 - 2)
 * set c b
 * jnz a 2     ###
 * jnz 1 5
 * mul b 100
 * sub b -100000
 * set c b
 * sub c -17000
 * set f 1     ###  d = 2
 * set d 2     ###  OUTER:
 * set e 2     ###  e = 2
 * set g d     ###  LOOP:
 * mul g e     ###  
 * sub g b     ###  f = 0 if b != d * e
 * jnz g 2     ###  e++
 * set f 0     ###
 * sub e -1    ###
 * set g e     ###  if b != e goto loop
 * sub g b     ###
 * jnz g -8    ###
 * sub d -1    ###  d++
 * set g d     ###
 * sub g b     ###
 * jnz g -13   ###  if b != d goto outer
 * jnz f 2
 * sub h -1
 * set g b
 * sub g c
 * jnz g 2
 * jnz 1 3
 * sub b -17
 * jnz 1 -23
 *
 */
export default function solve23(input) {
    let ans1 = 0;
    let ans2 = 0;

    let instructions = input.split("\n").map(line => line.split(" "));
    let start = parseInt(instructions[0][2])

    ans1 = (start - 2) * (start - 2);

    start = start * 100 + 100000;
    let end = start + 17000;

    function isPrime(n) {
        if (n < 2) {
            return false;
        } else if (n == 2) {
            return true;
        } else if (n % 2 == 0) {
            return false;
        }

        for (let i = 3; i*i <= n; i += 2) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }

    for (let n = start; n <= end; n += 17) {
        ans2 += !isPrime(n);
    }

    return [ans1, ans2];
}
