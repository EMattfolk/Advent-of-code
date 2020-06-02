year=2015
session="your session here"

for i in $(seq 1 1 9); do
	curl --cookie "session=$session" "https://adventofcode.com/$year/day/$i/input" > "0$i.txt"
done
for i in $(seq 10 1 25); do
	curl --cookie "session=$session" "https://adventofcode.com/$year/day/$i/input" > "$i.txt"
done

echo "Done downloading inputs."
