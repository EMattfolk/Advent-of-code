export default function solve02(input) {
    let ans1 = 0;
    let ans2 = 0;

    input.split("\n").forEach((row) => {
        let min = 9999;
        let max = 0;
        let values = row.split(/\s+/).map((n) => parseInt(n));
        values.forEach((value) => {
            min = Math.min(value, min);
            max = Math.max(value, max);
        });

        (() => {
            for (let i = 0; i < values.length; i++) {
                for (let j = i + 1; j < values.length; j++) {
                    let a = values[i];
                    let b = values[j];

                    if (a % b == 0) {
                        ans2 += a / b;
                        return;
                    }
                    if (b % a == 0) {
                        ans2 += b / a;
                        return;
                    }
                }
            }
        })();

        ans1 += max - min;
    });

    return [ans1, ans2];
}
