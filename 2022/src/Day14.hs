module Day14 (solution) where

import qualified Data.Set as Set
import Lib

addPos :: (Int, Int) -> (Int, Int) -> (Int, Int)
addPos (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

expand :: [(Int, Int)] -> [(Int, Int)]
expand [] = []
expand [_] = []
expand (from : to : xs) =
  let dir (x1, y1) (x2, y2) =
        if x2 - x1 /= 0
          then (div (x2 - x1) (abs (x2 - x1)), 0)
          else (0, div (y2 - y1) (abs (y2 - y1)))
      go _ f t | f == t = [t]
      go d f t = f : go d (addPos f d) t
   in go (dir from to) from to <> expand (to : xs)

solution :: String -> (String, String)
solution input =
  let parsed :: [[(Int, Int)]]
      parsed =
        input
          # lines
          <#> split (\c -> c == ' ' || c == '-' || c == '>')
          <#> map ("(" <>)
          <#> map (<> ")")
          <#> map read

      tiles = parsed # concatMap expand # Set.fromList

      start = (500, 0)
      end = tiles # Set.toList <#> snd # maximum

      simulate grain t =
        let down = addPos grain (0, 1)
            dleft = addPos grain (-1, 1)
            dright = addPos grain (1, 1)
         in case Set.member down t of
              True -> case (Set.member dleft t, Set.member dright t) of
                (True, True) -> simulate start (Set.insert grain t)
                (True, False) -> simulate dright t
                (False, _) -> simulate dleft t
              False ->
                if snd grain > end
                  then t
                  else simulate down t

      newTiles = simulate start tiles

      simulate2 grain t =
        let down = addPos grain (0, 1)
            dleft = addPos grain (-1, 1)
            dright = addPos grain (1, 1)
         in case Set.member down t of
              True -> case (Set.member dleft t, Set.member dright t) of
                (True, True) ->
                  if grain == start
                    then Set.insert grain t
                    else simulate2 start (Set.insert grain t)
                (True, False) -> simulate2 dright t
                (False, _) -> simulate2 dleft t
              False -> simulate2 down t

      startx = addPos start (- end -2, end + 2)
      endx = addPos start (end + 2, end + 2)

      tiles2 = Set.union tiles (Set.fromList (expand [startx, endx]))
      newTiles2 = simulate2 start tiles2

      ans1 = length newTiles - length tiles
      ans2 = length newTiles2 - length tiles2
   in (show ans1, show ans2)
