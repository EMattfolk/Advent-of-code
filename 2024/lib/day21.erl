-module(day21).

-export([solve/1]).

keypad(N) ->
    case N of
        $7 -> {0, 0};
        $8 -> {1, 0};
        $9 -> {2, 0};
        $4 -> {0, 1};
        $5 -> {1, 1};
        $6 -> {2, 1};
        $1 -> {0, 2};
        $2 -> {1, 2};
        $3 -> {2, 2};
        $0 -> {1, 3};
        $A -> {2, 3}
    end.

dpad(D) ->
    case D of
        $^ -> {1, 0};
        $A -> {2, 0};
        $< -> {0, 1};
        $v -> {1, 1};
        $> -> {2, 1}
    end.

diffs(_, _, <<>>) ->
    [];
diffs(Pos, F, <<C, Rest/binary>>) ->
    Fc = F(C),
    [{Pos, p:sub(Fc, Pos)} | diffs(Fc, F, Rest)].

tr(F, {{X, Y}, {Xd, Yd}}) ->
    MoveX =
        case Xd of
            -3 -> ~"<<<";
            -2 -> ~"<<";
            -1 -> ~"<";
            0 -> ~"";
            1 -> ~">";
            2 -> ~">>"
            %3 -> ~">>"
        end,
    MoveY =
        case Yd of
            -3 -> ~"^^^";
            -2 -> ~"^^";
            -1 -> ~"^";
            0 -> ~"";
            1 -> ~"v";
            2 -> ~"vv";
            3 -> ~"vvv"
        end,
    case
        (Xd < 0 andalso
            not ((Y =:= 3) andalso (X + Xd =:= 0) andalso (F =:= (fun keypad/1)) orelse
                (Y =:= 0) andalso (X + Xd =:= 0) andalso (F =:= (fun dpad/1)))) orelse
            ((X =:= 0) andalso (Y + Yd =:= 3) andalso (F =:= (fun keypad/1)) orelse
                (X =:= 0) andalso (Y + Yd =:= 0) andalso (F =:= (fun dpad/1)))
    of
        true -> <<MoveX/binary, MoveY/binary, "A">>;
        false -> <<MoveY/binary, MoveX/binary, "A">>
    end.

expand(F, Code) ->
    iolist_to_binary(lists:map(fun(D) -> tr(F, D) end, diffs(F($A), F, Code))).

grouped_expand(Moves) when is_binary(Moves) ->
    maps:map(
        fun(_, V) -> length(V) end,
        utils:group(
            lists:map(
                fun(S) -> {expand(fun dpad/1, <<S/binary, "A">>), 1} end,
                lists:droplast(string:split(Moves, ~"A", all))
            )
        )
    );
grouped_expand(Groups) ->
    maps:map(
        fun(_, V) -> lists:sum(V) end,
        utils:group([
            {M, C * Count}
         || {Moves, Count} <- maps:to_list(Groups),
            {M, C} <- maps:to_list(grouped_expand(Moves))
        ])
    ).

solve(Input) ->
    % 186150050707808 too low
    {
        lists:sum(
            lists:map(
                fun(Code = <<N:3/binary, _>>) ->
                    binary_to_integer(N) *
                        lists:sum([
                            byte_size(
                                Moves
                            ) * Count
                         || Moves := Count <-
                                utils:apply_n(2, fun grouped_expand/1, expand(fun keypad/1, Code))
                        ])
                end,
                utils:lines(Input)
            )
        ),
        lists:sum(
            lists:map(
                fun(Code = <<N:3/binary, _>>) ->
                    binary_to_integer(N) *
                        lists:sum([
                            byte_size(
                                Moves
                            ) * Count
                         || Moves := Count <-
                                utils:apply_n(25, fun grouped_expand/1, expand(fun keypad/1, Code))
                        ])
                end,
                utils:lines(Input)
            )
        )
    }.
