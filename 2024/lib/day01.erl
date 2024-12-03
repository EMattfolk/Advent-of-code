-module(day01).

-export([ solve/1 ]).

split([]) -> {[], []};
split([A, B | Rest]) ->
    {As, Bs} = split(Rest),
    {[A | As], [B | Bs]}.

solve(Input) ->
    {A, B} = split(utils:ints(Input)),
    Zipped = lists:zip(lists:sort(A), lists:sort(B), trim),
    { lists:sum([abs(I - J) || {I, J} <- Zipped])
    , lists:sum([I * length(lists:filter(fun(J) -> J == I end, B)) || I <- A])
    }.
