export default function solve09(input) {
    let ans1 = 0;
    let ans2 = 0;

    function parseGroup(index, depth) {
        ans1 += depth;
        index = parseGroupContent(index + 1, depth + 1);
        return index + 1;
    }

    function parseGarbage(index) {
        ans2--;
        while (input[index] != ">") {
            if (input[index] == "!") {
                index++;
                ans2--;
            }
            index++;
            ans2++;
        }

        return index + 1;
    }

    function parseGroupContent(index, depth) {
        while (input[index] != "}") {
            if (input[index] == ",") {
                index++;
            }

            if (input[index] == "{") {
                index = parseGroup(index, depth);
            } else if (input[index] == "<") {
                index = parseGarbage(index);
            } else {
                console.log(index);
            }
        }

        return index;
    }

    parseGroup(0, 1);

    return [ans1, ans2];
}
