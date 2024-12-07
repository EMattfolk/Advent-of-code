-module(day07).

-export([ solve/1 ]).

split_and_try(part1, [Target, Acc | Rest]) ->
    try_combinations(Target, Acc, Rest);
split_and_try(part2, [Target, Acc | Rest]) ->
    try_combinations2(Target, Acc, Rest).

try_combinations(Target, Target, []) -> true;
try_combinations(_, _, []) -> false;
try_combinations(Target, Acc, _) when Acc > Target -> false;
try_combinations(Target, Acc, [V|Rest]) ->
    try_combinations(Target, Acc + V, Rest)
    orelse try_combinations(Target, Acc * V, Rest).

try_combinations2(Target, Target, []) -> true;
try_combinations2(_, _, []) -> false;
try_combinations2(Target, Acc, _) when Acc > Target -> false;
try_combinations2(Target, Acc, [V|Rest]) ->
    try_combinations2(Target, Acc * V, Rest)
    orelse try_combinations2(Target, Acc + V, Rest)
    orelse try_combinations2(Target, binary_to_integer(<<(integer_to_binary(Acc))/binary, (integer_to_binary(V))/binary>>), Rest).


solve(Input) ->
    Parsed = [utils:ints(L, ": ") || L <- utils:lines(Input)],
    { lists:sum(lists:filtermap(fun (L = [Target|_]) -> case split_and_try(part1, L) of true -> {true, Target}; false -> false end end, Parsed))
    , lists:sum(lists:filtermap(fun (X) -> X end, utils:par(fun (L = [Target|_]) -> case split_and_try(part2, L) of true -> {true, Target}; false -> false end end, Parsed)))
    }.
