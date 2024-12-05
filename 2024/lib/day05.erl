-module(day05).

-export([ solve/1 ]).

group([]) -> #{};
group([[A, B] | Rest]) ->
    maps:update_with(B, fun (Acc) -> [A | Acc] end, [A], group(Rest)).

topo_sort(Pages, Deps) ->
    PageSet = sets:from_list(Pages),
    {Acc, _} =
        sets:fold(
          fun (Dep, {Acc, Seen}) ->
              topo_sort(PageSet, Deps, Dep, Acc, Seen)
          end,
          {[], #{}},
          PageSet
        ),
    lists:reverse(Acc).
topo_sort(PageSet, Deps, ToAdd, Acc, Seen) ->
    case sets:is_element(ToAdd, Seen) orelse not sets:is_element(ToAdd, PageSet) of
        true -> {Acc, Seen};
        false ->
            {Acc2, Seen2} =
                lists:foldl(
                  fun (Dep, {Acc2, Seen2}) ->
                          topo_sort(PageSet, Deps, Dep, Acc2, Seen2)
                  end,
                  {Acc, sets:add_element(ToAdd, Seen)},
                  maps:get(ToAdd, Deps)
                ),
            {[ToAdd|Acc2], Seen2}
    end.

middle(L) -> lists:nth(ceil(length(L) / 2), L).

solve(Input) ->
    [DepsInput, Orderings] = [[utils:ints(L) || L <- utils:lines(S)] || S <- utils:sections(Input)],
    Deps = group(DepsInput),
    OrdAndTopo = [{O, topo_sort(O, Deps)} || O <- Orderings],
    {Ok, NotOk} = lists:partition(fun ({O, T}) -> T =:= O end, OrdAndTopo),
    { lists:sum(lists:map(fun ({O, _}) -> middle(O) end, Ok))
    , lists:sum(lists:map(fun ({_, T}) -> middle(T) end, NotOk))
    }.
