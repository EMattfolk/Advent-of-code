year=2016
session=""

for i in $(seq 1 1 9); do
	curl --silent --cookie "session=$session" "https://adventofcode.com/$year/day/$i/input" > "0$i.txt"
	echo "Got day $i"
done
for i in $(seq 10 1 25); do
	curl --silent --cookie "session=$session" "https://adventofcode.com/$year/day/$i/input" > "$i.txt"
	echo "Got day $i"
done
