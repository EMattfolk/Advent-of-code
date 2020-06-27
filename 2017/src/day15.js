export default function solve15(input) {
    let ans1 = 0;
    let ans2 = 0;

    let mask = Math.pow(2, 31) - 1;
    let compMask = Math.pow(2, 16) - 1;

    let lines = input.split("\n");
    let a = parseInt(lines[0].split(" ")[4]);
    let b = parseInt(lines[1].split(" ")[4]);

    for (let i = 0; i < 40000000; i++) {
        a = (a * 16807) % 2147483647;
        b = (b * 48271) % 2147483647;
        if ((a & compMask) === (b & compMask)) {
            ans1++;
        }
    }

    a = parseInt(lines[0].split(" ")[4]);
    b = parseInt(lines[1].split(" ")[4]);

    for (let i = 0; i < 5000000; i++) {
        do {
            a = (a * 16807) % 2147483647;
        } while ((a & 3) != 0);
        do {
            b = (b * 48271) % 2147483647;
        } while ((b & 7) != 0);

        if ((a & compMask) === (b & compMask)) {
            ans2++;
        }
    }

    return [ans1, ans2];
}
