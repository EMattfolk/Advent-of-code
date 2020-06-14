package src

import (
    "fmt"
)

func nextRow(row string) string {
    newRow := ""
    for j := 0; j < len(row); j++ {
        var left byte
        if j != 0 {
            left = row[j-1]
        } else {
            left = '.'
        }
        center := row[j]
        var right byte
        if j != len(row)-1 {
            right = row[j+1]
        } else {
            right = '.'
        }

        if (left == center && center != right) || (center == right && center != left) {
            newRow += "^"
        } else {
            newRow += "."
        }
    }
    return newRow
}

func Solve18(input string) string {
    var ans1 int
    var ans2 int

    row := input
    safeTiles := 0

    for i := 0; i < 400000; i++ {
        for _, c := range row {
            if c == '.' {
                safeTiles++
            }
        }

        if i == 40 {
            ans1 = safeTiles
        }

        row = nextRow(row)
    }

    ans2 = safeTiles

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
