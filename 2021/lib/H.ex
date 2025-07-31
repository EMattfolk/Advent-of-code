defmodule H do
  def ints(input, delim \\ ~r/\s/) do
    input |> String.split(delim, trim: true) |> Enum.map(&String.to_integer/1)
  end
end
