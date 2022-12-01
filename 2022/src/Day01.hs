module Day01 (solution) where

import qualified Data.List as List
import Lib

solution :: String -> (String, String)
solution input =
  let parse [] = []
      parse xs =
        [List.takeWhile (/= "") xs]
          <> parse (List.drop 1 $ List.dropWhile (/= "") xs)

      parsed :: [[Int]]
      parsed =
        input
          # lines
          # parse
          <#> map read

      ans1 =
        parsed
          <#> sum
          # maximum

      ans2 =
        parsed
          <#> sum
          # List.sort
          # List.reverse
          # List.take 3
          # sum
   in (show ans1, show ans2)
