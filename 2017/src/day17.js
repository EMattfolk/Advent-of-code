export default function solve17(input) {
    let ans1 = 0;
    let ans2 = 0;

    let steps = parseInt(input);

    let list = { length: 0 };

    list.insert = (at, value) => {
        let old = list[at];
        list[at] = value;
        list[value] = old;
        list.length++;
    };

    list[0] = 0;
    list.length++;

    let pos = 0;
    let index = 0;
    for (let i = 1; i <= 2017; i++) {
        for (let j = 0; j < steps; j++) {
            pos = list[pos];
        }

        list.insert(pos, i);
        pos = list[pos];

        index = (((index + steps) % (list.length - 1)) + 1) % list.length
    }

    ans1 = list[2017];

    for (let i = 2018; i <= 50000000;) {
        let s = Math.floor((list.length - index - 1) / steps);
        if (s > 0) {
            list.length += s;
            index = index + steps * s + s;
            i += s;
        } else {
            list.length++;
            index = (((index + steps) % (list.length - 1)) + 1) % list.length;
            if (index === 1) {
                ans2 = i;
            }
            i++;
        }
    }

    return [ans1, ans2];
}
