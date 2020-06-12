package src

import (
    "fmt"
    "strings"
    "strconv"
    . "../utils"
)

func Solve01(input string) string {
    var ans1 int
    var ans2 int

    moves := strings.Split(input, ", ")

    pos := Point{0, 0}
    dir := Point{0, 1}

    visited := make(map[Point]bool)
    visited[pos] = true

    for _, move := range moves {
        dir.Turn(move[0] == 'R')
        dist, _ := strconv.Atoi(move[1:])

        for i := 0; i < dist; i++ {
            pos.Add(dir)
            exists := visited[pos]

            if exists && ans2 == 0 {
                ans2 = Abs(pos.X) + Abs(pos.Y)
            }

            visited[pos] = true
        }
    }

    ans1 = Abs(pos.X) + Abs(pos.Y)

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
