package src

import (
    "fmt"
    "strings"
    "strconv"
)

func Solve15(input string) string {
    var ans1 int
    var ans2 int

    values := map[int]int{}

    lines := strings.Split(input, "\n")
    for i, line := range lines {
        splits := strings.FieldsFunc(line, func (r rune) bool { return r == ' ' || r == '.' })
        pos, _ := strconv.Atoi(splits[3])
        curPos, _ := strconv.Atoi(splits[11])

        values[pos] = curPos + i + 1
    }

    time := 0
    mul := 1
    for pos, curPos := range values {
        for (curPos + time) % pos != 0 {
            time += mul
        }
        mul *= pos
    }

    ans1 = time

    for (len(lines) + 1 + time) % 11 != 0 {
        time += mul
    }

    ans2 = time

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
