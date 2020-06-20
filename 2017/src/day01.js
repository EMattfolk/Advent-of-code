export default function solve01(input) {
    let ans1 = 0;
    let ans2 = 0;

    let zero = "0".charCodeAt()

    for (let i = 0; i < input.length; i++) {
        if (input.charAt(i) === input.charAt((i+1) % input.length)) {
            ans1 += input.charCodeAt(i) - zero;
        }
        if (input.charAt(i) === input.charAt((i + input.length / 2) % input.length)) {
            ans2 += input.charCodeAt(i) - zero;
        }
    }

    return [ans1, ans2];
}
