-module(day25).

-export([solve/1]).

classify(Grid) ->
    {
        case hd(Grid) of
            {_, $#} -> lock;
            {_, $.} -> key
        end,
        [length([1 || {{X, _}, C} <- Grid, X =:= Col, C =:= $#]) || Col <- lists:seq(0, 4)]
    }.

fit({lock, Lock}, {key, Key}) ->
    fit_impl(Lock, Key).

fit_impl([L | Lock], [K | Key]) ->
    case L + K < 8 of
        true -> fit_impl(Lock, Key);
        false -> false
    end;
fit_impl([], []) ->
    true.

solve(Input) ->
    {Locks, Keys} = lists:partition(
        fun({T, _}) -> T =:= lock end,
        lists:map(fun classify/1, lists:map(fun utils:grid/1, utils:sections(Input)))
    ),
    % erlang:display({Locks, Keys}),
    % not 23
    {
        length([1 || L <- Locks, K <- Keys, fit(L, K)]),
        ~"*"
    }.
