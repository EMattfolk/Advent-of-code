package src

import (
    "fmt"
    "strings"
    "sort"
    "strconv"
)

func roomSplit(r rune) bool {
    return r == '[' || r == ']' || r == '-'
}

type runeN struct {
    n int
    r rune
}

func Solve04(input string) string {
    var ans1 int
    var ans2 int

    rooms := strings.Split(input, "\n")
    letter_counts := map[rune]int{}

    for _, room := range rooms {
        splits := strings.FieldsFunc(room, roomSplit)
        id, _ := strconv.Atoi(splits[len(splits)-2])

        for i := 0; i < len(splits) - 2; i++{
            split := splits[i]
            decryptedName := ""
            for _, r := range split {
                letter_counts[r]++
                decryptedName += string('a' + (r - 'a' + rune(id)) % 26)
            }

            if decryptedName == "northpole" {
                ans2 = id
            }
        }

        runeNs := make([]runeN, len(letter_counts))
        for r, n := range letter_counts {
            runeNs = append(runeNs, runeN{n, r})
        }

        sort.Slice(runeNs[:], func (i, j int) bool {
            return runeNs[i].n > runeNs[j].n ||
                (runeNs[i].n == runeNs[j].n && runeNs[i].r < runeNs[j].r)
        })

        checksum := ""
        for _, rn := range runeNs[:5] {
            checksum += string(rn.r)
        }

        if checksum == splits[len(splits)-1] {
            ans1 += id
        }

        letter_counts = make(map[rune]int)
    }

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
