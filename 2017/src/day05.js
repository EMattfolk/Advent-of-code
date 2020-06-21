export default function solve05(input) {
    let ans1 = 0;
    let ans2 = 0;

    let maze = input.split("\n").map((line) => parseInt(line));
    let mazeCopy = maze.slice();
    let index = 0;

    while (index >= 0 && index < maze.length) {
        index += maze[index]++;
        ans1++;
    }

    maze = mazeCopy;

    index = 0;
    while (index >= 0 && index < maze.length) {
        let oldIndex = index;
        index += maze[index];

        if (maze[oldIndex] >= 3) {
            maze[oldIndex]--;
        } else {
            maze[oldIndex]++;
        }

        ans2++;
    }

    return [ans1, ans2];
}
