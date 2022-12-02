module Day02 (solution) where

import Lib

data Game = Rock | Paper | Scissors

tr :: Char -> Game
tr c = case c of
  'A' -> Rock
  'B' -> Paper
  'C' -> Scissors
  'X' -> Rock
  'Y' -> Paper
  'Z' -> Scissors
  _ -> Rock

score :: (Game, Game) -> Int
score g = case g of
  (Rock, Rock) -> 3 + 1
  (Rock, Paper) -> 6 + 2
  (Rock, Scissors) -> 0 + 3
  (Paper, Rock) -> 0 + 1
  (Paper, Paper) -> 3 + 2
  (Paper, Scissors) -> 6 + 3
  (Scissors, Rock) -> 6 + 1
  (Scissors, Paper) -> 0 + 2
  (Scissors, Scissors) -> 3 + 3

changeOutcome :: (Game, Game) -> (Game, Game)
changeOutcome g = case g of
  (Rock, Rock) -> (Rock, Scissors)
  (Rock, Paper) -> (Rock, Rock)
  (Rock, Scissors) -> (Rock, Paper)
  (Paper, Rock) -> (Paper, Rock)
  (Paper, Paper) -> (Paper, Paper)
  (Paper, Scissors) -> (Paper, Scissors)
  (Scissors, Rock) -> (Scissors, Paper)
  (Scissors, Paper) -> (Scissors, Scissors)
  (Scissors, Scissors) -> (Scissors, Rock)

solution :: String -> (String, String)
solution input =
  let parse [] = []
      parse (x : xs) = (tr (x !! 0), tr (x !! 2)) : parse xs

      parsed :: [(Game, Game)]
      parsed =
        input
          # lines
          # parse

      ans1 =
        parsed
          <#> score
          # sum

      ans2 =
        parsed
          <#> changeOutcome
          <#> score
          # sum
   in (show ans1, show ans2)
