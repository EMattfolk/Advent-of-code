-module(utils).

-export([
    ints/1,
    ints/2,
    lines/1,
    sections/1,
    grid/1,
    par/2,
    group/1,
    apply_n/3,
    mod/2,
    print_grid/1
]).

-doc """
Split a string into a list of integers.
""".
ints(S) -> ints(S, "|, \n").
ints(S, Sep) -> lists:map(fun binary_to_integer/1, string:lexemes(S, Sep)).
lines(S) -> string:lexemes(S, "\n").
sections(S) -> string:split(S, "\n\n", all).
grid(S) ->
    [
        {{X, Y}, C}
     || {Y, L} <- lists:enumerate(0, lines(S)), {X, C} <- lists:enumerate(0, binary_to_list(L))
    ].
par(F, L) ->
    Parent = self(),
    Ref = make_ref(),
    lists:foreach(fun(V) -> spawn(fun() -> Parent ! {Ref, F(V)} end) end, L),
    lists:map(
        fun(_) ->
            receive
                {Ref, V} -> V
            end
        end,
        L
    ).

group([]) -> #{};
group([{A, B} | Rest]) -> maps:update_with(A, fun(Acc) -> [B | Acc] end, [B], group(Rest)).

apply_n(0, _, V) -> V;
apply_n(N, F, V) when is_integer(N), N > 0 -> apply_n(N - 1, F, F(V)).

mod(I, M) -> (M + (I rem M)) rem M.

print_grid(Grid) ->
    Width = lists:max([X || {X, _} <- maps:keys(Grid)]),
    Height = lists:max([Y || {_, Y} <- maps:keys(Grid)]),
    io:put_chars(
        lists:join($\n, [
            [maps:get({X, Y}, Grid, $\s) || X <- lists:seq(0, Width)]
         || Y <- lists:seq(0, Height)
        ]) ++ "\n"
    ).
