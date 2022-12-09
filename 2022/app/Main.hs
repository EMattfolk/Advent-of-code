module Main (main) where

import Control.DeepSeq (force)
import Control.Exception (evaluate)
import Data.Foldable (traverse_)
import qualified Day01
import qualified Day02
import qualified Day03
import qualified Day04
import qualified Day05
import qualified Day06
import qualified Day07
import qualified Day08
import qualified Day09
import Lib
import System.CPUTime (getCPUTime)

solutions :: [String -> (String, String)]
solutions =
  [ Day01.solution,
    Day02.solution,
    Day03.solution,
    Day04.solution,
    Day05.solution,
    Day06.solution,
    Day07.solution,
    Day08.solution,
    Day09.solution
  ]

pad :: Char -> Int -> String -> String
pad char width s = replicate (width - length s) char <> s

diffNs :: Integer -> Integer -> Integer
diffNs st end =
  div (end - st) 1000

runDay :: (String -> (String, String)) -> Int -> IO ()
runDay solution day =
  do
    input <- readFile ("input/day" <> pad '0' 2 (show day) <> ".txt")
    st <- getCPUTime
    (a1, a2) <- evaluate $ force (solution input)
    end <- getCPUTime
    let timeDiffNs = diffNs st end
        out =
          "Day "
            <> pad ' ' 2 (show day)
            <> ": "
            <> pad ' ' 7 (show (div timeDiffNs 1000))
            <> "μs - "
            <> a1
            <> ", "
            <> a2
    putStrLn out

main :: IO ()
main = do
  st <- getCPUTime
  solutions
    <#> runDay
    # zip [1 ..]
    # traverse_ (\(day, runner) -> runner day)
  end <- getCPUTime
  putStrLn ""
  putStrLn ("Total: " <> show (div (diffNs st end) 1000) <> "μs")
