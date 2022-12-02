module Main (main) where

import qualified Day01
import qualified Day02

main :: IO ()
main =
  print
    =<< sequence
      [ Day01.solution <$> readFile "input/day01.txt",
        Day02.solution <$> readFile "input/day02.txt"
      ]
