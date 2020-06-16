package src

import (
    "fmt"
    "strings"
    "strconv"
    . "../utils"
)

func Solve23(input string) string {
    var ans1 int
    var ans2 int

    constants := []int{}

    for _, line := range strings.Split(input, "\n") {
        for _, code := range strings.Split(line, " ") {
            value, err := strconv.Atoi(code)
            if err == nil && value > 30 {
                constants = append(constants, value)
            }
        }
    }

    ans1 = Factorial(7) + constants[0] * constants[1]
    ans2 = Factorial(12) + constants[0] * constants[1]

    //vars := map[byte]int{
    //    'a': 7,
    //    'b': 0,
    //    'c': 0,
    //    'd': 0,
    //}

    //pc := 0

    //for pc < len(instructions) {
    //    op := instructions[pc][0]

    //    if op == "cpy" {
    //        arg1 := instructions[pc][1]
    //        arg2 := instructions[pc][2][0]
    //        if arg2 >= 'a' && arg2 <= 'd' {
    //            if arg1[0] >= 'a' && arg1[0] <= 'd' {
    //                vars[arg2] = vars[arg1[0]]
    //            } else {
    //                value, _ := strconv.Atoi(arg1)
    //                vars[arg2] = value
    //            }
    //        }
    //    } else if op == "jnz" {
    //        arg1 := instructions[pc][1]
    //        arg1v := 0
    //        var arg2 int
    //        if instructions[pc][2][0] >= 'a' && instructions[pc][2][0] <= 'd' {
    //            arg2 = vars[instructions[pc][2][0]]
    //        } else {
    //            arg2, _ = strconv.Atoi(instructions[pc][2])
    //        }

    //        if arg1[0] >= 'a' && arg1[0] <= 'd' {
    //            arg1v = vars[arg1[0]]
    //        } else {
    //            arg1v, _ = strconv.Atoi(arg1)
    //        }

    //        if arg1v != 0 {
    //            pc += arg2
    //        } else {
    //            pc++
    //        }

    //        continue
    //    } else if op == "inc" {
    //        arg1 := instructions[pc][1][0]
    //        vars[arg1]++
    //    } else if op == "dec" {
    //        arg1 := instructions[pc][1][0]
    //        vars[arg1]--
    //    } else if op == "tgl" {
    //        index := pc + vars[instructions[pc][1][0]]
    //        if index >= 0 && index < len(instructions) {
    //            toChange := instructions[index][0]
    //            if toChange == "tgl" || toChange == "dec" {
    //                instructions[index][0] = "inc"
    //            } else if toChange == "inc" {
    //                instructions[index][0] = "dec"
    //            } else if toChange == "jnz" {
    //                instructions[index][0] = "cpy"
    //            } else {
    //                instructions[index][0] = "jnz"
    //            }
    //        }
    //    }
    //    pc++
    //}

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
