-module(main).

-export([ run/0, read_input/1 ]).

day_string(Day) ->
    iolist_to_binary(["day", string:pad(integer_to_binary(Day), 2, leading, ~"0")]).

read_input(Day) -> 
    Filename = [~"input/", day_string(Day), ~".txt"],
    {ok, Res} = file:read_file(iolist_to_binary(Filename)),
    Res.


run() ->
    {ok, Inputs} = file:list_dir(~"input"),
    Days = lists:seq(1, length(Inputs)),
    Runner = self(),
    lists:map(fun (Day) ->
                      Module = binary_to_atom(day_string(Day)),
                      spawn(fun() ->
                                    Start = os:system_time(microsecond),
                                    Runner ! {Day, catch Module:solve(read_input(Day)), os:system_time(microsecond) - Start}
                            end)
              end, Days),
    lists:foreach(fun (Day) ->
                      {{Part1, Part2}, Elapsed} =
                          receive
                              {D, Res, E} when D == Day -> {Res, E}
                          end,
                      io:format("Day ~2..0B: ~8.3f ms - ~p, ~p\n", [Day, Elapsed / 1000, Part1, Part2 ])
              end, Days).
