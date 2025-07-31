defmodule Day01 do
  def solve(input) do
    parsed = input |> H.ints()

    ans1 =
      parsed
      |> Enum.zip(tl(parsed))
      |> Enum.filter(fn {a, b} -> b > a end)
      |> Enum.count()

    ans2 =
      Enum.zip([parsed, tl(parsed), tl(tl(parsed))])
      |> Enum.map(fn {a, b, c} -> a + b + c end)
      |> then(fn l -> Enum.zip(l, tl(l)) end)
      |> Enum.filter(fn {a, b} -> b > a end)
      |> Enum.count()

    {"#{ans1}", "#{ans2}"}
  end
end
