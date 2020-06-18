import solve01 from "/src/day01.js";

let functions = [
    solve01,
]

let button = document.getElementById("runButton");
button.addEventListener("click", () => {
    let results = document.getElementById("results");
    functions.forEach((fn) => {
        let ans = fn("yeet");
        if (ans === "") {
            return;
        }

        let ansEntry = document.createElement("li");
        ansEntry.textContent = ans;
        results.appendChild(ansEntry);
    })
});
