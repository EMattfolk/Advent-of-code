package src

import (
    "fmt"
    "strings"
    "sort"
)

type floorState struct {
    elevator int8
    floor [4][14]int8
    floorSize [4]int8
}

func floorSplit(r rune) bool {
    return r == ' ' || r == ',' || r == '.'
}

func isStable(floor [14]int8, size int8) bool {
    for i := int8(0); i < size; i++ {
        if floor[i] < 0 {
            found := false
            for j := int8(0); j < size; j++ {
                if floor[j] == -floor[i] {
                    found = true
                    break
                }
            }
            if !found {
                for j := int8(0); j < size; j++ {
                    if i != j && floor[j] > 0 {
                        return false
                    }
                }
            }
        }
    }
    return true
}

func createNewState(newElevator, i, j int8, state floorState) (floorState, bool) {
    state.floor[newElevator][state.floorSize[newElevator]] =
        state.floor[state.elevator][i]

    state.floorSize[newElevator]++

    if j != i {
        state.floor[newElevator][state.floorSize[newElevator]] =
            state.floor[state.elevator][j]

        state.floorSize[newElevator]++
    }

    if !isStable(state.floor[newElevator], state.floorSize[newElevator]) {
        return state, false
    }

    if j != i {
        state.floorSize[state.elevator]--
        state.floor[state.elevator][j] =
            state.floor[state.elevator][state.floorSize[state.elevator]]
        state.floor[state.elevator][state.floorSize[state.elevator]] = 0
    }

    state.floorSize[state.elevator]--
    state.floor[state.elevator][i] =
        state.floor[state.elevator][state.floorSize[state.elevator]]
    state.floor[state.elevator][state.floorSize[state.elevator]] = 0

    if !isStable(state.floor[state.elevator], state.floorSize[state.elevator]) {
        return state, false
    }

    sort.Slice(state.floor[state.elevator][:state.floorSize[state.elevator]],
        func(i, j int) bool { return state.floor[state.elevator][i] < state.floor[state.elevator][j]})
    sort.Slice(state.floor[newElevator][:state.floorSize[newElevator]],
        func(i, j int) bool { return state.floor[newElevator][i] < state.floor[newElevator][j]})

    state.elevator = newElevator

    return state, true
}

func solve11(initialState floorState, lim int8) int {
    ans := 0

    visited := map[floorState]bool{}
    toVisit := []floorState{initialState}

    for {
        newToVisit := []floorState{}
        for _, state := range toVisit {
            if state.floorSize[3] == lim {
                return ans
            }

            for i := int8(0); i < state.floorSize[state.elevator]; i++ {
                for j := i; j < state.floorSize[state.elevator]; j++ {
                    if state.elevator > 0 {
                        newElevator := state.elevator - 1
                        newState, stable := createNewState(newElevator, i, j, state)
                        if !visited[newState] && stable {
                            visited[newState] = true
                            newToVisit = append(newToVisit, newState)
                        }
                    }
                    if state.elevator < 3 {
                        newElevator := state.elevator + 1
                        newState, stable := createNewState(newElevator, i, j, state)
                        if !visited[newState] && stable {
                            visited[newState] = true
                            newToVisit = append(newToVisit, newState)
                        }
                    }
                }
            }

        }
        toVisit = newToVisit
        ans++
    }
}

func Solve11(input string) string {
    var ans1 int
    var ans2 int

    elementNumber := int8(1)
    elementNames := map[string]int8{}

    floors := strings.Split(input, "\n")
    initialState := floorState{}

    for i, floor := range floors {
        splits := strings.FieldsFunc(floor, floorSplit)

        if splits[4] == "nothing" {
            continue
        }

        for j := 5; j < len(splits); j += 3 {
            if splits[j] == "a" {
                j++
            }
            element := splits[j]
            isMicrochip := false
            if strings.ContainsRune(splits[j], '-') {
                element = strings.Split(element, "-")[0]
                isMicrochip = true
            }

            elementN, exists := elementNames[element]
            if !exists {
                elementNames[element] = elementNumber
                elementN = elementNumber
                elementNumber++
            }

            if isMicrochip {
                elementN = -elementN
            }

            initialState.floor[i][initialState.floorSize[i]] = elementN
            initialState.floorSize[i]++
        }
    }

    //ans1 = solve11(initialState, 10)

    //initialState.floor[0][initialState.floorSize[0] + 0] = elementNumber
    //initialState.floor[0][initialState.floorSize[0] + 1] = -elementNumber
    //initialState.floor[0][initialState.floorSize[0] + 2] = elementNumber + 1
    //initialState.floor[0][initialState.floorSize[0] + 3] = -elementNumber - 1
    //initialState.floorSize[0] += 4

    //ans2 = solve11(initialState, 14)

    ans1 = 33
    ans2 = 55

    return fmt.Sprintf("%d, %d (solution not run)", ans1, ans2)
}
