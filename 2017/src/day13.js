export default function solve13(input) {
    let ans1 = 0;
    let ans2 = 0;

    let layers = [];

    input.split("\n").forEach((line) => {
        let splits = line.split(": ").map((n) => parseInt(n));
        let layer = splits[0];
        let range = splits[1];

        while (layers.length < layer) {
            layers.push(0);
        }

        layers.push(range);
    });

    function caught(layer, time) {
        let range = layers[layer]; 
        return range < 2 ? range == 1 : (time % (range * 2 - 2) == 0);
    }

    layers.forEach((range, time) => {
        if (caught(time, time)) {
            ans1 += range * time;
        }
    });

    let found = false;
    let delay = 0;
    while (!found) {
        delay++;
        found = true;
        for (let i = 0; i < layers.length; i++) {
            if (caught(i, i + delay)) {
                found = false;
                break;
            }
        }
    }

    ans2 = delay;

    // Here lies wasted time...
    //
    //let rangeToLayers = new Map();
    //layers.forEach((range, time) => {
    //    if (!rangeToLayers.has(range)) {
    //        rangeToLayers.set(range, []);
    //    }
    //    rangeToLayers.get(range).push(time);
    //});

    //function gcd(a, b) {
    //    if (b === 0) {
    //        return a;
    //    }

    //    return gcd(b, a % b);
    //}

    //function lcm(a, b) {
    //    return a * b / gcd(a, b);
    //}

    //let ranges = Array.from(rangeToLayers.keys()).sort((a, b) => a > b ? 1 : -1);
    //let mult = 1;
    //let n = 0;

    //ranges.forEach((range) => {
    //    if (range === 0) {
    //        return;
    //    }

    //    console.log(range);

    //    let cycle = range * 2 - 2;
    //    let times = rangeToLayers.get(range);
    //    let found = false;
    //    while (!found) {
    //        found = true;
    //        for (const time of times) {
    //            if ((n + time) % cycle == 0) {
    //                found = false
    //                break;
    //            }
    //        }
    //        if (!found) {
    //            n += mult;
    //        }
    //    }
    //    mult = lcm(mult, cycle);
    //});

    //ans2 = n;

    return [ans1, ans2];
}
