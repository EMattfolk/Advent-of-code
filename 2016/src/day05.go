package src

import (
    "fmt"
    "crypto/md5"
    "strconv"
    "strings"
)

func Solve05(input string) string {
    var ans1 string
    var ans2 string

    passw2 := [8]string{}
    passw2_remaining := 8

    i := 0
    for passw2_remaining > 0 {
        hash := md5.Sum([]byte(input + strconv.Itoa(i)))

        if hash[0] == 0 && hash[1] == 0 && (hash[2] & 0xf0) == 0 {
            if len(ans1) < 8 {
                ans1 += fmt.Sprintf("%x", hash[2])
            }

            pos := hash[2]
            char := fmt.Sprintf("%x", (hash[3] & 0xf0) >> 4)
            if pos < 8 && passw2[pos] == "" {
                passw2[pos] = char
                passw2_remaining--
            }
        }

        i++
    }

    ans2 = strings.Join(passw2[:], "")

    return fmt.Sprintf("%s, %s", ans1, ans2)
}
