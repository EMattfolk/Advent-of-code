-module(day06).

-export([ solve/1 ]).

next_dir({X, Y}) -> {-Y, X}.

walk(Map, Pos = {X, Y}, Dir = {Xo, Yo}) ->
    case maps:get(Pos, Map, done) of
        done -> #{};
        $# -> walk(Map, {X - Xo, Y - Yo}, next_dir(Dir));
        _ -> maps:update_with(Pos, fun (Acc) -> sets:add_element(Dir, Acc) end, #{Dir =>[]}, walk(Map, {X + Xo, Y + Yo}, Dir))
    end.

eventually_same(Visited, Map, Pos = {X, Y}, Dir = {Xo, Yo}) ->
    case maps:get(Pos, Map, done) of
        done -> false;
        $# -> eventually_same(Visited, Map, {X - Xo, Y - Yo}, next_dir(Dir));
        _ -> case sets:is_element(Dir, maps:get(Pos, Visited, #{})) of
                 true -> true;
                 false ->
                     eventually_same(maps:update_with(Pos, fun (Acc) -> sets:add_element(Dir, Acc) end, #{Dir =>[]}, Visited), Map, {X + Xo, Y + Yo}, Dir)
             end
    end.

walk2(Visited, Map, Pos = {X, Y}, Dir = {Xo, Yo}) ->
    case maps:get(Pos, Map, done) of
        done -> 0;
        $# -> walk2(Visited, Map, {X - Xo, Y - Yo}, next_dir(Dir));
        _ ->
            NewPos = {X + Xo, Y + Yo},
            case maps:is_key(NewPos, Map) andalso not maps:is_key(NewPos, Visited) andalso eventually_same(Visited, Map#{NewPos => $#}, Pos, Dir) of
                true -> 1;
                false -> 0
            end + walk2(maps:update_with(Pos, fun (Acc) -> sets:add_element(Dir, Acc) end, #{Dir =>[]}, Visited), Map, {X + Xo, Y + Yo}, Dir)
    end.

solve(Input) ->
    Lists = lists:map(fun binary_to_list/1, utils:lines(Input)),
    % Size = length(Lists),
    Indexes = [{{X, Y}, Char} || {Y, Row} <- lists:enumerate(Lists), {X, Char} <- lists:enumerate(Row)],
    Map = maps:from_list(Indexes),
    [{Start, $^}] = lists:filter(fun ({_, C}) -> C == $^ end, Indexes),
    Visited = walk(Map, Start, {0, -1}),
    { maps:size(Visited)
    , walk2(#{}, Map, Start, {0, -1})
    }.
    % length(lists:filter(fun (Pos) -> case maps:get(Pos, Map) of $^ -> false; _ -> eventually_same(#{}, Map#{Pos => $#}, Start, {0, -1}) end end, maps:keys(Visited))) ~ 6s
