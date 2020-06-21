export default function solve04(input) {
    let ans1 = 0;
    let ans2 = 0;

    input.split("\n").forEach((line) => {
        let words = new Set();
        let ok = true;
        for (const word of line.split(" ")) {
            if (words.has(word)) {
                ok = false;
                break;
            }
            words.add(word);
        }

        if (ok) {
            ans1++;
        }

        ok = true;
        words.clear();
        for (let word of line.split(" ")) {
            word = word.split("").sort().join("");
            if (words.has(word)) {
                ok = false;
                break;
            }
            words.add(word);
        }

        if (ok) {
            ans2++;
        }
    });

    return [ans1, ans2];
}
