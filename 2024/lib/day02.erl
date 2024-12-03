-module(day02).

-export([ solve/1 ]).

is_safe(L) -> is_safe(L, inc) orelse is_safe(L, dec).
is_safe([_], _) -> true;
is_safe([A, B | Rest], inc) ->
    case B - A of
        1 -> is_safe([B | Rest], inc);
        2 -> is_safe([B | Rest], inc);
        3 -> is_safe([B | Rest], inc);
        _ -> false
    end;
is_safe([A, B | Rest], dec) ->
    case B - A of
        -1 -> is_safe([B | Rest], dec);
        -2 -> is_safe([B | Rest], dec);
        -3 -> is_safe([B | Rest], dec);
        _ -> false
    end.

any_safe(Level) -> any_safe([], Level).
any_safe(Agg, []) ->
    is_safe(Agg);
any_safe(Agg, [A|Rest]) ->
    is_safe(Agg ++ Rest) orelse any_safe(Agg ++ [A], Rest).

solve(Input) ->
    Levels = lists:map(fun utils:ints/1, utils:lines(Input)),
    { length(lists:filter(fun is_safe/1, Levels))
    , length(lists:filter(fun any_safe/1, Levels))
    }.
