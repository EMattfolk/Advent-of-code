-module(day13).

-export([solve/1]).

% (Ax Bx)(A) =:= (Px),
% (Ay By)(B) =:= (Py)

%       1         (By -Bx) (Px)
% Ax*By - Ay*Bx   (-Ay Ax) (Py)
%
%       1         (By * Px - Bx * Py)
% Ax*By - Ay*Bx   (-Ay * Px + Ax * Py)

% part1([]) ->
%     0;
% part1([Ax, Ay, Bx, By, Px, Py | Rest]) ->
%     case
%         [
%             A * 3 + B
%          || A <- lists:seq(0, 100),
%             B <- lists:seq(0, 100),
%             Ax * A + Bx * B =:= Px,
%             Ay * A + By * B =:= Py
%         ]
%     of
%         [] -> 0;
%         L -> lists:min(L)
%     end + part1(Rest).

inc([Ax, Ay, Bx, By, Px, Py | Rest]) ->
    [Ax, Ay, Bx, By, Px + 10000000000000, Py + 10000000000000 | inc(Rest)];
inc([]) ->
    [].

sum_solutions([]) ->
    0;
sum_solutions([Ax, Ay, Bx, By, Px, Py | Rest]) ->
    case
        {(By * Px - Bx * Py) rem (Ax * By - Ay * Bx), (-Ay * Px + Ax * Py) rem (Ax * By - Ay * Bx)}
    of
        {0, 0} ->
            trunc((By * Px - Bx * Py) / (Ax * By - Ay * Bx)) * 3 +
                trunc((-Ay * Px + Ax * Py) / (Ax * By - Ay * Bx));
        _ ->
            0
    end + sum_solutions(Rest).

solve(Input) ->
    Parsed = lists:map(fun binary_to_integer/1, string:lexemes(Input, "ButtonPrize AB:XY=+,\n")),
    {sum_solutions(Parsed), sum_solutions(inc(Parsed))}.
