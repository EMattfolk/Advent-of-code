export default function solve25(input) {
    let ans1 = 0;
    let ans2 = 0;

    let stateNames = new Map([["A", 0], ["B", 1], ["C", 2], ["D", 3], ["E", 4], ["F", 5]]);
    let states = [];

    let tape = new Map();
    let pos = 0;
    let state = 0;

    function createState(write0, move0, state0, write1, move1, state1) {
        return function() {

            let current = tape.has(pos) ? tape.get(pos) : false;

            if (!current) {
                tape.set(pos, write0);
                pos += move0;
                state = state0;
            } else {
                tape.set(pos, write1);
                pos += move1;
                state = state1;
            }
        };
    }

    let lines = input.split("\n");
    let steps = parseInt(lines[1].split(/[ .]/)[5]);

    state = stateNames.get(lines[0].split(/[ .]/)[3]);


    for (let line = 5; line < lines.length; line += 10) {
        let write0 = lines[line + 0].search("1") !== -1;
        let write1 = lines[line + 4].search("1") !== -1;
        let move0  = lines[line + 1].search("right") !== -1 ? 1 : -1;
        let move1  = lines[line + 5].search("right") !== -1 ? 1 : -1;
        let state0 = stateNames.get(lines[line + 2][lines[line + 2].length - 2]);
        let state1 = stateNames.get(lines[line + 6][lines[line + 6].length - 2]);

        states.push(createState(write0, move0, state0, write1, move1, state1));
    }

    console.log(steps);
    for (let i = 0; i < steps; i++) {
        states[state]();
    }

    tape.forEach((value, key) => ans1 += value);

    return [ans1];
}
