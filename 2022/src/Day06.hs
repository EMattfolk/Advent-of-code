module Day06 (solution) where

import qualified Data.List as List
import Data.Maybe (fromMaybe)
import Lib

solution :: String -> (String, String)
solution input =
  let -- Assume list is infinite - go wroom
      windows n xs = take n xs : windows n (drop 1 xs)

      findNDistinct :: Int -> Int
      findNDistinct n =
        input
          # windows n
          # zip [n ..]
          # List.find (\(_, s) -> List.nub s == s)
          <#> fst
          # fromMaybe (-9999)

      ans1 = findNDistinct 4
      ans2 = findNDistinct 14
   in (show ans1, show ans2)
