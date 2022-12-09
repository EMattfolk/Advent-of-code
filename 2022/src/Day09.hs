module Day09 (solution) where

import qualified Data.List as List
import qualified Data.Set as Set
import Lib

data Dir = U | L | R | D deriving (Show)

charToDir :: Char -> Dir
charToDir 'U' = U
charToDir 'L' = L
charToDir 'R' = R
charToDir 'D' = D
charToDir _ = U

dirToOffset :: Dir -> (Int, Int)
dirToOffset U = (0, 1)
dirToOffset L = (-1, 0)
dirToOffset R = (1, 0)
dirToOffset D = (0, -1)

addOffset :: (Int, Int) -> (Int, Int) -> (Int, Int)
addOffset (x, y) (z, w) = (x + z, y + w)

follow :: (Int, Int) -> (Int, Int) -> (Int, Int)
follow (hx, hy) (tx, ty) =
  if abs (hx - tx) >= 2 && abs (hy - ty) >= 2
    then addOffset (hx, hy) (div (tx - hx) (abs (hx - tx)), div (ty - hy) (abs (hy - ty)))
    else
      if abs (hx - tx) >= 2
        then addOffset (hx, hy) (div (tx - hx) (abs (hx - tx)), 0)
        else
          if abs (hy - ty) >= 2
            then addOffset (hx, hy) (0, div (ty - hy) (abs (hy - ty)))
            else (tx, ty)

followList :: [(Int, Int)] -> [(Int, Int)]
followList [] = []
followList (k : []) = [k]
followList (a : b : t) = a : followList (follow a b : t)

solution :: String -> (String, String)
solution input =
  let parsed =
        input
          # lines
          # foldMap (\l -> List.replicate (read (drop 2 l)) (charToDir (l !! 0)))

      sim len =
        parsed
          # foldl
            ( \(rope, visited) dir ->
                let offset = dirToOffset dir
                    newHead = addOffset (rope !! 0) offset
                    newList = followList (newHead : tail rope)
                 in (newList, Set.insert (last newList) visited)
            )
            (List.replicate (len + 1) (0, 0), Set.singleton (0, 0))
          # snd
          # length

      ans1 = sim 1
      ans2 = sim 9
   in (show ans1, show ans2)
