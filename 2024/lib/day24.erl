-module(day24).

-export([solve/1, init/1, handle_cast/2, handle_call/3]).

-behavior(gen_server).

parse_consts([A, B | Rest]) -> [{A, binary_to_integer(B)} | parse_consts(Rest)];
parse_consts([]) -> [].

parse_combinators([A, Op, B, C | Rest]) -> [{A, Op, B, C} | parse_combinators(Rest)];
parse_combinators([]) -> [].

diffs(_, [], _) -> [];
diffs(_, _, []) -> [];
diffs(I, [A | Rest1], [A | Rest2]) -> diffs(I + 1, Rest1, Rest2);
diffs(I, [_ | Rest1], [_ | Rest2]) -> [I | diffs(I + 1, Rest1, Rest2)].

do_swap(Mapping, Combinators) ->
    Before = length(get_diff(Mapping, Combinators)),
    Pids = [{N, P} || N := {_, _, P} <- Combinators],
    {value, Swapped} = lists:search(
        fun({{N1, P1}, {N2, P2}}) ->
            #{N1 := {Arg1_1, Arg2_1, P1}, N2 := {Arg1_2, Arg2_2, P2}} = Combinators,
            length(
                get_diff(Mapping, Combinators#{
                    N1 := {Arg1_1, Arg2_1, P2}, N2 := {Arg1_2, Arg2_2, P1}
                })
            ) < Before
        end,
        [{{N1, P1}, {N2, P2}} || {N1, P1} <- Pids, {N2, P2} <- Pids, P1 < P2]
    ),
    Swapped.

has_cycles(Mapping, Combinators, Visited, P) ->
    sets:is_element(P, Visited).

get_diff(Mapping, Combinators) ->
    maps:foreach(
        fun(_, {Arg1, Arg2, Pid}) ->
            gen_server:call(Pid, {set, [maps:get(Arg1, Mapping), maps:get(Arg2, Mapping)]})
        end,
        Combinators
    ),
    Bits1 = lists:concat([
        gen_server:call(Pid, get)
     || Name := Pid <- maps:iterator(Mapping, ordered), binary:at(Name, 0) =:= $z
    ]),
    Bits2 = lists:reverse(
        integer_to_list(
            list_to_integer(
                lists:concat([
                    gen_server:call(Pid, get)
                 || Name := Pid <- maps:iterator(Mapping, reversed), binary:at(Name, 0) =:= $x
                ]),
                2
            ) +
                list_to_integer(
                    lists:concat([
                        gen_server:call(Pid, get)
                     || Name := Pid <- maps:iterator(Mapping, reversed), binary:at(Name, 0) =:= $y
                    ]),
                    2
                ),
            2
        )
    ),
    lists:map(fun(I) -> I end, diffs(0, Bits1, Bits2)).

solve(Input) ->
    [A, B] = utils:sections(Input),
    Consts = lists:map(
        fun({Name, V}) ->
            {ok, Pid} = gen_server:start_link(?MODULE, fun([]) -> V end, []),
            {Name, Pid}
        end,
        parse_consts(string:lexemes(A, "\n :"))
    ),
    Combinators = lists:map(
        fun({Arg1, Op, Arg2, Name}) ->
            {ok, Pid} = gen_server:start_link(
                ?MODULE,
                case Op of
                    ~"AND" -> fun([X, Y]) -> X band Y end;
                    ~"XOR" -> fun([X, Y]) -> X bxor Y end;
                    ~"OR" -> fun([X, Y]) -> X bor Y end
                end,
                []
            ),
            {Name, {Arg1, Arg2, Pid}}
        end,
        parse_combinators(string:lexemes(B, "\n ->"))
    ),
    Mapping = maps:from_list(
        Consts ++
            lists:map(
                fun({Name, {_, _, Pid}}) ->
                    {Name, Pid}
                end,
                Combinators
            )
    ),
    lists:foreach(
        fun({_, {Arg1, Arg2, Pid}}) ->
            gen_server:call(Pid, {set, [maps:get(Arg1, Mapping), maps:get(Arg2, Mapping)]})
        end,
        Combinators
    ),
    Bits1 = lists:concat([
        gen_server:call(Pid, get)
     || Name := Pid <- maps:iterator(Mapping, ordered), binary:at(Name, 0) =:= $z
    ]),
    %do_swap(Mapping, maps:from_list(Combinators)),
    P2 = 1,
    maps:foreach(fun(_, Pid) -> gen_server:stop(Pid) end, Mapping),
    {
        list_to_integer(lists:reverse(Bits1), 2),
        P2
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
