-module(day16).

-export([solve/1]).

right({X, Y}) -> {-Y, X}.
left({X, Y}) -> {Y, -X}.

djik(Grid, Visited, T) ->
    case pop(T) of
        empty ->
            Visited;
        {Cost, Pos, Dir, Rest} ->
            case
                maps:get({Pos, Dir}, Visited, 10000000) > Cost andalso maps:get(Pos, Grid) =/= $#
            of
                true ->
                    New =
                        [
                            {Cost + 1, p:add(Pos, Dir), Dir},
                            {Cost + 1000, Pos, right(Dir)},
                            {Cost + 1000, Pos, left(Dir)}
                        ],
                    djik(
                        Grid,
                        maps:put({Pos, Dir}, Cost, Visited),
                        push(Rest, New)
                    );
                false ->
                    djik(Grid, Visited, Rest)
            end
    end.

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

push(T, [{C, P, D} | Rest]) ->
    push(
        case gb_trees:lookup(C, T) of
            {value, Value} ->
                gb_trees:insert(C, ordsets:add_element({P, D}, Value), gb_trees:delete(C, T));
            none ->
                gb_trees:insert(C, [{P, D}], T)
        end,
        Rest
    );
push(T, []) ->
    T.

pop(T) ->
    case gb_trees:is_empty(T) of
        true ->
            empty;
        false ->
            case gb_trees:take_smallest(T) of
                {C, [{P, D}], Tr} ->
                    {C, P, D, Tr};
                {C, [{P, D} | Rest], Tr} ->
                    {C, P, D, gb_trees:insert(C, Rest, Tr)}
            end
    end.

solve(Input) ->
    GridList = utils:grid(Input),
    [Start] = [P || {P, C} <- GridList, C =:= $S],
    [End] = [P || {P, C} <- GridList, C =:= $E],
    Grid = (maps:from_list(GridList))#{Start := $., End := $.},
    Dists = djik(Grid, #{}, gb_trees:insert(0, [{Start, {1, 0}}], gb_trees:empty())),
    Ans1 = min(maps:get({End, {1, 0}}, Dists, 10000000), maps:get({End, {0, -1}}, Dists, 10000000)),
    Ans2 = sets:size(
        sets:map(
            fun({P, _}) -> P end,
            backtrack(Dists, #{{End, {-1, 0}} => Ans1}, {End, Ans1, {-1, 0}})
        )
    ),
    {Ans1, Ans2}.
