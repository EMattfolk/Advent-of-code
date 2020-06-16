package src

import (
    "fmt"
    "strings"
    "strconv"
    . "../utils"
)

type node struct {
    Pos   Point
    Size  int
    Used  int
    Avail int
}

type state22 struct {
    Empty Point
    Goal Point
}

func Solve22(input string) string {
    var ans1 int
    var ans2 int

    grid := map[Point]node{}
    nodes := []node{}
    datax := 0
    var empty node
    for l, line := range strings.Split(input, "\n") {
        if l < 2 {
            continue
        }

        splits := strings.FieldsFunc(line, func (r rune) bool {
            return r == ' ' || r == 'x' || r == 'y' || r == '-' || r == 'T'
        })

        x, _ := strconv.Atoi(splits[1])
        y, _ := strconv.Atoi(splits[2])
        size, _ := strconv.Atoi(splits[3])
        used, _ := strconv.Atoi(splits[4])
        avail, _ := strconv.Atoi(splits[5])

        n := node{Point{x, y}, size, used, avail}
        grid[Point{x, y}] = n

        if used == 0 {
            empty = n
        }

        if y == 0 && x > datax {
            datax = x
        }

        nodes = append(nodes, n)
    }

    for _, node := range nodes {
        if node.Used == 0 {
            continue
        }

        if node.Used <= empty.Avail {
            ans1++
        }
    }

    goal := Point{0, 0}
    visited := map[state22]bool{}
    toVisit := []state22{state22{empty.Pos, Point{datax, 0}}}

    bfs:
    for {
        newToVisit := []state22{}

        for _, state := range toVisit {
            if state.Goal == goal {
                break bfs
            }

            for _, offset := range []Point{Point{-1, 0}, Point{0, -1}, Point{1, 0}, Point{0, 1}} {
                newPos := state.Empty.Plus(offset)
                if node, exists := grid[newPos]; !exists || node.Size > 100 {
                    continue
                }

                var newState state22
                if newPos == state.Goal {
                    newState.Empty = state.Goal
                    newState.Goal = state.Empty
                } else {
                    newState.Empty = newPos
                    newState.Goal = state.Goal
                }

                if !visited[newState] {
                    visited[newState] = true
                    newToVisit = append(newToVisit, newState)
                }
            }
        }

        toVisit = newToVisit
        ans2++
    }

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
