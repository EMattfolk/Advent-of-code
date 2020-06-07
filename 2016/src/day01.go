package src

import (
	"fmt"
	"strings"
	"strconv"
)

type point struct {
	x int
	y int
}

func (p *point) Turn(right bool) {
	if right {
		temp := p.y
		p.y = -p.x
		p.x = temp
	} else {
		temp := p.x
		p.x = -p.y
		p.y = temp
	}
}

func (p *point) Add(o point) {
	p.x += o.x
	p.y += o.y
}

func (p point) Mul(scale int) point {
	return point{p.x * scale, p.y * scale}
}

func Abs(n int) int {
	if (n < 0) {
		return -n
	}

	return n
}

func Solve01(input string) string {
	var ans1 int
	var ans2 int

	moves := strings.Split(input, ", ")

	pos := point{0, 0}
	dir := point{0, 1}

	visited := make(map[point]bool)
	visited[pos] = true

	for _, move := range moves {
		dir.Turn(move[0] == 'R')
		dist, _ := strconv.Atoi(move[1:])

		for i := 0; i < dist; i++ {
			pos.Add(dir)
			exists := visited[pos]

			if exists && ans2 == 0 {
				ans2 = Abs(pos.x) + Abs(pos.y)
			}

			visited[pos] = true
		}
	}

	ans1 = Abs(pos.x) + Abs(pos.y)

	return fmt.Sprintf("%d, %d", ans1, ans2)
}
