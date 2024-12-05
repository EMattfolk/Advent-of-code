-module(utils).

-export([ ints/1, lines/1, sections/1 ]).

ints(S) -> lists:map(fun binary_to_integer/1, string:lexemes(S, "|, \n")).
lines(S) -> string:lexemes(S, "\n").
sections(S) -> string:split(S, "\n\n").
