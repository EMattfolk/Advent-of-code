-module(day14).

-export([solve/1]).

-define(Width, 101).
-define(Height, 103).
-define(MiddleW, 50).
-define(MiddleH, 51).

quad([{X, Y} | Rest]) ->
    Q1 =
        case true of
            _ when X < ?MiddleW -> 1;
            _ when X > ?MiddleW -> 2;
            _ -> 0
        end,
    Q2 =
        case true of
            _ when Y < ?MiddleH -> 1;
            _ when Y > ?MiddleH -> 2;
            _ -> 0
        end,
    case Q1 =:= 0 orelse Q2 =:= 0 of
        true -> quad(Rest);
        false -> [{(Q1 - 1) + (Q2 - 1) * 2, 1} | quad(Rest)]
    end;
quad([]) ->
    [].

steps(Steps, [Px, Py, Vx, Vy | Rest]) ->
    X = utils:mod(Px + Vx * Steps, ?Width),
    Y = utils:mod(Py + Vy * Steps, ?Height),
    [{X, Y} | steps(Steps, Rest)];
steps(_, []) ->
    [].

solve(Input) ->
    Parsed = utils:ints(Input, "pv=,\n "),
    [A, B, C, D] = maps:values(
        maps:map(fun(_, V) -> length(V) end, utils:group(quad(steps(100, Parsed))))
    ),
    % lists:foreach(
    %     fun(Steps) ->
    %         Points = sets:from_list(steps(Steps, Parsed)),
    %         io:put_chars([$\n, integer_to_binary(Steps), $\n]),
    %         io:put_chars(
    %             lists:join($\n, [
    %                 [
    %                     case sets:is_element({X, Y}, Points) of
    %                         true -> $X;
    %                         false -> $\s
    %                     end
    %                  || X <- lists:seq(0, ?Width - 1)
    %                 ]
    %              || Y <- lists:seq(0, ?Height - 1)
    %             ]) ++ "\n"
    %         ),
    %         timer:sleep(10)
    %     end,
    %     lists:seq(6800, 7200)
    % ),
    {A * B * C * D, 7037}.
