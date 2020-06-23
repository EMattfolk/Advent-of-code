export default function solve10(input) {
    let ans1 = 0;
    let ans2 = 0;

    let lengths = input.split(",").map((n) => parseInt(n));
    let asciiLengths = input.split("").map((c) => c.charCodeAt(0)).concat([17, 31, 73, 47, 23]);
    let list = [];

    for (let i = 0; i < 256; i++) {
        list.push(i);
    }

    let index = 0;
    let skip = 0;

    function knotHash(lengths, list) {
        list = list.slice();
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

        return list;
    }

    index = 0;
    skip = 0;
    let list1 = knotHash(lengths, list);

    ans1 = list1[0] * list1[1];


    index = 0;
    skip = 0;
    let list2 = list.slice();

    for (let r = 0; r < 64; r++) {
        list2 = knotHash(asciiLengths, list2);
    }

    let dense = [];
    for (let i = 0; i < list2.length; i += 16) {
        let d = list2[i];
        for (let j = i+1; j < i + 16; j++) {
            d = d ^ list2[j];
        }
        dense.push(d);
    }

    let hash = "";
    dense.forEach((c) => {
        if (c < 16) {
            hash += "0";
        }

        hash += c.toString(16);
    });

    ans2 = hash;

    return [ans1, ans2];
}
