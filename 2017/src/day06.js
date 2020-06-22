export default function solve06(input) {
    let ans1 = 0;
    let ans2 = 0;

    let banks = input
        .split(/\s/)
        .map((bank) => parseInt(bank));

    let seen = new Set();
    seen.add(banks.join(""));

    let foundCycle = false;
    while (true) {
        let max = 0;
        let maxIndex = 0;

        banks.forEach((bank, index) => {
            if (bank > max) {
                max = bank;
                maxIndex = index;
            }
        });

        banks[maxIndex] = 0;

        let end = maxIndex + 1 + max;
        for (let i = maxIndex + 1; i < end; i++) {
            banks[i % banks.length]++;
        }

        if (!foundCycle) {
            ans1++;
        } else {
            ans2++;
        }

        let banksString = banks.join("");

        if (seen.has(banksString)) {
            if (foundCycle) {
                break;
            } else {
                foundCycle = true;
                seen.clear();
            }
        }

        seen.add(banksString);
    }

    return [ans1, ans2];
}
