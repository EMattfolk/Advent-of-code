package src

import (
    "fmt"
    "strings"
)

func extendData(data string) string {
    var res strings.Builder
    res.WriteString(data)
    res.WriteString("0")
    for i := len(data) - 1; i >= 0; i-- {
        if data[i] == '1' {
            res.WriteString("0")
        } else {
            res.WriteString("1")
        }
    }

    return res.String()
}

func checksum(data string) string {
    var sum strings.Builder
    for i := 0; i < len(data) - 1; i += 2 {
        if data[i] == data[i+1] {
            sum.WriteString("1")
        } else {
            sum.WriteString("0")
        }
    }

    return sum.String()
}

func solve16(data string, length int) string {
    for len(data) < length {
        data = extendData(data)
    }

    data = data[:length]

    for len(data) % 2 == 0 {
        data = checksum(data)
    }

    return data
}

func Solve16(input string) string {
    ans1 := solve16(input, 272)
    ans2 := solve16(input, 35651584)

    return fmt.Sprintf("%s, %s", ans1, ans2)
}
