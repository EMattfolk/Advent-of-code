package src

import (
    "fmt"
    "crypto/md5"
    . "../utils"
)

type state17 struct {
    path string
    pos Point
}

func inBounds17(p Point) bool {
    return p.X >= 0 && p.X < 4 && p.Y >= 0 && p.Y < 4
}

func Solve17(input string) string {
    var ans1 string
    var ans2 int

    toVisit := []state17{ state17{"", Point{0, 0}} }

    dirs := [4]string{ "U", "D", "L", "R" }
    goal := Point{3, 3}

    for len(toVisit) > 0 {
        newToVisit := []state17{}

        for _, state := range toVisit {
            if state.pos == goal {
                if ans1 == "" {
                    ans1 = state.path
                }
                ans2 = len(state.path)
                continue
            }

            hash := md5.Sum([]byte(input + state.path))
            paths := [4]bool{
                hash[0] & 0xf0 > 0xa0, hash[0] & 0xf > 0xa,
                hash[1] & 0xf0 > 0xa0, hash[1] & 0xf > 0xa,
            }

            for i, dir := range [4]Point{ Point{0, -1}, Point{0, 1}, Point{-1, 0}, Point{1, 0} } {
                newPos := state.pos.Plus(dir)

                if !paths[i] || !inBounds17(newPos) {
                    continue
                }

                newToVisit = append(newToVisit, state17{state.path + dirs[i], newPos})
            }
        }

        toVisit = newToVisit
    }

    return fmt.Sprintf("%s, %d", ans1, ans2)
}
