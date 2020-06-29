export default function solve18(input) {
    let ans1 = 0;
    let ans2 = 0;

    let instructions = input.split("\n").map(line => line.split(" "));

    let registers = new Map();

    instructions.forEach(instruction => {
        let reg = instruction[1];
        if (!registers.has(reg) && reg !== "1") {
            registers.set(reg, 0);
        }
    });

    let prog1 = {
        pc: 0,
        regs: new Map(registers),
        queue: [],
        waiting: false
    };

    let prog2 = {
        pc: 0,
        regs: new Map(registers),
        queue: [],
        waiting: false,
        other: prog1
    };

    prog1.other = prog2;

    prog2.regs.set("p", 1);

    function toValue(v) {
        if (registers.has(v)) {
            return registers.get(v);
        } else {
            return parseInt(v);
        }
    }

    let pc = 0;
    while (pc >= 0 && pc < instructions.length) {
        let op = instructions[pc][0];
        let arg1 = instructions[pc][1];
        let arg2 = instructions[pc][2];

        switch (op) {
            case 'snd':
                ans1 = toValue(arg1);
                break;
            case 'set':
                registers.set(arg1, toValue(arg2));
                break;
            case 'add':
                registers.set(arg1, toValue(arg1) + toValue(arg2));
                break;
            case 'mul':
                registers.set(arg1, toValue(arg1) * toValue(arg2));
                break;
            case 'mod':
                registers.set(arg1, toValue(arg1) % toValue(arg2));
                break;
            case 'rcv':
                if (toValue(arg1) !== 0) {
                    pc = instructions.length;
                }
                break;
            case 'jgz':
                if (toValue(arg1) > 0) {
                    pc += toValue(arg2) - 1;
                }
                break;
        }
        pc++;
    }

    function run(prog) {

        function toValue(v) {
            if (prog.regs.has(v)) {
                return prog.regs.get(v);
            } else {
                return parseInt(v);
            }
        }

        if (prog.pc >= 0 && prog.pc < instructions.length) {
            let op = instructions[prog.pc][0];
            let arg1 = instructions[prog.pc][1];
            let arg2 = instructions[prog.pc][2];

            switch (op) {
                case 'snd':
                    if (prog === prog2) {
                        ans2++;
                    }
                    prog.other.queue.push(toValue(arg1));
                    break;
                case 'set':
                    prog.regs.set(arg1, toValue(arg2));
                    break;
                case 'add':
                    prog.regs.set(arg1, toValue(arg1) + toValue(arg2));
                    break;
                case 'mul':
                    prog.regs.set(arg1, toValue(arg1) * toValue(arg2));
                    break;
                case 'mod':
                    prog.regs.set(arg1, toValue(arg1) % toValue(arg2));
                    break;
                case 'rcv':
                    if (prog.queue.length > 0) {
                        prog.regs.set(arg1, prog.queue.shift());
                    } else {
                        prog.waiting = true;
                        return;
                    }
                    break;
                case 'jgz':
                    if (toValue(arg1) > 0) {
                        prog.pc += toValue(arg2) - 1;
                    }
                    break;
            }
            prog.pc++;
        } else {
            prog.waiting = true;
        }
    }

    while (!prog1.waiting || !prog2.waiting) {
        run(prog1);
        run(prog2);
    }

    return [ans1, ans2];
}
