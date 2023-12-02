module Day15 (solution) where

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

      -- beacons = parsed <#> snd # Set.fromList # Set.toList

      sensors = parsed <#> (\(s, b) -> (s, dist s b))

      mergeSpans [] = []
      mergeSpans (a : []) = [a]
      mergeSpans ((a1, a2) : (b1, b2) : xs) =
        if a2 + 1 >= b1
          then mergeSpans ((a1, max a2 b2) : xs)
          else (a1, a2) : mergeSpans ((b1, b2) : xs)

      spans y =
        sensors
          # concatMap
            ( \((sx, sy), r) ->
                let ydiff = abs (sy - y)
                 in if ydiff > r
                      then []
                      else [(sx - (r - ydiff), (sx + (r - ydiff)))]
            )
          # List.sort

      ans1 =
        spans 2000000
          # mergeSpans
          <#> (\(a, b) -> 1 - 1 {- There is a beacon at y=2000000 -} + b - a)
          # sum

      -- [(957210,[(-493335,2203211),(2203213,4716458)]),(3398893,[(-1628590,2889604),(2889606,4238366)])]
      ans2 = "Redacted"
   in -- [0 .. 4000000]
      --   <#> spans
      --   <#> mergeSpans
      --   # zip [0 ..]
      --   # filter (\(_, s) -> length s == 2)
      --   # filter (\(_, [(_, a), (b, _)]) -> b - a == 2)
      (show ans1, show ans2)
