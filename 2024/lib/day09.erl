-module(day09).

-export([ solve/1 ]).

char_to_int(C) -> C - $0.

mark(Input) -> mark(0, binary_to_list(Input)).
mark(Id, [C, $\n]) -> [{file, char_to_int(C), Id}];
mark(Id, [C, E | Rest]) -> [{file, char_to_int(C), Id}, {space, char_to_int(E)} | mark(Id + 1, Rest)].

expand([{file, Size, Id} | Rest]) -> lists:duplicate(Size, Id) ++ expand(Rest);
expand([{space, Size} | Rest]) -> lists:duplicate(Size, empty) ++ expand(Rest);
expand([]) -> [].

compact(L) -> compact_impl(queue:from_list(L)).
compact_impl(Q) ->
    case queue:is_empty(Q) of
        true -> [];
        false ->
            case {queue:get(Q), queue:get_r(Q)} of
                {empty, empty} -> compact_impl(queue:drop_r(Q));
                {empty, V} -> [V | compact_impl(queue:drop(queue:drop_r(Q)))];
                {V, empty} -> [V | compact_impl(queue:drop(queue:drop_r(Q)))];
                {V, _} -> [V | compact_impl(queue:drop(Q))]
            end
    end.

compact2(L) -> remove_duplicates(#{}, compact2(L, lists:reverse(L))).
compact2([File = {file, _, _} | Rest], Files) ->
    [File | compact2(Rest, Files)];
compact2(L, [File = {file, _, _} | Rest]) ->
    compact2(insert(L, File), Rest);
compact2(L, [{space, _} | Rest]) ->
    compact2(L, Rest);
compact2(L, []) ->
    L.

insert([File = {file, _, _} | Rest], File) ->
    [File | Rest];
insert([Space = {space, SpaceSize} | Rest], File = {file, FileSize, _}) ->
    case SpaceSize < FileSize of
        true -> [Space | insert(Rest, File)];
        false ->
            case SpaceSize =:= FileSize of
                true -> [File | Rest];
                false -> [File, {space, SpaceSize - FileSize} | Rest]
            end
    end;
insert([F | Rest], File) ->
    [F | insert(Rest, File)].

remove_duplicates(Seen, [File = {file, Size, Id} | Rest]) ->
    case sets:is_element(Id, Seen) of
        true -> [{space, Size} | remove_duplicates(Seen, Rest)];
        false -> [File | remove_duplicates(sets:add_element(Id, Seen), Rest)]
    end;
remove_duplicates(Seen, [Space = {space, _} | Rest]) -> [Space | remove_duplicates(Seen, Rest)];
remove_duplicates(_, []) -> [].


solve(Input) ->
    Marked = mark(Input),
    { lists:sum([I * V || {I, V} <- lists:enumerate(0, compact(expand(Marked)))])
    , lists:sum([I * V || {I, V} <- lists:enumerate(0, expand(compact2(Marked))), V =/= empty])
    }.
