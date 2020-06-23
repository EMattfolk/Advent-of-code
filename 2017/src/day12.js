export default function solve12(input) {
    let ans1 = 0;
    let ans2 = 0;

    let connections = new Map();

    input.split("\n").forEach((line) => {
        let splits = line.split(/[ <\->,]+/).map((n) => parseInt(n));
        let prog = splits[0];
        let children = splits.slice(1, splits.length);

        connections.set(prog, children);
    });

    function getGroup(initProg) {

        let visited = new Set([initProg]);
        let toVisit = [initProg];

        while (toVisit.length > 0) {
            let prog = toVisit.pop();

            connections.get(prog).forEach((child) => {
                if (!visited.has(child)) {
                    toVisit.push(child);
                    visited.add(child);
                }
            });
        }

        return visited
    }

    ans1 = getGroup(0).size;

    let found = new Set();
    for (const prog of connections.keys()) {
        if (!found.has(prog)) {
            ans2++;
            getGroup(prog).forEach((p) => found.add(p));
        }
    }

    return [ans1, ans2];
}
