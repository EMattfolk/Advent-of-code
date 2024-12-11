-module(day11).

-export([ solve/1 ]).

transform({0, Count}) -> [{1, Count}];
transform({Stone, Count}) ->
    Binary = integer_to_binary(Stone),
    IsEven = byte_size(Binary) rem 2 =:= 0,
    case IsEven of
        true ->
            Half = trunc(byte_size(Binary) / 2),
            <<A:Half/binary, B:Half/binary>> = Binary,
            [{binary_to_integer(A), Count}, {binary_to_integer(B), Count}];
        false ->
            [{Stone * 2024, Count}]
    end.

blink(Stones) ->
    maps:map(fun (_, V) -> lists:sum(V) end, utils:group(lists:flatmap(fun transform/1, maps:to_list(Stones)))).

solve(Input) ->
    Stones = maps:from_list([{S, 1} || S <- utils:ints(Input)]),
    { lists:sum(lists:map(fun ({_, Count}) -> Count end, maps:to_list(utils:apply_n(25, fun blink/1, Stones))))
    , lists:sum(lists:map(fun ({_, Count}) -> Count end, maps:to_list(utils:apply_n(75, fun blink/1, Stones))))
    }.
