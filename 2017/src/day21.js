export default function solve21(input) {
    let ans1 = 0;
    let ans2 = 0;

    let transforms = new Map();

    input.split("\n").forEach(line => {
        line = line.split(" => ");

        let toRotate = line[0].split("/");
        let result = line[1].split("/");

        let size = toRotate.length;
        while (!transforms.has(toRotate.join("/"))) {
            transforms.set(toRotate.join("/"), result);

            let rotation = toRotate.join("/").split("/").map(l => l.split(""));

            for (let i = 0; i < size; i++) {
                for (let j = 0; j < size; j++) {
                    rotation[i][j] = toRotate[j][size - 1 - i]
                }
            }

            rotation = rotation.map(l => l.join(""));
            toRotate = rotation;

            if (transforms.has(toRotate.join("/"))) {
                let temp = toRotate[0];
                toRotate[0] = toRotate[toRotate.length - 1];
                toRotate[toRotate.length - 1] = temp;
            }
        }
    });

    let f = Math.floor;
    let grid = [".#.", "..#", "###"];

    for (let iteration = 0; iteration < 18; iteration++) {

        if (iteration === 5) {
            grid.forEach(line => line.split("").forEach(c => ans1 += c === "#"));
        }

        let splitSize = 2 + (grid.length % 2);

        let transformGrid = [];

        for (let sy = 0; sy < grid.length; sy += splitSize) {
            let transformLine = [];
            for (let sx = 0; sx < grid.length; sx += splitSize) {
                let square = [];
                for (let y = 0; y < splitSize; y++) {
                    let squareLine = "";
                    for (let x = 0; x < splitSize; x++) {
                        squareLine += grid[sy + y][sx + x];
                    }
                    square.push(squareLine);
                }
                transformLine.push(transforms.get(square.join("/")));
            }
            transformGrid.push(transformLine);
        }

        let newSize = grid.length / splitSize * (splitSize + 1)
        grid = [];

        for (let y = 0; y < newSize; y++) {
            let line = "";
            for (let x = 0; x < newSize; x++) {
                line += transformGrid[f(y / (splitSize + 1))][f(x / (splitSize + 1))][y % (splitSize + 1)][x % (splitSize + 1)];
            }
            grid.push(line);
        }
    }

    grid.forEach(line => line.split("").forEach(c => ans2 += c === "#"));

    return [ans1, ans2];
}
