package src

import (
    "fmt"
    "strconv"
    "container/ring"
)

func Solve19(input string) string {
    var ans1 int
    var ans2 int

    ringSize, _ := strconv.Atoi(input)

    r := ring.New(ringSize)

    for i := 1; i <= ringSize; i++ {
        r.Value = i
        r = r.Next()
    }

    for i := 0; i < ringSize - 1; i++ {
        r.Unlink(1)
        r = r.Next()
    }

    ans1 = r.Value.(int)

    r = ring.New(ringSize)

    for i := 1; i <= ringSize; i++ {
        r.Value = i
        r = r.Next()
    }

    steps := (ringSize - 1) / 2 - (1 - ringSize % 2)

    for i := 0; i < steps; i++ {
        r = r.Next()
    }

    for ringSize > 0 {
        if ringSize % 2 == 0 {
            r = r.Next()
            r.Unlink(1)
        } else {
            r.Unlink(1)
        }
        ringSize--
    }

    ans2 = r.Value.(int)

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
