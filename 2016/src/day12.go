package src

import (
    "fmt"
    "strings"
    "strconv"
)

func solve12(instructions [][3]string, c int) int {
    vars := map[byte]int{
        'a': 0,
        'b': 0,
        'c': c,
        'd': 0,
    }

    pc := 0

    for pc < len(instructions) {
        op := instructions[pc][0]

        if op == "cpy" {
            arg1 := instructions[pc][1]
            arg2 := instructions[pc][2][0]
            if arg1[0] >= 'a' && arg1[0] <= 'd' {
                vars[arg2] = vars[arg1[0]]
            } else {
                value, _ := strconv.Atoi(arg1)
                vars[arg2] = value
            }
        } else if op == "jnz" {
            arg1 := instructions[pc][1]
            arg1v := 0
            arg2, _ := strconv.Atoi(instructions[pc][2])
            if arg1[0] >= 'a' && arg1[0] <= 'd' {
                arg1v = vars[arg1[0]]
            } else {
                arg1v, _ = strconv.Atoi(arg1)
            }

            if arg1v != 0 {
                pc += arg2
            } else {
                pc++
            }

            continue
        } else if op == "inc" {
            vars[instructions[pc][1][0]]++
        } else if op == "dec" {
            vars[instructions[pc][1][0]]--
        }
        pc++
    }

    return vars['a']
}

func Solve12(input string) string {
    var ans1 int
    var ans2 int

    instructions := [][3]string{}

    for _, line := range strings.Split(input, "\n") {
        instruction := [3]string{}
        for i, code := range strings.Split(line, " ") {
            instruction[i] = code
        }
        instructions = append(instructions, instruction)
    }


    ans1 = solve12(instructions, 0)
    ans2 = solve12(instructions, 1)

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
