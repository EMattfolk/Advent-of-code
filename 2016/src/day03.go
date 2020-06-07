package src

import (
    "fmt"
    "strings"
    "strconv"
)

func split(r rune) bool {
    return r == ' '
}

func isTriangle(sides [3]int) bool {
    return sides[0] + sides[1] > sides[2] &&
        sides[0] + sides[2] > sides[1] &&
        sides[1] + sides[2] > sides[0]
}

func Solve03(input string) string {
    var ans1 int
    var ans2 int

    triangles := strings.Split(input, "\n")
    var vertTriangle [3][3]int

    for i, triangle := range triangles {
        sidesStr := strings.FieldsFunc(triangle, split)
        var sides [3]int
        for j, s := range sidesStr {
            sides[j], _ = strconv.Atoi(s)
            vertTriangle[j][i % 3] = sides[j]
        }

        if isTriangle(sides) {
            ans1++
        }

        if i % 3 == 2 {
            for j := 0; j < 3; j++ {
                if isTriangle(vertTriangle[j]) {
                    ans2++
                }
            }
        }
    }

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
