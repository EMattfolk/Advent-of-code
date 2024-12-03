-module(day03).

-export([ solve/1 ]).

step([_, A, B], {Sum1, Sum2, Enabled}) ->
     ToAdd = binary_to_integer(A) * binary_to_integer(B),
     case Enabled of
         false -> {Sum1 + ToAdd, Sum2, Enabled};
         true -> {Sum1 + ToAdd, Sum2 + ToAdd, Enabled}
     end;
step([_, <<>>, <<>>, <<>>, _], {Sum1, Sum2, _}) ->
    {Sum1, Sum2, true};
step([_, <<>>, <<>>, _], {Sum1, Sum2, _}) ->
    {Sum1, Sum2, false}.

solve(Input) ->
    Regex = ~S"mul\((\d+),(\d+)\)|(don't\(\))|(do\(\))",
    {match, Matches} = re:run(Input, Regex, [global, {capture, all, binary}]),
    {P1, P2, _} = lists:foldl(fun step/2, {0, 0, true}, Matches),
    {P1, P2}.
