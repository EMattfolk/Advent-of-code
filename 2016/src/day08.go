package src

import (
    "fmt"
    "strings"
    "strconv"
)

func day8RotateSplit (r rune) bool {
    return r == ' ' || r == '='
}

func day8RectSplit (r rune) bool {
    return r == ' ' || r == 'x'
}

func Solve08(input string) string {
    var ans1 int
    var ans2 string

    display := [6][50]bool{}
    lines := strings.Split(input, "\n")

    for _, line := range lines {
        if line[1] == 'e' {
            split := strings.FieldsFunc(line, day8RectSplit)
            width, _ := strconv.Atoi(split[1])
            height, _ := strconv.Atoi(split[2])

            for y := 0; y < height; y++ {
                for x := 0; x < width; x++ {
                    display[y][x] = true
                }
            }
        } else {
            splits := strings.FieldsFunc(line, day8RotateSplit)
            var buf [50]bool

            index, _ := strconv.Atoi(splits[3])
            amount, _ := strconv.Atoi(splits[5])

            if line[7] == 'r' {
                for i := 0; i < 50; i++ {
                    buf[(i + amount) % 50] = display[index][i]
                }
                for i := 0; i < 50; i++ {
                    display[index][i] = buf[i]
                }
            } else {
                for i := 0; i < 6; i++ {
                    buf[(i + amount) % 6] = display[i][index]
                }
                for i := 0; i < 6; i++ {
                    display[i][index] = buf[i]
                }
            }

        }
    }

    for y := 0; y < 6; y++ {
        ans2 += "\n"
        for x := 0; x < 50; x++ {
            if display[y][x] {
                ans1++
                ans2 += "█"
            } else {
                ans2 += " "
            }
        }
    }

    return fmt.Sprintf("%d, %s", ans1, ans2)
}
