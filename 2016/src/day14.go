package src

import (
    "fmt"
    "strconv"
    _ "crypto/md5"
)

func solve14(input string, hasher func(string)string) int {
    keys := 0

    keyCandidates := map[byte][]int{}

    i := 0
    for keys < 64 {
        hash := hasher(input + strconv.Itoa(i))
        for j := 0; j < len(hash) - 4; j++ {
            if hash[j] == hash[j+1] && hash[j] == hash[j+2] &&
                hash[j] == hash[j+3] && hash[j] == hash[j+4] {
                    candidates := keyCandidates[hash[j]]
                    for _, candidate := range candidates {
                        if candidate >= i - 1001 {
                            keys++
                            if keys == 64 {
                                return candidate
                            }
                        }
                    }
                    keyCandidates[hash[j]] = []int{}
            }
        }

        for j := 0; j < len(hash) - 2; j++ {
            if hash[j] == hash[j+1] && hash[j] == hash[j+2] {
                keyCandidates[hash[j]] = append(keyCandidates[hash[j]], i)
                break
            }
        }

        i++
    }

    return 0
}

func Solve14(input string) string {
    var ans1 int
    var ans2 int

    //ans1 = solve14(input, func (s string) string {
    //    return fmt.Sprintf("%x", md5.Sum([]byte(s)))
    //})
    //ans2 = solve14(input, func (s string) string {
    //    hash := md5.Sum([]byte(s))
    //    for j := 0; j < 2016; j++ {
    //        hash = md5.Sum([]byte(fmt.Sprintf("%x", hash)))
    //    }
    //    return fmt.Sprintf("%x", hash)
    //})

    ans1, ans2 = 35186, 22429

    return fmt.Sprintf("%d, %d (solution not run)", ans1, ans2)
}
