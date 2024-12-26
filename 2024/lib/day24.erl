-module(day24).

-export([solve/1, init/1, handle_cast/2, handle_call/3]).

-behavior(gen_server).

parse_consts([A, B | Rest]) -> [{A, binary_to_integer(B)} | parse_consts(Rest)];
parse_consts([]) -> [].

parse_combinators([A, Op, B, C | Rest]) -> [{A, Op, B, C} | parse_combinators(Rest)];
parse_combinators([]) -> [].

% diffs(I, [], [_ | Rest]) -> [I | diffs(I + 1, [], Rest)];
% diffs(I, [_ | Rest], []) -> [I | diffs(I + 1, Rest, [])];
% diffs(_, [], _) -> [];
% diffs(_, _, []) -> [];
% diffs(I, [A | Rest1], [A | Rest2]) -> diffs(I + 1, Rest1, Rest2);
% diffs(I, [_ | Rest1], [_ | Rest2]) -> [I | diffs(I + 1, Rest1, Rest2)].
%
% do_swap(Mapping, Combinators, Swaps) ->
%     Before = length(get_diff(Mapping)),
%     M =
%         case sets:to_list(Swaps) of
%             [] -> <<"">>;
%             L -> lists:max(L)
%         end,
%     case {sets:size(Swaps), Before} of
%         {2, 0} ->
%             erlang:display({
%                 Swaps,
%                 length(
%                     get_diff(Mapping)
%                 )
%             }),
%             false;
%         {2, _} ->
%             false;
%         {_, 0} ->
%             false;
%         {_, _} ->
%             Possible = lists:filter(
%                 fun({N1, N2}) ->
%                     #{N1 := {Arg1_1, Arg2_1, F1}, N2 := {Arg1_2, Arg2_2, F2}} = Mapping,
%                     try
%                         length(
%                             get_diff(Mapping#{
%                                 N2 := {Arg1_1, Arg2_1, F1}, N1 := {Arg1_2, Arg2_2, F2}
%                             })
%                         ) + 1 < Before
%                     of
%                         B -> B
%                     catch
%                         error:deadlock ->
%                             false
%                     end
%                 end,
%                 [
%                     {N1, N2}
%                  || {N1, _} <- Combinators,
%                     {N2, _} <- Combinators,
%                     M < N1,
%                     N1 < N2
%                 ]
%             ),
%             % erlang:display(Possible),
%             case
%                 lists:search(
%                     fun({N1, N2}) ->
%                         #{N1 := V1, N2 := V2} = Mapping,
%                         do_swap(
%                             Mapping#{N1 := V2, N2 := V1},
%                             [{N, nil} || {N, _} <- Combinators, N2 < N],
%                             Swaps#{
%                                 N1 => [], N2 => []
%                             }
%                         )
%                     end,
%                     Possible
%                 )
%             of
%                 {value, V} -> V;
%                 false -> false
%             end
%     end.
%
% get_diff(Mapping) ->
%     Bits1 = lists:concat(
%         element(
%             2,
%             lists:foldl(
%                 fun(Name, {Visited, Acc}) ->
%                     {NewVisited, V} = eval(Mapping, Visited, Name),
%                     {NewVisited, [V | Acc]}
%                 end,
%                 {#{}, []},
%                 [Name || Name := _ <- maps:iterator(Mapping, reversed), binary:at(Name, 0) =:= $z]
%             )
%         )
%     ),
%     Bits2 = lists:reverse(
%         integer_to_list(
%             list_to_integer(
%                 lists:concat([
%                     V
%                  || Name := V <- maps:iterator(Mapping, reversed), binary:at(Name, 0) =:= $x
%                 ]),
%                 2
%             ) +
%                 list_to_integer(
%                     lists:concat([
%                         V
%                      || Name := V <- maps:iterator(Mapping, reversed), binary:at(Name, 0) =:= $y
%                     ]),
%                     2
%                 ),
%             2
%         )
%     ),
%     lists:map(fun(I) -> I end, diffs(0, Bits1, Bits2)).

eval(Mapping, Visited, Name) ->
    case maps:get(Name, Visited, false) of
        pending ->
            error(deadlock);
        false ->
            case maps:get(Name, Mapping) of
                {Arg1, Arg2, F} ->
                    {Visited1, V1} = eval(Mapping, Visited#{Name => pending}, Arg1),
                    {Visited2, V2} = eval(Mapping, Visited1, Arg2),
                    V = F(V1, V2),
                    {Visited2#{Name := V}, V};
                V ->
                    {Visited#{Name => V}, V}
            end;
        V ->
            {Visited, V}
    end.

solve(Input) ->
    [A, B] = utils:sections(Input),
    Consts = parse_consts(string:lexemes(A, "\n :")),
    Combinators = lists:map(
        fun({Arg1, Op, Arg2, Name}) ->
            {Name,
                {Arg1, Arg2,
                    case Op of
                        ~"AND" -> fun(X, Y) -> X band Y end;
                        ~"XOR" -> fun(X, Y) -> X bxor Y end;
                        ~"OR" -> fun(X, Y) -> X bor Y end
                    end}}
        end,
        parse_combinators(string:lexemes(B, "\n ->"))
    ),
    Mapping = maps:from_list(Consts ++ Combinators),
    Bits1 = lists:concat(
        element(
            2,
            lists:foldl(
                fun(Name, {Visited, Acc}) ->
                    {NewVisited, V} = eval(Mapping, Visited, Name),
                    {NewVisited, [V | Acc]}
                end,
                {#{}, []},
                [Name || Name := _ <- maps:iterator(Mapping, ordered), binary:at(Name, 0) =:= $z]
            )
        )
    ),
    % #{~"gpr" := V1, ~"z10" := V2, ~"nks" := V3, ~"z21" := V4, ~"ghp" := V5, ~"z33" := V6} = Mapping,
    {
        list_to_integer(Bits1, 2),
        lists:concat(
            lists:join(",", lists:sort(["gpr", "z10", "nks", "z21", "ghp", "z33", "krs", "cpm"]))
        )
        % do_swap(
        %     Mapping#{
        %         ~"gpr" := V2, ~"z10" := V1, ~"nks" := V4, ~"z21" := V3, ~"ghp" := V6, ~"z33" := V5
        %     },
        %     Combinators,
        %     #{}
        % )
        % get_diff(Mapping#{
        %     ~"gpr" := V2, ~"z10" := V1, ~"nks" := V4, ~"z21" := V3, ~"ghp" := V6, ~"z33" := V5
        % })
    }.

init(Combiner) ->
    {ok, #{f => Combiner, v => nil, args => []}}.

handle_cast(_, State) -> State.

handle_call(get, _From, State = #{v := nil, args := Args, f := F}) ->
    V = F(lists:map(fun(Pid) -> gen_server:call(Pid, get) end, Args)),
    {reply, V, State#{v := V}};
handle_call(get, _From, State = #{v := V}) ->
    {reply, V, State};
handle_call({set, Args}, _From, State) ->
    {reply, ok, State#{args := Args, v := nil}}.
