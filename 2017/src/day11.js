export default function solve11(input) {
    let ans1 = 0;
    let ans2 = 0;

    let x = 0;
    let y = 0;

    function stepsTo(x, y) {
        x = Math.abs(x);
        y = Math.abs(y);
        return x + Math.max(y - x, 0) / 2;
    }

    input.split(",").forEach((dir) => {
        if (dir == "n") {
            y += 2;
        } else if (dir == "s") {
            y -= 2;
        } else if (dir == "nw") {
            x--;
            y++;
        } else if (dir == "ne") {
            x++;
            y++;
        } else if (dir == "sw") {
            x--;
            y--;
        } else if (dir == "se") {
            x++;
            y--;
        }

        ans2 = Math.max(stepsTo(x, y), ans2);
    });

    ans1 = stepsTo(x, y);

    return [ans1, ans2];
}
