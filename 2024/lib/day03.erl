-module(day03).

-export([ solve/1 ]).

extract_int(Input, P, L) -> binary_to_integer(binary:part(Input, P, L)).

step(Input, [_, {Ap, Al}, {Bp, Bl}], {Sum1, Sum2, Enabled}) ->
     ToAdd = extract_int(Input, Ap, Al) * extract_int(Input, Bp, Bl),
     case Enabled of
         false -> {Sum1 + ToAdd, Sum2, Enabled};
         true -> {Sum1 + ToAdd, Sum2 + ToAdd, Enabled}
     end;
step(_, [_, {-1,0}, {-1,0}, {-1,0}, _], {Sum1, Sum2, _}) ->
    {Sum1, Sum2, true};
step(_, [_, {-1,0}, {-1,0}, _], {Sum1, Sum2, _}) ->
    {Sum1, Sum2, false}.

solve(Input) ->
    Regex = ~S"mul\((\d+),(\d+)\)|(don't\(\))|(do\(\))",
    {match, Matches} = re:run(Input, Regex, [global]),
    {P1, P2, _} =
        lists:foldl(fun (Match, Acc) -> step(Input, Match, Acc) end
                   , {0, 0, true}
                   , Matches),
    { P1
    , P2
    }.
