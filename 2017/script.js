import { solutions } from "/src/solutions.js";

let button = document.getElementById("runButton");
button.addEventListener("click", () => {
    let results = document.getElementById("results");
    results.innerHTML = "";

    solutions.forEach(async function(fn, i) {
        let day = i + 1;
        let elapsed = 0;
        let ans = await fetch("input/" + (day < 10 ? "0" : "") + day + ".txt")
            .then(response => response.text())
            .then(text => {
                elapsed = performance.now();
                let ans = fn(text.trim())
                elapsed = performance.now() - elapsed;
                return ans;
            });

        if (ans.length === 0) {
            return;
        }

        let ansEntry = document.createElement("li");
        ansEntry.innerHTML = day + ": " + elapsed.toFixed(3) + "ms";
        ansEntry.innerHTML += "<span id=\"first\">" + ans[0] + "</span>";
        if (ans.length == 2) {
            ansEntry.innerHTML += "<span id=\"second\">" + ans[1] + "</span>";
        }

        results.appendChild(ansEntry);
    })
});
