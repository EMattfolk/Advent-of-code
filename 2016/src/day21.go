package src

import (
    "fmt"
    "strings"
    "strconv"
)

func scramble(password string, steps [][]string) string {
    for _, step := range steps {
        if step[0] == "swap" {
            var pos1 int
            var pos2 int
            if step[1] == "position" {
                pos1, _ = strconv.Atoi(step[2])
                pos2, _ = strconv.Atoi(step[5])
            } else {
                pos1 = strings.IndexByte(password, step[2][0])
                pos2 = strings.IndexByte(password, step[5][0])
            }

            if pos1 > pos2 {
                pos1, pos2 = pos2, pos1
            }

            password = password[:pos1] + string(password[pos2]) + password[pos1+1:pos2] +
                string(password[pos1]) + password[pos2+1:]
        } else if step[0] == "rotate" {
            right := step[1] != "left"
            amount := 0
            if step[1] == "left" || step[1] == "right" {
                amount, _ = strconv.Atoi(step[2])
            } else {
                amount = strings.IndexByte(password, step[6][0])
                if amount >= 4 {
                    amount++
                }
                amount++
            }

            amount = amount % len(password)
            if right {
                amount = len(password) - amount
            }
            password = password[amount:] + password[:amount]
        } else if step[0] == "reverse" {
            start, _ := strconv.Atoi(step[2])
            end, _ := strconv.Atoi(step[4])
            var b strings.Builder
            b.WriteString(password[:start])
            for i := end; i >= start; i-- {
                b.WriteByte(password[i])
            }
            b.WriteString(password[end+1:])

            password = b.String()
        } else if step[0] ==  "move" {
            from, _ := strconv.Atoi(step[2])
            to, _ := strconv.Atoi(step[5])
            toMove := password[from]
            password = password[:from] + password[from+1:]
            password = password[:to] + string(toMove) + password[to:]
        }
    }
    return password
}

func permutations(per []byte, k int, res *[]string) {
    if k == len(per) {
        var b strings.Builder
        for _, c := range per {
            b.WriteByte(c)
        }
        *res = append(*res, b.String())
        return
    }

    for j := k; j < len(per); j++ {
        per[j], per[k] = per[k], per[j]
        permutations(per, k+1, res)
        per[j], per[k] = per[k], per[j]
    }
}

func Solve21(input string) string {
    var ans1 string
    var ans2 string

    steps := [][]string{}
    for _, line := range strings.Split(input, "\n") {
        tokens := strings.Split(line, " ")
        steps = append(steps, tokens)
    }

    ans1 = scramble("abcdefgh", steps)

    per := []string{}
    permutations([]byte("abcdefgh"), 0, &per)

    for _, permutation := range per {
        if scramble(permutation, steps) == "fbgdceah" {
            ans2 = permutation
            break
        }
    }

    return fmt.Sprintf("%s, %s", ans1, ans2)
}
