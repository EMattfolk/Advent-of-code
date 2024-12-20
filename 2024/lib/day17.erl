-module(day17).

-export([solve/1]).

% combo(0, _) -> 0;
% combo(1, _) -> 1;
% combo(2, _) -> 2;
% combo(3, _) -> 3;
% combo(4, #{a := A}) -> A;
% combo(5, #{b := B}) -> B;
% combo(6, #{c := C}) -> C.
%
% adv(State = #{a := A, i := I}) ->
%     O = combo(maps:get(I + 1, State), State),
%     State#{a := A bsr O, i := I + 2}.
%
% bxl(State = #{b := B, i := I}) ->
%     O = maps:get(I + 1, State),
%     State#{b := B bxor O, i := I + 2}.
%
% bst(State = #{i := I}) ->
%     O = combo(maps:get(I + 1, State), State),
%     State#{b := O band 7, i := I + 2}.
%
% jnz(State = #{a := 0, i := I}) ->
%     State#{i := I + 2};
% jnz(State = #{i := I}) ->
%     O = maps:get(I + 1, State),
%     State#{i := O}.
%
% bxc(State = #{b := B, c := C, i := I}) ->
%     State#{b := B bxor C, i := I + 2}.
%
% out(State = #{i := I, out := Out}) ->
%     O = combo(maps:get(I + 1, State), State),
%     % erlang:display(integer_to_binary(O, 2)),
%     State#{out := [O band 7 | Out], i := I + 2}.
%
% bdv(State = #{a := A, i := I}) ->
%     O = combo(maps:get(I + 1, State), State),
%     State#{b := A bsr O, i := I + 2}.
%
% cdv(State = #{a := A, i := I}) ->
%     O = combo(maps:get(I + 1, State), State),
%     State#{c := A bsr O, i := I + 2}.
%
% loop(State = #{i := I}) ->
%     case maps:get(I, State, halt) of
%         0 -> loop(adv(State));
%         1 -> loop(bxl(State));
%         2 -> loop(bst(State));
%         3 -> loop(jnz(State));
%         4 -> loop(bxc(State));
%         5 -> loop(out(State));
%         6 -> loop(bdv(State));
%         7 -> loop(cdv(State));
%         halt -> State
%     end.

loop2(0) ->
    [];
loop2(A) ->
    [(A bxor (A bsr ((A bxor 3) band 7)) bxor 6) band 7 | loop2(A bsr 3)].

% B <- A & 111
% B <- B xor 11
% C <- A >> B
% B <- B xor C
% A <- A >> 3
% B <- B xor 101
% Out <- B & 111
% if A /= 0 start over

% B <- (A & 111) xor 11
% C <- A >> B
% A <- A >> 3
% Out <- (B xor C xor 101) & 111
% if A /= 0 start over

try_all(_, Got, _, <<>>) ->
    binary_to_integer(Got, 2);
try_all(Program, Got, NeedsMatch, <<_, _, _, ToDecide/binary>>) ->
    lists:foldl(
        fun(B, Acc) ->
            case Acc of
                false ->
                    Cur = loop2(binary_to_integer(<<Got/binary, B/binary, ToDecide/binary>>, 2)),
                    case
                        lists:sublist(lists:reverse(Cur), NeedsMatch) =:=
                            lists:sublist(lists:reverse(Program), NeedsMatch)
                    of
                        true ->
                            try_all(Program, <<Got/binary, B/binary>>, NeedsMatch + 1, ToDecide);
                        false ->
                            false
                    end;
                _ ->
                    Acc
            end
        end,
        false,
        [~"000", ~"001", ~"010", ~"011", ~"100", ~"101", ~"110", ~"111"]
    ).

solve(Input) ->
    [A, _B, _C | Program] = utils:ints(Input, "Registr ABC:\nPoam,"),
    %State = #{Key => Value || {Key, Value} <- lists:enumerate(0, Program)}#{
    %    a => A, b => B, c => C, i => 0, out => []
    %},
    {
        loop2(A),
        try_all(Program, <<>>, 1, ~"000000000000000000000000000000000000000000000000")
    }.
