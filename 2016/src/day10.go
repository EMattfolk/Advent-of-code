package src

import (
    "fmt"
    "strings"
    "strconv"
)

type bot struct {
    low int
    high int
    chips []int
}

func Solve10(input string) string {
    var ans1 int
    var ans2 int

    bots := [300]bot{}
    outputs := [30][]int{}

    for _, line := range strings.Split(input, "\n") {
        splits := strings.Split(line, " ")
        if line[0] == 'v' {
            value, _ := strconv.Atoi(splits[1])
            botN, _ := strconv.Atoi(splits[5])
            bots[botN].chips = append(bots[botN].chips, value)
        } else {
            botN, _ := strconv.Atoi(splits[1])
            low,  _ := strconv.Atoi(splits[6])
            high, _ := strconv.Atoi(splits[11])

            // Use negative number -1 to indicate output
            if splits[5][0] == 'o' {
                low = -low - 1
            }
            if splits[10][0] == 'o' {
                high = -high - 1
            }

            bots[botN].low = low
            bots[botN].high = high
        }
    }

    //outer:
    for len(outputs[1]) == 0 || len(outputs[2]) == 0 || len(outputs[3]) == 0 {
        for i, bot := range bots {
            if len(bot.chips) == 2 {
                max := bot.chips[0]
                min := bot.chips[1]
                bots[i].chips = make([]int, 0)
                if max < min {
                    temp := max
                    max = min
                    min = temp
                }

                if min == 17 && max == 61 {
                    ans1 = i
                    //break outer
                }

                if bot.low < 0 {
                    outputs[-bot.low] = append(outputs[-bot.low], min)
                } else {
                    bots[bot.low].chips = append(bots[bot.low].chips, min)
                }
                if bot.high < 0 {
                    outputs[-bot.high] = append(outputs[-bot.high], max)
                } else {
                    bots[bot.high].chips = append(bots[bot.high].chips, max)
                }
            }
        }
    }

    ans2 = outputs[1][0] * outputs[2][0] * outputs[3][0]

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
