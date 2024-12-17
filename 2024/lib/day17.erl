-module(day17).

-export([solve/1]).

combo(0, _) -> 0;
combo(1, _) -> 1;
combo(2, _) -> 2;
combo(3, _) -> 3;
combo(4, #{a := A}) -> A;
combo(5, #{b := B}) -> B;
combo(6, #{c := C}) -> C.

adv(State = #{a := A, i := I}) ->
    O = combo(maps:get(I + 1, State), State),
    State#{a := A bsr O, i := I + 2}.

bxl(State = #{b := B, i := I}) ->
    O = maps:get(I + 1, State),
    State#{b := B bxor O, i := I + 2}.

bst(State = #{i := I}) ->
    O = combo(maps:get(I + 1, State), State),
    State#{b := O band 7, i := I + 2}.

jnz(State = #{a := 0, i := I}) ->
    State#{i := I + 2};
jnz(State = #{i := I}) ->
    O = maps:get(I + 1, State),
    State#{i := O}.

bxc(State = #{b := B, c := C, i := I}) ->
    State#{b := B bxor C, i := I + 2}.

out(State = #{i := I, out := Out}) ->
    O = combo(maps:get(I + 1, State), State),
    State#{out := [O band 7 | Out], i := I + 2}.

bdv(State = #{a := A, i := I}) ->
    O = combo(maps:get(I + 1, State), State),
    State#{b := A bsr O, i := I + 2}.

cdv(State = #{a := A, i := I}) ->
    O = combo(maps:get(I + 1, State), State),
    State#{c := A bsr O, i := I + 2}.

loop(State = #{i := I}) ->
    erlang:display(State),
    case maps:get(I, State, halt) of
        0 -> loop(adv(State));
        1 -> loop(bxl(State));
        2 -> loop(bst(State));
        3 -> loop(jnz(State));
        4 -> loop(bxc(State));
        5 -> loop(out(State));
        6 -> loop(bdv(State));
        7 -> loop(cdv(State));
        halt -> State
    end.

solve(Input) ->
    [A, B, C | Program] = utils:ints(Input, "Registr ABC:\nPoam,"),
    State = #{Key => Value || {Key, Value} <- lists:enumerate(0, Program)}#{
        a => A, b => B, c => C, i => 0, out => []
    },
    {lists:reverse(maps:get(out, loop(State))), 0}.
