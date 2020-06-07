package main

import (
    "fmt"
    "time"
    "strings"
    "io/ioutil"

    "./src"
)

func main() {
    days := [25]func(string)string {
        src.Solve01,
        src.Solve02,
        src.Solve03,
        src.Solve04,
        src.Solve05,
        src.Solve06,
        src.Solve07,
        src.Solve08,
        src.Solve09,
        src.Solve10,
        src.Solve11,
        src.Solve12,
        src.Solve13,
        src.Solve14,
        src.Solve15,
        src.Solve16,
        src.Solve17,
        src.Solve18,
        src.Solve19,
        src.Solve20,
        src.Solve21,
        src.Solve22,
        src.Solve23,
        src.Solve24,
        src.Solve25,
    }

    for day, fn := range days {
        day += 1

        bytes, _ := ioutil.ReadFile(fmt.Sprintf("input/%02d.txt", day))
        input := strings.TrimSpace(string(bytes))

        start := time.Now()
        answers := fn(input)
        elapsed := time.Since(start)

        millis := float64(elapsed) / 1000000

        if answers != "0, 0" {
            fmt.Printf("Day %2d: %8.3fms - %s\n", day, millis, answers)
        }
    }
}
