export default function solve19(input) {
    let ans1 = "";
    let ans2 = 0;

    let grid = input.split("\n");

    let pos = [0, 0];
    grid[0].split("").forEach((c, i) => {
        if (c === "|") {
            pos[0] = i;
        }
    });

    let dir = [0, 1];

    while (dir !== null) {

        ans2++;

        let [dx, dy] = dir;
        pos[0] += dx;
        pos[1] += dy;

        let [x, y] = pos;
        let c = grid[y][x];

        if (c === "+") {
            dir = null;
            for (const [ox, oy] of [[-1, 0], [0, -1], [1, 0], [0, 1]]) {
                if (ox === -dx && oy === -dy) {
                    continue;
                }
                if (grid[y + oy][x + ox] !== " ") {
                    dir = [ox, oy];
                    break;
                }
            }
        } else if (c === " ") {
            break;
        } else if (c !== "-" && c !== "|") {
            ans1 += c;
        }
    }

    return [ans1, ans2];
}
