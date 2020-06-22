export default function solve08(input) {
    let ans1 = 0;
    let ans2 = 0;

    let ops = new Map([
        [">", (a, b) => a > b],
        ["<", (a, b) => a < b],
        [">=", (a, b) => a >= b],
        ["<=", (a, b) => a <= b],
        ["==", (a, b) => a == b],
        ["!=", (a, b) => a != b],
    ]);

    let vars = new Map();

    input.split("\n").forEach((line) => {
        let instruction = line.split(" ");

        let reg1 = instruction[0];
        let reg2 = instruction[4];

        if (!vars.has(reg1)) {
            vars.set(reg1, 0);
        }
        if (!vars.has(reg2)) {
            vars.set(reg2, 0);
        }

        let dir = instruction[1] === "inc" ? 1 : -1;
        let op = ops.get(instruction[5]);

        let change = parseInt(instruction[2]) * dir;
        if (op(vars.get(reg2), parseInt(instruction[6]))) {
            vars.set(reg1, vars.get(reg1) + change);
            ans2 = Math.max(vars.get(reg1), ans2);
        }
    });

    ans1 = Array.from(vars.values()).reduce((a, b) => Math.max(a, b), 0);

    return [ans1, ans2];
}
