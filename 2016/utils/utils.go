package utils

type Point struct {
    X int
    Y int
}

func (p *Point) Add(o Point) {
    p.X += o.X
    p.Y += o.Y
}

func (p *Point) Plus(o Point) Point {
    return Point{p.X + o.X, p.Y + o.Y}
}

func (p Point) Mul(scale int) Point {
    return Point{p.X * scale, p.Y * scale}
}

func (p *Point) Turn(right bool) {
    if right {
        temp := p.Y
        p.Y = -p.X
        p.X = temp
    } else {
        temp := p.X
        p.X = -p.Y
        p.Y = temp
    }
}

func Min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func Max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func Abs(n int) int {
    if (n < 0) {
        return -n
    }

    return n
}

func Factorial(n int) int {
    f := 1
    for i := 2; i <= n; i++ {
        f *= i
    }
    return f
}
