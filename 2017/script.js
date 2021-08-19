import { solutions } from "./src/solutions.js";

const browser = typeof document !== "undefined";

let _performance = typeof performance === "undefined" ? undefined : performance;

if (!browser) {
    (async () => {
        _performance = (await import("perf_hooks")).performance;
    })();
}

const runAll = async () => {
    if (browser) {
        document.getElementById("results").innerHTML = "";
    }

    for (let day = 1; day <= solutions.length; day++) {
        let elapsed = 0;
        let inputFile = "input/" + ("0" + day).slice(-2) + ".txt";
        let input = browser ?
            await fetch(inputFile).then(response => response.text())
            :
            (await import("fs")).readFileSync(inputFile).toString();

        elapsed = _performance.now();
        let ans = solutions[day - 1](day !== 19 ? input.trim() : input)
        elapsed = _performance.now() - elapsed;

        if (ans.length === 0) {
            return;
        }

        let text = (" " + day).slice(-2) + ": "
                 + ("   " + elapsed.toFixed(3)).slice(-8) + "ms ";

        let ansEntry = undefined;
        if (browser) {
            ansEntry = document.createElement("pre");
            ansEntry.innerHTML = text + "<code id=\"first\">" + ans[0] + "</code>";
            if (ans.length == 2) {
                ansEntry.innerHTML += " <code id=\"second\">" + ans[1] + "</code>";
            }
        } else {
            text += ans[0] + (ans[1] ? ", " + ans[1] : "");
        }

        if (browser) {
            let listEntry = document.createElement("li");
            listEntry.appendChild(ansEntry);
            document.getElementById("results").appendChild(listEntry);
        } else {
            console.log(text);
        }
    }
}

if (browser) {
    document.getElementById("runButton")
            .addEventListener("click", runAll);
} else {
    runAll()
}
