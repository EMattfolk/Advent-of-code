module Day12 (solution) where

import qualified Data.Map as Map
import qualified Data.Set as Set
import Lib

charToElevation :: Char -> Int
charToElevation 'S' = charToElevation 'a'
charToElevation 'E' = charToElevation 'z'
charToElevation c = fromEnum c - fromEnum 'a'

solution :: String -> (String, String)
solution input =
  let (tiles, start, end) =
        input
          # lines
          # zip [0 ..]
          <#> (\(y, l) -> zipWith (\x c -> ((x, y), c)) [0 ..] l)
          # concat
          # foldl
            ( \(t, s, e) (pos, c) ->
                let newTiles = t # Map.insert pos (charToElevation c)
                 in case c of
                      'S' -> (newTiles, pos, e)
                      'E' -> (newTiles, s, pos)
                      _ -> (newTiles, s, e)
            )
            (Map.empty, (-999, -999), (-999, -999))

      bfs :: ([(Int, Int)] -> Bool) -> (Int -> Int -> Bool) -> [(Int, Int)] -> Set.Set (Int, Int) -> Int
      bfs endCond neighborCond currentlyAt visited =
        let isValid pos = not (Set.member pos visited) && Map.member pos tiles
            neighbors (x, y) =
              [(x + 1, y), (x -1, y), (x, y + 1), (x, y -1)]
                # filter isValid
                # filter
                  ( \pos ->
                      Just True == do
                        curElev <- Map.lookup (x, y) tiles
                        elev <- Map.lookup pos tiles
                        pure (neighborCond elev curElev)
                  )
            frontierSet = currentlyAt # concatMap neighbors # Set.fromList
            frontier = Set.toList frontierSet
         in if endCond currentlyAt
              then 0
              else 1 + bfs endCond neighborCond frontier (Set.union visited frontierSet)

      ans1 = bfs (elem end) (\elev curElev -> elev <= curElev + 1) [(start)] Set.empty
      ans2 = bfs (elem (Just 0) . map (flip Map.lookup tiles)) (\elev curElev -> elev >= curElev - 1) [(end)] Set.empty
   in (show ans1, show ans2)
