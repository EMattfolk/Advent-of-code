-module(p).

-export([ add/2, sub/2, mul/2, neg/1 ]).

add({X1, Y1}, {X2, Y2}) -> {X1 + X2, Y1 + Y2}.
sub({X1, Y1}, {X2, Y2}) -> {X1 - X2, Y1 - Y2}.
mul({X, Y}, V) -> {X * V, Y * V}.
neg({X, Y}) -> {-X, -Y}.
