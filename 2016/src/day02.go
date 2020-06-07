package src

import (
    "fmt"
    "strings"
    . "../utils"
)

func inBounds(x, y int) bool {
    return Abs(x) + Abs(y) <= 2
}

func Solve02(input string) string {
    var ans1 int
    var ans2 int

    keypad1 := [3][3]int {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 },
    }

    keypad2 := [5][5]int {
        { 0,   0,   1,   0, 0 },
        { 0,   2,   3,   4, 0 },
        { 5,   6,   7,   8, 9 },
        { 0, 0xA, 0xB, 0xC, 0 },
        { 0,   0, 0xD,   0, 0 },
    }

    instructions := strings.Split(input, "\n")

    for _, instruction := range instructions {
        x1 := 1
        y1 := 1
        x2 := 0
        y2 := 2
        for _, char := range instruction {
            diffx := 0
            diffy := 0
            switch char {
            case 'U':
                y1--
                diffy--
            case 'R':
                x1++
                diffx++
            case 'D':
                y1++
                diffy++
            case 'L':
                x1--
                diffx--
            }

            x1 = Max(Min(x1, 2), 0)
            y1 = Max(Min(y1, 2), 0)

            if inBounds(x2 + diffx - 2, y2 + diffy - 2) {
                x2 += diffx
                y2 += diffy
            }
        }
        ans1 = ans1 * 10 + keypad1[y1][x1]
        ans2 = ans2 * 16 + keypad2[y2][x2]
    }

    return fmt.Sprintf("%d, %X", ans1, ans2)
}
