export default function solve03(input) {
    let ans1 = 0;
    let ans2 = 0;

    let goalPos = parseInt(input);

    let outerRing = Math.ceil(Math.sqrt(goalPos));
    outerRing = outerRing % 2 === 0 ? outerRing + 1 : outerRing;
    let innerRing = outerRing - 2;

    let quarter = (outerRing * outerRing - innerRing * innerRing) / 4;
    let posOnRing = (goalPos - innerRing * innerRing) % quarter;

    let toMiddle = (innerRing + 1) / 2 - posOnRing;
    toMiddle = toMiddle < 0 ? -toMiddle : toMiddle;

    ans1 = (innerRing + 1) / 2 + toMiddle;

    function turn(pos) {
        return { x: pos.y, y: -pos.x };
    }

    function plus(pos, offset) {
        return { x: pos.x + offset.x, y: pos.y + offset.y };
    }

    let offsets = [];
    for (let i = -1; i <= 1; i++) {
        for (let j = -1; j <= 1; j++) {
            if (i === 0 && j === 0) {
                continue;
            }
            offsets.push({ x: i, y: j });
        }
    }

    let square = new Map();
    let pos = { x: 0, y: 0 };
    let dir = { x: 1, y: 0 };
    let layer = 1;
    quarter = 1;

    square.set(pos.x + "," + pos.y, 1);

    let i = 1;
    let value = 1;
    while (value < goalPos) {
        if (i === layer * layer) {
            layer += 2;
            quarter = (layer*layer - (layer-2)*(layer-2)) / 4;
            pos = plus(pos, dir);
            dir = turn(dir);
        } else {
            if ((i - (layer-2)*(layer-2)) % quarter === 0) {
                dir = turn(dir);
            }
            pos = plus(pos, dir);
        }

        value = 0;
        offsets.forEach((offset) => {
            let newPos = plus(pos, offset);
            if (square.has(newPos.x + "," + newPos.y)) {
                value += square.get(newPos.x + "," + newPos.y);
            }
        });

        square.set(pos.x + "," + pos.y, value);

        i++;
    }

    ans2 = value;

    return [ans1, ans2];
}
