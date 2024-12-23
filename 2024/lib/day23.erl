-module(day23).

-export([solve/1]).

split([A, B | Rest]) -> [{A, B} | split(Rest)];
split([]) -> [].

add_one(Graph, F, Groups) ->
    #{
        lists:sort([New | Keys]) => sets:intersection(Possible, maps:get(New, Graph))
     || Keys := Possible <- Groups,
        New <-
            case
                F(
                    fun(P) -> sets:is_subset(sets:from_list(Keys), maps:get(P, Graph)) end,
                    sets:to_list(Possible)
                )
            of
                {value, V} -> [V];
                false -> [];
                L -> L
            end
    }.

until(P, F, V) ->
    case P(V) of
        true -> V;
        false -> until(P, F, F(V))
    end.

solve(Input) ->
    Parsed = split(string:lexemes(Input, "\n-")),
    Graph = maps:map(
        fun(_, V) -> sets:from_list(V, [{version, 2}]) end,
        utils:group(Parsed ++ [{B, A} || {A, B} <- Parsed])
    ),
    Init = #{[K] => P || K := P <- Graph},
    {
        length([
            1
         || K := _ <- add_one(
                Graph,
                fun lists:filter/2,
                add_one(Graph, fun lists:filter/2, Init)
            ),
            lists:any(fun(B) -> binary:at(B, 0) =:= $t end, K)
        ]),
        unicode:characters_to_list(
            lists:join(
                $,,
                hd(
                    sets:to_list(
                        until(
                            fun(S) -> sets:size(S) =:= 1 end,
                            fun(S) -> add_one(Graph, fun lists:search/2, S) end,
                            Init
                        )
                    )
                )
            )
        )
    }.

% length([
%     1
%  || K1 := V1 <- Graph,
%     K2 := V2 <- Graph,
%     K3 := V3 <- Graph,
%     K1 < K2,
%     K2 < K3,
%     sets:is_element(K1, V2),
%     sets:is_element(K1, V3),
%     sets:is_element(K2, V1),
%     sets:is_element(K2, V3),
%     sets:is_element(K3, V1),
%     sets:is_element(K3, V2),
%     binary:at(K1, 0) =:= $t orelse
%         binary:at(K2, 0) =:= $t orelse
%         binary:at(K3, 0) =:= $t
% ]),
