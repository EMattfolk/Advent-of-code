/* Some right solutions
 *
 * abcdefghijklmnop
 *
 * kgdchlfniambejop
 * abdkcgfepimjnlho
 * blchegmpifdanjko
 * alpmhofcjgdiebkn
 * jdpecgaoilkfmbhn
 * jlcdeifhabkgmnop
 * kfdchginajmlebop
 *
 *
 * Name swapping is linearly independent of the other two transformations.
 * I made this problem much more complicated than it needed to be...
 */

export default function solve16(input) {
    let ans1 = 0;
    let ans2 = 0;

    let instructions = input.split(",");
    let programs = "abcdefghijklmnop".split("");
    let swaps = programs.slice();

    function mod(n, m) {
          return ((n % m) + m) % m;
    }

    function dance(instr) {
        switch (instr.charAt(0)) {
            case "s":
                let size = parseInt(instr.slice(1, instr.length));
                programs = programs.slice(programs.length - size, programs.length)
                    .concat(programs.slice(0, programs.length - size));
                break;
            case "x":
                let indexes = instr.slice(1, instr.length)
                    .split("/").map(n => parseInt(n));
                let temp1 = programs[indexes[0]];
                programs[indexes[0]] = programs[indexes[1]];
                programs[indexes[1]] = temp1;
                break;
            case "p":
                let names = instr.slice(1, instr.length).split("/")
                    .map(name => name.charCodeAt(0) - "a".charCodeAt(0));
                let temp2 = swaps[names[0]];
                swaps[names[0]] = swaps[names[1]];
                swaps[names[1]] = temp2;
                break;
        }
    }

    let foundSwaps = new Set();
    let foundUnique = new Set();

    let runSwaps = true;
    let runUnique = true;

    while (runSwaps || runUnique) {
        instructions.forEach(instruction => dance(instruction));

        let progString = programs.join("");
        let swapsString = swaps.join("");

        runSwaps = !foundSwaps.has(swapsString);
        runUnique = !foundUnique.has(progString);

        if (runSwaps) {
            foundSwaps.add(swapsString);
        }
        if (runUnique) {
            foundUnique.add(progString);
        }
    }

    function gcd(a, b) {
       if (b == 0) {
           return a;
       }
       return gcd(b, a % b);
    }

    let cycle = foundSwaps.size * foundUnique.size / gcd(foundSwaps.size, foundUnique.size);

    let cyclesLeft = 1000000000 % cycle;

    programs = "abcdefghijklmnop".split("");
    swaps = programs.slice();
    for (let i = 0; i < cyclesLeft; i++) {
        if (i == 1) {
            ans1 = applySwaps();
        }
        instructions.forEach(instruction => dance(instruction));
    }

    function applySwaps() {
        let newPrograms = "                ".split("");
        for (let i = 0; i < swaps.length; i++) {
            let newChar = String.fromCharCode("a".charCodeAt(0) + i);
            let index = programs.indexOf(swaps[i]);
            newPrograms[index] = newChar;
        }

        return newPrograms.join("");
    }

    ans2 = applySwaps();

    return [ans1, ans2];
}
