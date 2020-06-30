export default function solve20(input) {
    let ans1 = 0;
    let ans2 = 0;

    function newParticle(line) {
        let splits = line.split(/[apv=, <>]+/).map(n => parseInt(n)).slice(1);
        return {
            p: [splits[0], splits[1], splits[2]],
            v: [splits[3], splits[4], splits[5]],
            a: [splits[6], splits[7], splits[8]],
        };
    }

    let particles = [];

    input.split("\n").forEach(line => particles.push(newParticle(line)));

    let minA = Number.MAX_SAFE_INTEGER;

    particles.forEach((particle, i) => {
        let a = Math.abs(particle.a[0]) + Math.abs(particle.a[1]) + Math.abs(particle.a[2]);
        if (a < minA) {
            minA = a;
            ans1 = i;
        }
    });

    function integrate(particle) {
        particle.v[0] += particle.a[0];
        particle.v[1] += particle.a[1];
        particle.v[2] += particle.a[2];
        particle.p[0] += particle.v[0];
        particle.p[1] += particle.v[1];
        particle.p[2] += particle.v[2];
    }

    for (let i = 0; i < 50; i++) {

        let positions = new Map();

        particles.forEach((particle, i) => {
            let posString = particle.p.toString();

            if (!positions.has(posString)) {
                positions.set(posString, []);
            }

            positions.get(posString).push(i);
        });

        let collisions = new Set();

        positions.forEach((value, key) => {
            if (value.length > 1) {
                value.forEach((i) => collisions.add(i));
            }
        });

        let sorted = [];

        collisions.forEach(i => sorted.push(i));

        sorted = sorted.sort((a, b) => b - a).forEach(i => particles.splice(i, 1));

        particles.forEach(particle => integrate(particle));
    }

    ans2 = particles.length;

    return [ans1, ans2];
}
