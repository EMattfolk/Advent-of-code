export default function solve14(input) {
    let ans1 = 0;
    let ans2 = 0;

    function knotHash(string) {

        let list = [];

        for (let i = 0; i < 256; i++) {
            list.push(i);
        }

        let lengths = string.split("").map((c) => c.charCodeAt(0)).concat([17, 31, 73, 47, 23]);

        let index = 0;
        let skip = 0;
        for (let r = 0; r < 64; r++) {
            lengths.forEach((l) => {
                let buf = [];

                for (let i = l - 1; i >= 0; i--) {
                    buf.push(list[(index + i) % list.length]);
                }

                for (let i = 0; i < l; i++) {
                    list[(index + i) % list.length] = buf[i];
                }

                index += l + skip;
                skip++;
            });
        }

        let dense = [];
        for (let i = 0; i < list.length; i += 16) {
            let d = list[i];
            for (let j = i+1; j < i + 16; j++) {
                d = d ^ list[j];
            }
            dense.push(d);
        }

        return dense;
    }

    let grid = [];
    for (let i = 0; i < 128; i++) {
        let row = "";
        knotHash(input + "-" + i).forEach((b) => {
            let binStr = b.toString(2);
            binStr.split("").forEach((bit) => ans1 += bit === "1"); 

            while (binStr.length < 8) {
                binStr = "0" + binStr;
            }
            row += binStr;
        });
        grid.push(row);
    }

    let visited = new Set();

    function fill(x, y) {
        let toVisit = [];
        toVisit.push([x, y]);
        visited.add(x + "," + y);

        while (toVisit.length > 0) {
            let [x, y] = toVisit.pop();

            for (const [xo, yo] of [[-1, 0], [0, 1], [1, 0], [0, -1]]) {
                let nx = x + xo;
                let ny = y + yo;
                let posStr = nx + "," + ny;

                if (nx >= 0 && nx < 128 && ny >= 0 && ny < 128 &&
                    grid[ny][nx] === "1" && !visited.has(posStr)) {
                        visited.add(posStr);
                        toVisit.push([nx, ny]);
                }
            }
        }
    }

    grid.forEach((line, y) => {
        line.split("").forEach((bit, x) => {
            if (bit == "1" && !visited.has(x + "," + y)) {
                fill(x, y);
                ans2++;
            }
        });
    });

    return [ans1, ans2];
}
