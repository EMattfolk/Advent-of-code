package src

import (
    "fmt"
    "sort"
    "strings"
    "strconv"
)

type UPoint struct {
    X uint
    Y uint
}

func UMax(a, b uint) uint {
    if a > b {
        return a
    }
    return b
}

func Solve20(input string) string {
    var ans1 uint
    var ans2 uint

    ranges := []UPoint{}

    for _, line := range strings.Split(input, "\n") {
        values := strings.Split(line, "-")
        start, _ := strconv.ParseInt(values[0], 10, 64)
        end, _ := strconv.ParseInt(values[1], 10, 64)

        ranges = append(ranges, UPoint{uint(start), uint(end)})
    }

    sort.Slice(ranges, func (i, j int) bool {
        return ranges[i].X < ranges[j].X || (ranges[i].X == ranges[j].X && ranges[i].Y < ranges[j].Y)
    })

    newRanges := []UPoint{}
    nr := ranges[0]

    for _, r := range ranges {
        if r.X <= nr.Y + 1 {
            nr.Y = UMax(r.Y, nr.Y)
        } else {
            newRanges = append(newRanges, nr)
            nr = r
        }
    }

    newRanges = append(newRanges, nr)
    ranges = newRanges

    ans1 = ranges[0].Y + 1

    cur := uint(0)
    for _, r := range ranges {
        ans2 += r.X - cur
        cur = r.Y + 1
    }

    ans2 += (4294967295 - cur) + 1

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
