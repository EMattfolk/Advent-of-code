-module(day08).

-export([ solve/1 ]).

-define(Size, 50).

pairs([X | Rest]) -> [{X, Y} || Y <- Rest] ++ pairs(Rest);
pairs([]) -> [].

place_antinodes(Beacons) -> lists:foldl(fun place_antinodes/2, #{}, maps:values(Beacons)).
place_antinodes(Nodes, Antinodes) -> 
    lists:foldl(
      fun ({A, B}, Acc) ->
              Diff = p:sub(B, A),
              P1 = p:sub(A, Diff),
              P2 = p:add(A, p:mul(Diff, 2)),
              sets:add_element(P1, sets:add_element(P2, Acc))
      end,
      Antinodes, pairs(Nodes)).

place_antinodes2(Beacons) -> sets:from_list(lists:foldl(fun place_antinodes2/2, [], maps:values(Beacons))).
place_antinodes2(Nodes, Antinodes) -> 
    lists:foldl(
      fun ({A, B}, Acc) ->
              Diff = p:sub(B, A),
              generate(A, Diff) ++ generate(A, p:neg(Diff)) ++ Acc
      end,
      Antinodes, pairs(Nodes)).

generate(P, Dir) -> 
    case in_bounds(P) of
        true -> [P | generate(p:add(P, Dir), Dir)];
        false -> []
    end.

in_bounds({X, Y}) -> 0 =< X andalso X < ?Size andalso 0 =< Y andalso Y < ?Size.

solve(Input) ->
    Lines = utils:lines(Input),
    Beacons = utils:group([ {C, {X, Y}} || {Y, L} <- lists:enumerate(0, Lines), {X, C} <- lists:enumerate(0, binary_to_list(L)), C /= $.]),
    { sets:size(sets:filter(fun in_bounds/1, place_antinodes(Beacons)))
    , sets:size(place_antinodes2(Beacons))
    }.
