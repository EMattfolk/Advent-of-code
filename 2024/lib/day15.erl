-module(day15).

-export([solve/1]).

parse_moves(<<>>) -> [];
parse_moves(<<"<", Rest/binary>>) -> [{-1, 0} | parse_moves(Rest)];
parse_moves(<<"^", Rest/binary>>) -> [{0, -1} | parse_moves(Rest)];
parse_moves(<<">", Rest/binary>>) -> [{1, 0} | parse_moves(Rest)];
parse_moves(<<"v", Rest/binary>>) -> [{0, 1} | parse_moves(Rest)];
parse_moves(<<"\n", Rest/binary>>) -> parse_moves(Rest).

do_moves(Grid, _, []) ->
    Grid;
do_moves(Grid, Pos, [Dir | Rest]) ->
    NextPos = p:add(Pos, Dir),
    NewGrid = push(Grid, NextPos, Dir),
    % utils:print_grid(maps:put(NextPos, $7, NewGrid)),
    % timer:sleep(100),
    case maps:get(NextPos, NewGrid) of
        $@ -> do_moves(NewGrid, NextPos, Rest);
        $. -> do_moves(NewGrid, NextPos, Rest);
        $# -> do_moves(NewGrid, Pos, Rest);
        $O -> do_moves(NewGrid, Pos, Rest);
        $[ -> do_moves(NewGrid, Pos, Rest);
        $] -> do_moves(NewGrid, Pos, Rest)
    end.

push(Grid, Pos, Dir = {Dx, _}) ->
    case maps:get(Pos, Grid) of
        $@ ->
            Grid;
        $. ->
            Grid;
        $# ->
            Grid;
        $O ->
            NextPos = p:add(Pos, Dir),
            NewGrid = push(Grid, NextPos, Dir),
            case maps:get(NextPos, NewGrid) of
                $@ -> NewGrid#{Pos := $., NextPos := $O};
                $. -> NewGrid#{Pos := $., NextPos := $O};
                $# -> NewGrid;
                $O -> NewGrid
            end;
        $[ ->
            case Dx =:= 0 of
                true ->
                    Other = p:add({1, 0}, Pos),
                    NextPos1 = p:add(Pos, Dir),
                    NextPos2 = p:add(Other, Dir),
                    NewGrid = push(push(Grid, NextPos1, Dir), NextPos2, Dir),
                    case {maps:get(NextPos1, NewGrid), maps:get(NextPos2, NewGrid)} of
                        {$@, $.} ->
                            NewGrid#{Pos := $., Other := $., NextPos1 := $[, NextPos2 := $]};
                        {$., $@} ->
                            NewGrid#{Pos := $., Other := $., NextPos1 := $[, NextPos2 := $]};
                        {$., $.} ->
                            NewGrid#{Pos := $., Other := $., NextPos1 := $[, NextPos2 := $]};
                        _ ->
                            % Rollback
                            Grid
                    end;
                false ->
                    Other = p:add({1, 0}, Pos),
                    NextPos = p:add(Pos, p:mul(Dir, 2)),
                    NewGrid = push(Grid, NextPos, Dir),
                    case maps:get(NextPos, NewGrid) of
                        $@ ->
                            NewGrid#{Pos := $., Other := $[, NextPos := $]};
                        $. ->
                            NewGrid#{Pos := $., Other := $[, NextPos := $]};
                        $# ->
                            NewGrid;
                        $[ ->
                            NewGrid
                    end
            end;
        $] ->
            case Dx =:= 0 of
                true ->
                    Other = p:add({-1, 0}, Pos),
                    NextPos1 = p:add(Pos, Dir),
                    NextPos2 = p:add(Other, Dir),
                    NewGrid = push(push(Grid, NextPos1, Dir), NextPos2, Dir),
                    case {maps:get(NextPos1, NewGrid), maps:get(NextPos2, NewGrid)} of
                        {$@, $.} ->
                            NewGrid#{Pos := $., Other := $., NextPos1 := $], NextPos2 := $[};
                        {$., $@} ->
                            NewGrid#{Pos := $., Other := $., NextPos1 := $], NextPos2 := $[};
                        {$., $.} ->
                            NewGrid#{Pos := $., Other := $., NextPos1 := $], NextPos2 := $[};
                        _ ->
                            % Rollback
                            Grid
                    end;
                false ->
                    Other = p:add({-1, 0}, Pos),
                    NextPos = p:add(Pos, p:mul(Dir, 2)),
                    NewGrid = push(Grid, NextPos, Dir),
                    case maps:get(NextPos, NewGrid) of
                        $@ ->
                            NewGrid#{Pos := $., Other := $], NextPos := $[};
                        $. ->
                            NewGrid#{Pos := $., Other := $], NextPos := $[};
                        $# ->
                            NewGrid;
                        $] ->
                            NewGrid
                    end
            end
    end.

solve(Input) ->
    [RawGrid, RawMoves] = utils:sections(Input),
    Grid = maps:from_list(utils:grid(RawGrid)),
    [Start] = [P || {P, C} <- maps:to_list(Grid), C =:= $@],
    Moves = parse_moves(RawMoves),
    % utils:print_grid(do_moves(Grid, Start, Moves)),
    Big = maps:from_list(
        lists:flatmap(
            fun({{X, Y}, C}) ->
                case C of
                    $@ -> [{{X * 2, Y}, $@}, {{X * 2 + 1, Y}, $.}];
                    $. -> [{{X * 2, Y}, $.}, {{X * 2 + 1, Y}, $.}];
                    $# -> [{{X * 2, Y}, $#}, {{X * 2 + 1, Y}, $#}];
                    $O -> [{{X * 2, Y}, $[}, {{X * 2 + 1, Y}, $]}]
                end
            end,
            maps:to_list(Grid)
        )
    ),
    [Start2] = [P || {P, C} <- maps:to_list(Big), C =:= $@],
    % utils:print_grid(do_moves(Big, Start2, Moves)),
    {
        lists:sum([
            X + 100 * Y
         || {{X, Y}, C} <- maps:to_list(do_moves(Grid, Start, Moves)), C =:= $O
        ]),
        lists:sum([
            X + 100 * Y
         || {{X, Y}, C} <- maps:to_list(do_moves(Big, Start2, Moves)), C =:= $[
        ])
    }.
