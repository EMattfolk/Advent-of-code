-module(day20).

-export([solve/1]).

bfs(Grid, Visited, Q) ->
    case queue:peek(Q) of
        empty ->
            Visited;
        {value, {Steps, Pos = {X, Y}}} ->
            case not maps:is_key(Pos, Visited) andalso maps:get(Pos, Grid) =/= $# of
                true ->
                    New =
                        [
                            {X + 1, Y},
                            {X - 1, Y},
                            {X, Y + 1},
                            {X, Y - 1}
                        ],
                    bfs(
                        Grid,
                        maps:put(Pos, Steps, Visited),
                        lists:foldl(
                            fun(P, Acc) -> queue:in({Steps + 1, P}, Acc) end, queue:drop(Q), New
                        )
                    );
                false ->
                    bfs(Grid, Visited, queue:drop(Q))
            end
    end.

find_faster(Dist, Visited, {X, Y}) ->
    length(
        lists:filter(
            fun(P) ->
                maps:get(P, Visited, 0) - (maps:get({X, Y}, Visited) + p:manhattan(P, {X, Y})) >=
                    100
            end,
            [
                {X + Xo, Y + Yo}
             || Xo <- lists:seq(-Dist, Dist),
                Yo <- lists:seq(-Dist, Dist),
                abs(Xo) + abs(Yo) =< Dist
            ]
        )
    ).

solve(Input) ->
    GridList = utils:grid(Input),
    [Start] = [P || {P, C} <- GridList, C =:= $S],
    [End] = [P || {P, C} <- GridList, C =:= $E],
    Grid = (maps:from_list(GridList))#{Start := $., End := $.},
    Visited = bfs(Grid, #{}, queue:from_list([{0, Start}])),
    % 1052793 too high
    % 1056371 too high
    {
        lists:sum([find_faster(2, Visited, P) || P <- maps:keys(Visited)]),
        lists:sum([find_faster(20, Visited, P) || P <- maps:keys(Visited)])
    }.
