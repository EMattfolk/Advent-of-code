export default function solve24(input) {
    let ans1 = 0;
    let ans2 = 0;

    let connectors = new Map();

    input.split("\n").map(line => {
        line = line.split("/").map(n => parseInt(n));

        if (!connectors.has(line[0])) {
            connectors.set(line[0], []);
        }
        if (!connectors.has(line[1])) {
            connectors.set(line[1], []);
        }

        connectors.get(line[0]).push(line[1]);
        connectors.get(line[1]).push(line[0]);
    });

    let longest = 0;

    function buildBridge(connector, sum, depth) {
        ans1 = Math.max(sum, ans1);

        if (depth > longest) {
            longest = depth;
            ans2 = sum;
        } else if (depth == longest) {
            ans2 = Math.max(sum, ans2);
        }

        connectors.get(connector).slice().forEach(c => {
            connectors.get(connector).splice(connectors.get(connector).indexOf(c), 1);
            connectors.get(c).splice(connectors.get(c).indexOf(connector), 1);

            buildBridge(c, sum + c + connector, depth + 1);

            connectors.get(connector).push(c);
            connectors.get(c).push(connector);
        });
    }

    buildBridge(0, 0, 0);

    return [ans1, ans2];
}
