package src

import (
    "fmt"
    "strings"
    . "../utils"
)

func distTo(from, to Point, grid *[]string) int {
    dist := 0
    visited := map[Point]bool{}
    toVisit := []Point{from}

    for {
        newToVisit := []Point{}
        for _, p := range toVisit {
            if p == to {
                return dist
            }

            for _, offset := range []Point{Point{-1, 0}, Point{0, -1}, Point{1, 0}, Point{0, 1}} {
                np := p.Plus(offset)
                if (*grid)[np.Y][np.X] != '#' && !visited[np] {
                    visited[np] = true
                    newToVisit = append(newToVisit, np)
                }
            }
        }
        toVisit = newToVisit
        dist++
    }
}

func shortestDist (k int, path *[8]int, dists *[8][8]int, ans1, ans2 *int) {
    if k == 0 {
        shortestDist(k + 1, path, dists, ans1, ans2)
        return
    } else if k == len(path) {
        dist := 0
        for i := 0; i < len(path) - 1; i++ {
            dist += (*dists)[path[i]][path[i+1]]
        }
        dist2 := dist + (*dists)[path[0]][path[len(path)-1]]
        *ans1 = Min(dist, *ans1)
        *ans2 = Min(dist2, *ans2)
        return
    }

    for i := k; i < len(path); i++ {
        (*path)[i], (*path)[k] = (*path)[k], (*path)[i]
        shortestDist(k + 1, path, dists, ans1, ans2)
        (*path)[i], (*path)[k] = (*path)[k], (*path)[i]
    }
}

func Solve24(input string) string {
    var ans1 int
    var ans2 int

    grid := []string{}
    places := [8]Point{}

    for y, line := range strings.Split(input, "\n") {
        for x, c := range line {
            if c >= '0' && c <= '9' {
                places[c - '0'] = Point{x, y}
            }
        }
        grid = append(grid, line)
    }

    dists := [8][8]int{}
    for i := 0; i < len(places); i++ {
        for j := i + 1; j < len(places); j++ {
            dist := distTo(places[i], places[j], &grid)
            dists[i][j] = dist
            dists[j][i] = dist
        }
    }

    ans1 = 1 << 30
    ans2 = 1 << 30
    shortestDist(0, &[8]int{0, 1, 2, 3, 4, 5, 6, 7}, &dists, &ans1, &ans2)

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
