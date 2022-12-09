module Day08 (solution) where

import Data.Foldable (fold)
import qualified Data.List as List
import Data.Set (Set)
import qualified Data.Set as Set
import Lib

solution :: String -> (String, String)
solution input =
  let rows = lines input
      cols = lines input # List.transpose

      seen :: Bool -> Bool -> Set (Int, Int)
      seen transposed reversed =
        let pos x y = if transposed then (y, x) else (x, y)
            transposer = if transposed then List.transpose else id
            reverser = if reversed then reverse else id
         in rows
              # transposer
              # zip [0 ..]
              # foldl
                ( \acc (y, l) ->
                    l
                      # zip [0 ..]
                      # reverser
                      # foldl
                        ( \(cur, a) (x, c) ->
                            if cur < c
                              then (c, Set.insert (pos x y) a)
                              else (cur, a)
                        )
                        ('\0', acc)
                      # snd
                )
                Set.empty

      ans1 =
        length
          ( fold $ do
              transposed <- [True, False]
              reversed <- [True, False]
              [seen transposed reversed]
          )

      views l =
        let help _ _ [] = []
            help before current after =
              (before, current, after) :
              help (before <> [current]) (after !! 0) (drop 1 after)
         in help (take 1 l) (l !! 1) (drop 2 l)

      scenic view1 view2 =
        let score (before, current, after) =
              let b' = List.takeWhile (< current) after
                  a' = List.takeWhile (< current) (reverse before)
                  b = take (length b' + 1) after
                  a = take (length a' + 1) (reverse before)
               in length b * length a
         in score view1 * score view2

      rviews = rows <#> views
      cviews = cols <#> views

      ans2 = maximum $ do
        r <- [1 .. length rviews - 3]
        c <- [1 .. length cviews - 3]
        [scenic ((rviews !! r) !! (c - 1)) ((cviews !! c) !! (r - 1))]
   in (show ans1, show ans2)
