-module(day22).

-export([solve/1]).

mix_and_prune(A, B) ->
    (A bxor B) band 16777215.

evolve(L = [{Secret, _} | _]) ->
    A = mix_and_prune(Secret, Secret bsl 6),
    B = mix_and_prune(A, A bsr 5),
    New = mix_and_prune(B, B bsl 11),
    [{New, (New rem 10) - (Secret rem 10)} | L].

sequence_values(Seen, [{_, Ad} | Rest = [{_, Bd}, {_, Cd}, {V, Dd} | _]]) ->
    Key = {Ad, Bd, Cd, Dd},
    sequence_values(
        case maps:is_key(Key, Seen) of
            true -> Seen;
            false -> Seen#{Key => V rem 10}
        end,
        Rest
    );
sequence_values(Seen, _) ->
    Seen.

solve(Input) ->
    Diffs = [
        utils:apply_n(2000, fun evolve/1, [{I, -99999999}])
     || I <- utils:ints(Input)
    ],
    {
        lists:sum([element(1, hd(D)) || D <- Diffs]),
        lists:max(
            maps:values(
                lists:foldl(
                    fun(M, Acc) -> maps:merge_with(fun(_, A, B) -> A + B end, M, Acc) end,
                    #{},
                    lists:map(fun(L) -> sequence_values(#{}, tl(lists:reverse(L))) end, Diffs)
                )
            )
        )
    }.
