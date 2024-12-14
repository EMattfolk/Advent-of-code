-module(day12).

-export([solve/1]).

offsets() ->
    [{-1, 0}, {0, -1}, {0, 1}, {1, 0}].

offsets2() ->
    [{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}].

fill(Grid, Visited, Pos, C) ->
    case sets:is_element(Pos, Visited) orelse maps:get(Pos, Grid, empty) =/= C of
        true ->
            Visited;
        false ->
            lists:foldl(
                fun(O, Acc) ->
                    fill(Grid, Acc, p:add(Pos, O), C)
                end,
                sets:add_element(Pos, Visited),
                offsets()
            )
    end.

perim(Region) ->
    lists:sum(
        lists:map(
            fun(Pos) ->
                4 - length([1 || O <- offsets(), sets:is_element(p:add(Pos, O), Region)])
            end,
            sets:to_list(Region)
        )
    ).

perim2(Region) ->
    Expanded = sets:from_list(
        lists:flatmap(
            fun(P) ->
                T = p:mul(P, 2),
                [T, p:add(T, {1, 0}), p:add(T, {0, 1}), p:add(T, {1, 1})]
            end,
            sets:to_list(Region)
        )
    ),
    length(
        lists:filter(
            fun(Pos) ->
                case
                    length(
                        lists:filter(
                            fun(O) ->
                                sets:is_element(p:add(Pos, O), Expanded)
                            end,
                            offsets2()
                        )
                    )
                of
                    % Simple corner
                    3 -> true;
                    % Inner corner
                    7 -> true;
                    % Touching corner
                    4 -> true;
                    % On edge
                    5 -> false;
                    % Inner
                    8 -> false;
                    % 1 step out from inner corner
                    6 -> false
                end
            end,
            sets:to_list(Expanded)
        )
    ).

solve(Input) ->
    Grid = maps:from_list(utils:grid(Input)),
    {Regions, _} = lists:foldl(
        fun({Pos, C}, Acc = {Regions, Visited}) ->
            case sets:is_element(Pos, Visited) of
                true ->
                    Acc;
                false ->
                    Res = fill(Grid, #{}, Pos, C),
                    {
                        [Res | Regions],
                        sets:union(Visited, Res)
                    }
            end
        end,
        {[], #{}},
        maps:to_list(Grid)
    ),
    {
        lists:sum(lists:map(fun(Region) -> perim(Region) * sets:size(Region) end, Regions)),
        lists:sum(lists:map(fun(Region) -> perim2(Region) * sets:size(Region) end, Regions))
    }.
