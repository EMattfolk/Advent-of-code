-module(day10).

-export([ solve/1 ]).

offsets() ->
    [{-1, 0}, {0, -1}, {0, 1}, {1, 0}].

score(Part, Grid, Start) -> score(Part, Grid, #{}, Start).
score(Part, Grid, Seen, Pos) ->
    case {Part =:= part1 andalso sets:is_element(Pos, Seen), maps:get(Pos, Grid, out)} of
        {true, _} -> {Seen, 0};
        {_, out} -> {Seen, 0};
        {false, $9} -> {sets:add_element(Pos, Seen), 1};
        {false, Char} ->
            lists:foldl(
              fun (P, {AccSeen, AccScore}) ->
                      {Se, Sc} = score(Part, Grid, AccSeen, P),
                      {Se, AccScore + Sc}
              end,
              {Seen, 0},
              [p:add(Pos, O) || O <- offsets(), maps:get(p:add(Pos, O), Grid, -999) - Char =:= 1])
    end.

solve(Input) ->
    Flat = utils:grid(Input),
    Grid = maps:from_list(Flat),
    { lists:sum([element(2, score(part1, Grid, P)) || {P, C} <- Flat, C =:= $0])
    , lists:sum([element(2, score(part2, Grid, P)) || {P, C} <- Flat, C =:= $0])
    }.
