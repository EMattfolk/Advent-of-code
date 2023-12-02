module Day16 (solution) where

import Data.Char (isDigit)
import qualified Data.List as List
import Lib

solution :: String -> (String, String)
solution input =
  let dist (x1, y1) (x2, y2) = abs (x1 - x2) + abs (y1 - y2)
      parsed :: [((Int, Int), (Int, Int))]
      parsed =
        input
          # lines
          <#> split (not . isDigit)
          <#> drop 1
          <#> map read
          <#> (\l -> ((l !! 0, l !! 1), (l !! 2, l !! 3)))

      ans1 = 0
      ans2 = 0
   in (show ans1, show ans2)
