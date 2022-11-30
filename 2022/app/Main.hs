module Main (main) where

import qualified Day01

main :: IO ()
main = print =<< (Day01.solution <$> readFile "input/day01.txt")
