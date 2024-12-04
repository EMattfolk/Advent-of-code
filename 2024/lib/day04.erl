-module(day04).

-export([ solve/1 ]).

offsets() ->
    [{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}].

in_bounds(Map, X, Y) ->
    0 =< X andalso X < maps:size(Map) andalso 0 =< Y andalso Y < maps:size(Map).

xmas_at(Map, X, Y) -> 
    length(lists:filter(
      fun ({Xo, Yo}) ->
            Indexes = [{X + C * Xo, Y + C * Yo} || C <- [0, 1, 2, 3]],
            case lists:all(fun ({C, R}) -> in_bounds(Map, C, R) end, Indexes) of
                true -> lists:map(fun ({C, R}) -> binary:at(maps:get(R, Map), C) end, Indexes) == "XMAS";
                false -> false
            end
      end, offsets())).

mas_at(Map, X, Y) -> 
    Indexes = [{X - 1, Y - 1}, {X + 1, Y - 1}, {X, Y}, {X - 1, Y + 1}, {X + 1, Y + 1}],
    case lists:all(fun ({C, R}) -> in_bounds(Map, C, R) end, Indexes) of
        true -> 
            Letters = lists:map(fun ({C, R}) -> binary:at(maps:get(R, Map), C) end, Indexes),
            lists:any(fun (Cand) -> Cand == Letters end, ["MMASS", "SSAMM", "MSAMS", "SMASM"]);
        false ->
            false
    end.

solve(Input) ->
    Lines = utils:lines(Input),
    Map = maps:from_list(lists:enumerate(0, Lines)),
    Indexes = [{X, Y} || X <- lists:seq(0, maps:size(Map) - 1), Y <- lists:seq(0, maps:size(Map) - 1)],
    { lists:sum([xmas_at(Map, X, Y) || {X, Y} <- Indexes])
    , lists:sum([1 || {X, Y} <- Indexes, mas_at(Map, X, Y)])
    }.
