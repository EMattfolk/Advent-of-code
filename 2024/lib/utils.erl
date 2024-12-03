-module(utils).

-export([ ints/1 ]).

ints(S) -> lists:map(fun binary_to_integer/1, string:lexemes(S, " \n")).
