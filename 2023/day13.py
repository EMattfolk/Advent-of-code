def differences(arr1, arr2):
    return sum(1 for a, b in zip(arr1, arr2) for i, j in zip(a, b) if i != j)


def reflect_point(arr, allowed_differences):
    for i in range(1, len(arr)):
        size = min(i, len(arr) - i)

        # print(arr[i - size : i])
        # print(arr[i : i + size][::-1])
        if (
            differences(arr[i - size : i], arr[i : i + size][::-1])
            == allowed_differences
        ):
            return i


def solve(input):
    parsed = [c.split("\n") for c in input.split("\n\n")]
    ans1 = 0
    ans2 = 0
    for p in parsed:
        res = reflect_point(p, 0)
        if res is None:
            res = reflect_point(list(zip(*p)), 0)
            ans1 += res
        else:
            ans1 += res * 100
        res = reflect_point(p, 1)
        if res is None:
            res = reflect_point(list(zip(*p)), 1)
            ans2 += res
        else:
            ans2 += res * 100
    return (str(ans1), str(ans2))
