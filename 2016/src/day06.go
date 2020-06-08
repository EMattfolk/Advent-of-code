package src

import (
    "fmt"
    "strings"
)

func Solve06(input string) string {
    var ans1 string
    var ans2 string

    charCounts := [8][26]int{}
    lines := strings.Split(input, "\n")

    for _, line := range lines {
        for i, r := range line {
            charCounts[i][r - 'a']++
        }
    }

    for i := 0; i < 8; i++ {
        max := 0
        maxRune := 'a'

        min := 1000
        minRune := 'a'

        for j, c := range charCounts[i] {
            if c > max {
                max = c
                maxRune = 'a' + rune(j)
            }
            if c < min && c != 0 {
                min = c
                minRune = 'a' + rune(j)
            }
        }

        ans1 += string(maxRune)
        ans2 += string(minRune)
    }

    return fmt.Sprintf("%s, %s", ans1, ans2)
}
