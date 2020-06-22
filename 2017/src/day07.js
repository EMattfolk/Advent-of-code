export default function solve07(input) {
    let ans1 = 0;
    let ans2 = 0;

    let disks = new Map();

    input.split("\n").forEach((line) => {
        let splits = line.split(/[ ()\->,]+/);

        let name = splits[0];
        let weight = parseInt(splits[1]);
        let children = splits.slice(2, splits.length); 

        if (children.length === 1) {
            children = [];
        }

        if (!disks.has(name)) {
            disks.set(name, { p: null });
        }

        disks.get(name).weight = weight;
        disks.get(name).children = children;
        
        children.forEach((disk) => {
            if (!disks.has(disk)) {
                disks.set(disk, { p: null });
            }

            disks.get(disk).p = name;
        });
    });

    disks.forEach((disk, name, disks) => {
        if (disk.p === null) {
            ans1 = name;
        }
    });

    function findWrong(name) {

        if (ans2 != 0) {
            return 0;
        }

        let weights = disks.get(name).children
            .map((child) => findWrong(child));

        let weightCounts = new Map();
        weights.forEach((w) => {
            if (!weightCounts.has(w)) {
                weightCounts.set(w, 0);
            }
            weightCounts.set(w, weightCounts.get(w) + 1);
        });

        let oddWeight = null;
        weightCounts.forEach((count, weight) => {
            if (count === 1) {
                oddWeight = weight;
            }
        });

        if (oddWeight != null && ans2 === 0) {
            let oddIndex = 0;
            weights.forEach((w, i) => {
                if (w === oddWeight) {
                    oddIndex = i;
                }
            });

            let okIndex = (oddIndex + 1) % weights.length;
            let oddChild = disks.get(disks.get(name).children[oddIndex]);
            ans2 = oddChild.weight + weights[okIndex] - weights[oddIndex];
        }

        return disks.get(name).weight + weights.reduce((a, b) => a + b, 0);
    }

    findWrong(ans1);

    return [ans1, ans2];
}
