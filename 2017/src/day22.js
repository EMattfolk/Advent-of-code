export default function solve22(input) {
    let ans1 = 0;
    let ans2 = 0;

    let lines = input.split("\n");
    let grid = new Set();

    let pos = [Math.floor(lines[0].length / 2), Math.floor(lines.length / 2)];

    for (let y = 0; y < lines.length; y++) {
        for (let x = 0; x < lines[y].length; x++) {
            if (lines[y][x] === "#") {
                grid.add([x, y].join(","));
            }
        }
    }

    function right(d) {
        return [-d[1], d[0]];
    }

    function left(d) {
        return [d[1], -d[0]];
    }

    let dir = [0, -1];

    let bursts = 10000;

    for (let i = 0; i < bursts; i++) {
        let posString = pos.join(",");
        if (grid.has(posString)) {
            dir = right(dir);
            grid.delete(posString);
        } else {
            dir = left(dir);
            grid.add(posString);
            ans1++;
        }

        pos = [pos[0] + dir[0], pos[1] + dir[1]];
    }

    grid = new Map();

    pos = [Math.floor(lines[0].length / 2), Math.floor(lines.length / 2)];
    dir = [0, -1];

    for (let y = 0; y < lines.length; y++) {
        for (let x = 0; x < lines[y].length; x++) {
            if (lines[y][x] === "#") {
                grid.set([x, y].join(","), "I");
            }
        }
    }

    bursts = 10000000;

    for (let i = 0; i < bursts; i++) {
        let posString = pos.join(",");

        let state = grid.get(posString);
        if (state === "W") {
            grid.set(posString, "I");
            ans2++;
        } else if (state === "I") {
            dir = right(dir);
            grid.set(posString, "F");
        } else if (state === "F") {
            dir = left(left(dir));
            grid.delete(posString);
        } else {
            dir = left(dir);
            grid.set(posString, "W");
        }

        pos = [pos[0] + dir[0], pos[1] + dir[1]];
    }

    return [ans1, ans2];
}
