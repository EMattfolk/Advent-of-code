-module(main).

-export([ run/0, read_input/1 ]).

read_input(Day) -> 
    Filename = [~"input/day", string:pad(integer_to_binary(Day), 2, leading, ~"0"), ~".txt"],
    {ok, Res} = file:read_file(iolist_to_binary(Filename)),
    Res.


run() ->
    [ day01:solve(read_input(1))
    , day02:solve(read_input(2))
    ].
