-module(day06).

-export([ solve/1 ]).

next_dir({X, Y}) -> {-Y, X}.

walk(Map, Pos = {X, Y}, Dir = {Xo, Yo}) ->
    case maps:get(Pos, Map, done) of
        done -> #{};
        $# -> walk(Map, {X - Xo, Y - Yo}, next_dir(Dir));
        _ -> sets:add_element(Pos, walk(Map, {X + Xo, Y + Yo}, Dir))
    end.

eventually_same(Visited, Map, Pos = {X, Y}, Dir = {Xo, Yo}) ->
    case maps:get(Pos, Map, done) of
        done -> false;
        $# -> eventually_same(Visited, Map, {X - Xo, Y - Yo}, next_dir(Dir));
        _ -> case sets:is_element({Pos, Dir}, Visited) of
                 true -> true;
                 false ->
                     eventually_same(sets:add_element({Pos, Dir}, Visited), Map, {X + Xo, Y + Yo}, Dir)
             end
    end.

walk2(0, _, _, _, _) -> 0;
walk2(Counter, Visited, Map, Pos = {X, Y}, Dir = {Xo, Yo}) ->
    case maps:get(Pos, Map, done) of
        done -> 0;
        $# -> walk2(Counter - 1, Visited, Map, {X - Xo, Y - Yo}, next_dir(Dir));
        _ ->
            NewPos = {X + Xo, Y + Yo},
            case maps:is_key(NewPos, Map) andalso not maps:is_key(NewPos, Visited) andalso eventually_same(Visited, Map#{NewPos => $#}, Pos, Dir) of
                true -> 1;
                false -> 0
            end +  walk2(Counter - 1, sets:add_element(Pos, sets:add_element({Pos, Dir}, Visited)), Map, {X + Xo, Y + Yo}, Dir)
    end.

interval() -> 300.

walk3(Counter, P, Visited, Map, Pos = {X, Y}, Dir = {Xo, Yo}) ->
    {NewCounter, Spawned} =
        case Counter of
            0 -> spawn(fun () -> P ! walk2(interval(), Visited, Map, Pos, Dir) end), {interval(), 1};
            _ -> {Counter, 0}
        end,
    case maps:get(Pos, Map, done) of
        done -> 0;
        $# -> walk3(NewCounter - 1, P, Visited, Map, {X - Xo, Y - Yo}, next_dir(Dir));
        _ -> walk3(NewCounter - 1, P, sets:add_element(Pos, sets:add_element({Pos, Dir}, Visited)), Map, {X + Xo, Y + Yo}, Dir)
    end + Spawned.

await_all(0) -> 0;
await_all(Count) ->
    receive
        N -> N
    end + await_all(Count - 1).

solve(Input) ->
    Lists = lists:map(fun binary_to_list/1, utils:lines(Input)),
    % Size = length(Lists),
    Indexes = [{{X, Y}, Char} || {Y, Row} <- lists:enumerate(Lists), {X, Char} <- lists:enumerate(Row)],
    Map = maps:from_list(Indexes),
    [{Start, $^}] = lists:filter(fun ({_, C}) -> C == $^ end, Indexes),
    ToAwait = walk3(0, self(), #{}, Map, Start, {0, -1}),
    { maps:size(walk(Map, Start, {0, -1}))
    , await_all(ToAwait)
    }.
    % length(lists:filter(fun (Pos) -> case maps:get(Pos, Map) of $^ -> false; _ -> eventually_same(#{}, Map#{Pos => $#}, Start, {0, -1}) end end, maps:keys(Visited))) ~ 6s
