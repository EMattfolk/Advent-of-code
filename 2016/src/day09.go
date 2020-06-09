package src

import (
    "fmt"
    "strings"
    "strconv"
)

func decompressed_length(data string, recurse bool) int {
    size := 0
    index := 0
    for index < len(data) {
        if data[index] == '(' {
            marker := index
            for data[marker] != ')' {
                marker++
            }

            split := strings.Split(data[index+1:marker], "x")
            length, _ := strconv.Atoi(split[0])
            times, _ := strconv.Atoi(split[1])
            index = marker + length

            if recurse {
                size += decompressed_length(data[marker+1:marker+1+length], true) * times
            } else {
                size += length * times
            }
        } else {
            size++
        }

        index++
    }

    return size
}

func Solve09(input string) string {
    var ans1 int
    var ans2 int

    ans1 = decompressed_length(input, false)
    ans2 = decompressed_length(input, true)

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
