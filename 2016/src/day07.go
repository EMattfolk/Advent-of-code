package src

import (
    "fmt"
    "strings"
)

func abbaSplit(r rune) bool {
    return r == '[' || r == ']'
}

func hasABBA(s string) bool {
    for i := 0; i < len(s) - 3; i++ {
        if s[i] != s[i+1] && s[i] == s[i+3] && s[i+1] == s[i+2] {
            return true
        }
    }
    return false
}

func getABA(s string, bab bool) []string {
    abas := []string{}
    for i := 0; i < len(s) - 2; i++ {
        if s[i] != s[i+1] && s[i] == s[i+2] {
            a := string(s[i])
            b := string(s[i+1])
            if bab {
                abas = append(abas, b + a + b)
            } else {
                abas = append(abas, a + b + a)
            }
        }
    }
    return abas
}

func Solve07(input string) string {
    var ans1 int
    var ans2 int

    lines := strings.Split(input, "\n")

    for _, line := range lines {
        fields := strings.FieldsFunc(line, abbaSplit)

        aba := map[string]bool{}

        TLS := false
        noTLS := false
        for i, field := range fields {
            if i % 2 == 0 {
                TLS = TLS || hasABBA(field)
                for _, a := range getABA(field, false) {
                    aba[a] = true
                }
            } else {
                noTLS = noTLS || hasABBA(field)
            }

        }

        SSL := false
        for i, field := range fields {
            if i % 2 == 1 {
                for _, a := range getABA(field, true) {
                    SSL = SSL || aba[a]
                }
            }
        }

        if TLS && !noTLS {
            ans1++
        }

        if SSL {
            ans2++
        }
    }

    return fmt.Sprintf("%d, %d", ans1, ans2)
}
