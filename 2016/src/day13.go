package src

import (
    "fmt"
    "strconv"
    "math/bits"
    . "../utils"
)

func isWall(p Point, magic uint) bool {
    x := uint(p.X)
    y := uint(p.Y)
    return bits.OnesCount(x*x + 3*x + 2*x*y + y + y*y + magic) % 2 == 1
}

func Solve13(input string) string {
    var ans1 int
    var ans2 int

    magic, _ := strconv.Atoi(input)

    startPos := Point{1, 1}
    goal := Point{31, 39}

    visited := map[Point]bool{}
    toVisit := []Point{startPos}

    search:
    for {
        newToVisit := []Point{}

        for _, pos := range toVisit {
            if visited[pos] {
                continue
            }

            if pos == goal {
                break search
            }

            visited[pos] = true

            offsets := []Point{Point{-1, 0}, Point{0, -1}, Point{1, 0}, Point{0, 1}}
            for _, offset := range offsets {
                newPos := pos.Plus(offset)
                if newPos.X >= 0 && newPos.Y >= 0 && !isWall(newPos, uint(magic)) {
                    newToVisit = append(newToVisit, newPos)
                }
            }
        }

        toVisit = newToVisit

        if ans1 == 50 {
            ans2 = len(visited)
        }

        ans1++
    }

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
