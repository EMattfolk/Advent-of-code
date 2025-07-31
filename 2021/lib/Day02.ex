defmodule Day02 do
  defp part1([], {depth, horiz}) do
    depth * horiz
  end

  defp part1([dir, amount | rest], {depth, horiz}) do
    part1(
      rest,
      case dir do
        "forward" -> {depth, horiz + String.to_integer(amount)}
        "down" -> {depth + String.to_integer(amount), horiz}
        "up" -> {depth - String.to_integer(amount), horiz}
      end
    )
  end

  defp part2([], {depth, horiz, _}) do
    depth * horiz
  end

  defp part2([dir, amount | rest], {depth, horiz, aim}) do
    part2(
      rest,
      case dir do
        "forward" ->
          {depth + aim * String.to_integer(amount), horiz + String.to_integer(amount), aim}

        "down" ->
          {depth, horiz, aim + String.to_integer(amount)}

        "up" ->
          {depth, horiz, aim - String.to_integer(amount)}
      end
    )
  end

  def solve(input) do
    parsed = input |> H.split()
    ans1 = part1(parsed, {0, 0})
    ans2 = part2(parsed, {0, 0, 0})
    {"#{ans1}", "#{ans2}"}
  end
end
