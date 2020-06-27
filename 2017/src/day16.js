/*
 * kgdchlfniambejop
 * abdkcgfepimjnlho
 * blchegmpifdanjko
 * alpmhofcjgdiebkn
 * jdpecgaoilkfmbhn
 * jlcdeifhabkgmnop
 * kfdchginajmlebop
 */

export default function solve16(input) {
    let ans1 = 0;
    let ans2 = 0;

    let programs = "abcdefghijklmnop".split("");

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
                let temp = programs[indexes[0]];
                programs[indexes[0]] = programs[indexes[1]];
                programs[indexes[1]] = temp;
                break;
            case "p":
                let names = instr.slice(1, instr.length).split("/");
                programs.forEach((program, i, l) => {
                    if (program === names[0]) {
                        l[i] = names[1];
                    } else if (program === names[1]) {
                        l[i] = names[0];
                    }
                });
                break;
        }
    }

    input.split(",").forEach(instruction => dance(instruction));

    ans1 = programs.join("");

    console.log(programs.join(""));
    input.split(",").forEach(instruction => dance(instruction));
    console.log(programs.join(""));
    input.split(",").forEach(instruction => dance(instruction));
    console.log(programs.join(""));
    input.split(",").forEach(instruction => dance(instruction));
    console.log(programs.join(""));
    input.split(",").forEach(instruction => dance(instruction));
    console.log(programs.join(""));
    input.split(",").forEach(instruction => dance(instruction));
    console.log(programs.join(""));
    input.split(",").forEach(instruction => dance(instruction));
    console.log(programs.join(""));

    return [ans1];
}
