-module(day16).

-export([solve/1]).

right({X, Y}) -> {-Y, X}.
left({X, Y}) -> {Y, -X}.

djik(Grid, Visited, [{Pos, Cost, Dir} | Rest]) ->
    case maps:get({Pos, Dir}, Visited, 10000000) >= Cost andalso maps:get(Pos, Grid) =/= $# of
        true ->
            New = lists:filter(
                fun({P, C, D}) ->
                    maps:get({P, D}, Visited, 10000000) >= C andalso maps:get(P, Grid) =/= $#
                end,
                [
                    {p:add(Pos, Dir), Cost + 1, Dir},
                    {Pos, Cost + 1000, right(Dir)},
                    {Pos, Cost + 1000, left(Dir)}
                ]
            ),
            djik(
                Grid,
                lists:foldl(fun({P, C, D}, Acc) -> maps:put({P, D}, C, Acc) end, Visited, New),
                New ++ Rest
            );
        false ->
            djik(Grid, Visited, Rest)
    end;
djik(_, Visited, []) ->
    Visited.

backtrack(Dists, Visited, {Pos, Cost, Dir}) ->
    New =
        [
            {p:add(Pos, Dir), Cost - 1, Dir},
            {Pos, Cost - 1000, right(Dir)},
            {Pos, Cost - 1000, left(Dir)}
        ],
    lists:foldl(
        fun({P, C, D}, Acc) ->
            case maps:get({P, p:mul(D, -1)}, Dists, C - 1) =:= C of
                true -> backtrack(Dists, sets:add_element({P, D}, Acc), {P, C, D});
                false -> Acc
            end
        end,
        Visited,
        New
    ).

solve(Input) ->
    GridList = utils:grid(Input),
    [Start] = [P || {P, C} <- GridList, C =:= $S],
    [End] = [P || {P, C} <- GridList, C =:= $E],
    Grid = (maps:from_list(GridList))#{Start := $., End := $.},
    % T = ets:new(day16, [ordered_set]),
    Dists = djik(Grid, #{{Start, {1, 0}} => 0}, [{Start, 0, {1, 0}}]),
    Ans1 = min(maps:get({End, {1, 0}}, Dists, 10000000), maps:get({End, {0, -1}}, Dists, 10000000)),
    {Ans1,
        sets:size(
            sets:map(
                fun({P, _}) -> P end,
                backtrack(Dists, #{{End, {-1, 0}} => Ans1}, {End, Ans1, {-1, 0}})
            )
        )}.
