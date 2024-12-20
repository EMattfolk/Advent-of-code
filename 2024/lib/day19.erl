-module(day19).

-export([solve/1]).

is_possible(_, _, <<>>) ->
    1;
is_possible(T, Patterns, S) ->
    case ets:lookup(T, S) of
        [] ->
            R = lists:sum(
                lists:map(
                    fun(V) ->
                        <<Init:V/binary, Rest/binary>> = S,
                        case sets:is_element(Init, Patterns) of
                            true -> is_possible(T, Patterns, Rest);
                            false -> 0
                        end
                    end,
                    lists:seq(1, byte_size(S))
                )
            ),
            ets:insert(T, {S, R}),
            R;
        [{_, V}] ->
            V
    end.

solve(Input) ->
    [A, B] = utils:sections(Input),
    Patterns = sets:from_list(string:lexemes(A, ", "), [{version, 2}]),
    T = ets:new(day19, [set]),
    Possibilities = lists:filtermap(
        fun(S) ->
            case is_possible(T, Patterns, S) of
                0 -> false;
                P -> {true, P}
            end
        end,
        utils:lines(B)
    ),
    ets:delete(T),
    {
        length(Possibilities),
        lists:sum(Possibilities)
    }.
