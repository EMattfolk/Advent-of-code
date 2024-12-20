-module(day18).

-export([solve/1]).

split([]) ->
    [];
split([A, B | Rest]) ->
    [{A, B} | split(Rest)].

-define(Size, 71).
in_bounds({X, Y}) -> 0 =< X andalso X < ?Size andalso 0 =< Y andalso Y < ?Size.

bfs(Grid, Visited, Q) ->
    case queue:peek(Q) of
        empty ->
            Visited;
        {value, {Steps, Pos = {X, Y}}} ->
            case
                sets:is_element(Pos, Grid) orelse maps:is_key(Pos, Visited) orelse
                    not in_bounds(Pos)
            of
                false ->
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
                true ->
                    bfs(Grid, Visited, queue:drop(Q))
            end
    end.

traverse(Parsed, Bytes) ->
    Grid = sets:from_list(lists:sublist(Parsed, Bytes), [{version, 2}]),
    bfs(Grid, #{}, queue:in({0, {0, 0}}, queue:new())).

binary_search(List, F) ->
    Length = length(List),
    Middle = Length div 2,
    case Middle of
        0 ->
            hd(List);
        _ ->
            Item = lists:nth(Middle, List),

            case F(Item) of
                true -> binary_search(lists:sublist(List, Middle), F);
                false -> binary_search(lists:nthtail(Middle, List), F)
            end
    end.

solve(Input) ->
    Parsed = split(utils:ints(Input)),
    #{{70, 70} := Ans1} = traverse(Parsed, 1024),
    {Ans1,
        lists:nth(
            binary_search(
                lists:seq(1, length(Parsed)),
                fun(I) -> not maps:is_key({70, 70}, traverse(Parsed, I)) end
            ),
            Parsed
        )}.
