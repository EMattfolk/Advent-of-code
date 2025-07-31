defmodule Aoc do
  @moduledoc """
  Runner for all days.
  """

  def main() do
    IO.puts("")

    1..2
    |> Task.async_stream(fn day ->
      padded =
        case day < 10 do
          true -> "0#{day}"
          false -> "#{day}"
        end

      st = DateTime.utc_now()
      res = String.to_atom("Elixir.Day#{padded}").solve(File.read!("input/day#{padded}.txt"))
      nd = DateTime.utc_now()

      us =
        DateTime.diff(nd, st, :microsecond) |> Integer.to_string() |> String.pad_leading(7, " ")

      {padded, us, res}
    end)
    |> Stream.map(fn {:ok, {day, us, {part1, part2}}} ->
      IO.puts("Day #{day}: #{us} us - #{part1}, #{part2}")
    end)
    |> Stream.run()

    IO.puts("")
    IEx.dont_display_result()
  end

  def read do
    File.read!("input/day01.txt")
  end
end
