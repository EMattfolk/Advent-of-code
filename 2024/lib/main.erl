-module(main).

-export([run/0, run/1]).

day_string(Day) ->
    iolist_to_binary(["day", string:pad(integer_to_binary(Day), 2, leading, ~"0")]).

read_input(Day) ->
    Filename = [~"input/", day_string(Day), ~".txt"],
    {ok, Res} = file:read_file(iolist_to_binary(Filename)),
    Res.

run(Day) ->
    Module = binary_to_atom(day_string(Day)),
    Module:solve(read_input(Day)).

run() ->
    {ok, Inputs} = file:list_dir(~"input"),
    Last = length(Inputs),
    Days = lists:seq(1, Last),
    Runner = self(),
    lists:foreach(
        fun(Day) ->
            spawn(fun() ->
                Start = os:system_time(microsecond),
                Runner ! {Day, catch run(Day), os:system_time(microsecond) - Start}
            end),
            io:format("Day ~2..0B:      ... ms - ..., ...\n", [Day])
        end,
        Days
    ),
    lists:foreach(
        fun(_) ->
            {{Part1, Part2}, Elapsed} =
                receive
                    {Day, Res, E} -> {Res, E}
                end,
            io:put_chars(lists:duplicate(Last - Day + 1, "\e[1A")),
            io:format("Day ~2..0B: ~8.3f ms - ~p, ~p\r", [Day, Elapsed / 1000, Part1, Part2]),
            io:put_chars(lists:duplicate(Last - Day + 1, "\e[1B"))
        end,
        Days
    ).
