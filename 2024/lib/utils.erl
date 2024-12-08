-module(utils).

-export([ ints/1, ints/2, lines/1, sections/1, par/2, group/1 ]).

ints(S) -> ints(S, "|, \n").
ints(S, Sep) -> lists:map(fun binary_to_integer/1, string:lexemes(S, Sep)).
lines(S) -> string:lexemes(S, "\n").
sections(S) -> string:split(S, "\n\n").
par(F, L) ->
    Parent = self(),
    Ref = make_ref(),
    lists:foreach(fun(V) -> spawn(fun() -> Parent ! {Ref, F(V)} end) end, L),
    lists:map(fun (_) -> receive {Ref, V} -> V end end, L).

group([]) -> #{};
group([{A, B} | Rest]) ->
    maps:update_with(A, fun (Acc) -> [B | Acc] end, [B], group(Rest)).
