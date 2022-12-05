module Day05 (solution) where

import qualified Data.List as List
import qualified Data.Map as Map
import Data.Maybe (fromMaybe)
import Lib

solution :: String -> (String, String)
solution input =
  let readStack :: [String] -> Int -> [Char]
      readStack [] _ = []
      readStack (x : xs) i = case x !! i of
        ' ' -> readStack xs i
        c -> c : readStack xs i

      stacks :: [String]
      stacks =
        input
          # lines
          # List.takeWhile ((/=) " 1" . List.take 2)

      instr :: [(Int, Int, Int)]
      instr =
        input
          # lines
          # List.dropWhile (/= "")
          # List.drop 1
          <#> words
          <#> (\inst -> (inst !! 1 # read, inst !! 3 # read, inst !! 5 # read))

      parsedStacks =
        [1, 5 .. 33]
          <#> readStack stacks
          # zip [1 .. 9]
          # Map.fromList

      ans1 =
        instr
          # foldl
            ( \s (amount, from, to) ->
                fromMaybe Map.empty $ do
                  moved <- s # Map.lookup from <#> List.take amount
                  newFrom <- s # Map.lookup from <#> List.drop amount
                  newTo <- s # Map.lookup to <#> (List.reverse moved <>)
                  s # Map.insert from newFrom # Map.insert to newTo # Just
            )
            parsedStacks
          # foldMap (List.take 1)

      ans2 =
        instr
          # foldl
            ( \s (amount, from, to) ->
                fromMaybe Map.empty $ do
                  moved <- s # Map.lookup from <#> List.take amount
                  newFrom <- s # Map.lookup from <#> List.drop amount
                  newTo <- s # Map.lookup to <#> (moved <>)
                  s # Map.insert from newFrom # Map.insert to newTo # Just
            )
            parsedStacks
          # foldMap (List.take 1)
   in (ans1, ans2)
