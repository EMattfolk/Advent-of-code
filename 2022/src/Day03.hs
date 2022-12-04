module Day03 (solution) where

import Data.Bifunctor (bimap)
import qualified Data.Set as Set
import Lib

toPriority :: Char -> Int
toPriority c =
  if 'a' <= c && c <= 'z'
    then fromEnum c - fromEnum 'a' + 1
    else
      if 'A' <= c && c <= 'Z'
        then fromEnum c - fromEnum 'A' + 27
        else -999999999

group3 :: [a] -> [[a]]
group3 (a : b : c : xs) = [a, b, c] : group3 xs
group3 _ = []

solution :: String -> (String, String)
solution input =
  let parse line = (take (div (length line) 2) line, drop (div (length line) 2) line)

      parsed :: [(String, String)]
      parsed =
        input
          # lines
          <#> parse

      ans1 =
        parsed
          <#> bimap Set.fromList Set.fromList
          <#> (\(a, b) -> Set.intersection a b)
          <#> Set.toList
          <#> (!! 0)
          <#> toPriority
          # sum

      ans2 =
        parsed
          <#> (\(a, b) -> Set.fromList (a <> b))
          # group3
          <#> (\g -> foldl Set.intersection (g !! 0) g)
          <#> Set.toList
          <#> (!! 0)
          <#> toPriority
          # sum
   in (show ans1, show ans2)
