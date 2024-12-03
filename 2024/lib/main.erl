-module(main).

-export([ run/0, read_input/1 ]).

day_string(Day) ->
    iolist_to_binary(["day", string:pad(integer_to_binary(Day), 2, leading, ~"0")]).

read_input(Day) -> 
    Filename = [~"input/", day_string(Day), ~".txt"],
    {ok, Res} = file:read_file(iolist_to_binary(Filename)),
    Res.


run() ->
    Days = [1, 2, 3],
    Runner = self(),
    lists:map(fun (Day) ->
                      Module = binary_to_atom(day_string(Day)),
                      spawn(fun() -> Runner ! {Day, Module:solve(read_input(Day))} end)
              end, Days),
    lists:map(fun (Day) ->
                      receive
                          {Day, Res} -> Res
                      end
              end, Days).
