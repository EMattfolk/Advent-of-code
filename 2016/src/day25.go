package src

import (
    "fmt"
    "strings"
    "strconv"
)

func Solve25(input string) string {
    var ans1 int

    instructions := [][3]string{}

    for _, line := range strings.Split(input, "\n") {
        instruction := [3]string{}
        for i, code := range strings.Split(line, " ") {
            instruction[i] = code
        }
        instructions = append(instructions, instruction)
    }

    testSeq := 10
    running := true
    for i := 0; running; i++ {
        vars := map[byte]int{
            'a': i,
            'b': 0,
            'c': 0,
            'd': 0,
        }

        pc := 0
        curSeq := 0

        for pc < len(instructions) {
            op := instructions[pc][0]

            if op == "cpy" {
                arg1 := instructions[pc][1]
                arg2 := instructions[pc][2][0]
                if arg2 >= 'a' && arg2 <= 'd' {
                    if arg1[0] >= 'a' && arg1[0] <= 'd' {
                        vars[arg2] = vars[arg1[0]]
                    } else {
                        value, _ := strconv.Atoi(arg1)
                        vars[arg2] = value
                    }
                }
            } else if op == "jnz" {
                arg1 := instructions[pc][1]
                arg1v := 0
                var arg2 int
                if instructions[pc][2][0] >= 'a' && instructions[pc][2][0] <= 'd' {
                    arg2 = vars[instructions[pc][2][0]]
                } else {
                    arg2, _ = strconv.Atoi(instructions[pc][2])
                }

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
                arg1 := instructions[pc][1][0]
                vars[arg1]++
            } else if op == "dec" {
                arg1 := instructions[pc][1][0]
                vars[arg1]--
            } else if op == "tgl" {
                index := pc + vars[instructions[pc][1][0]]
                if index >= 0 && index < len(instructions) {
                    toChange := instructions[index][0]
                    if toChange == "tgl" || toChange == "dec" {
                        instructions[index][0] = "inc"
                    } else if toChange == "inc" {
                        instructions[index][0] = "dec"
                    } else if toChange == "jnz" {
                        instructions[index][0] = "cpy"
                    } else {
                        instructions[index][0] = "jnz"
                    }
                }
            } else if op == "out" {
                arg1 := instructions[pc][1]
                var value int
                if arg1[0] >= '0' && arg1[0] <= '9' {
                    value = int(arg1[0] - '0')
                } else {
                    value = vars[arg1[0]]
                }

                if value != curSeq % 2 {
                    break
                } else {
                    curSeq++
                    if curSeq == testSeq {
                        ans1 = i
                        running = false
                        break
                    }
                }
            }
            pc++
        }
    }

    return fmt.Sprintf("%d", ans1)
}
