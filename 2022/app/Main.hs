module Main (main) where

import Data.Foldable (traverse_)
import Data.Time.Clock.System (SystemTime, getSystemTime, systemNanoseconds, systemSeconds)
import qualified Day01
import qualified Day02
import qualified Day03
import qualified Day04
import qualified Day05
import qualified Day06
import Lib

solutions :: [String -> (String, String)]
solutions =
  [ Day01.solution,
    Day02.solution,
    Day03.solution,
    Day04.solution,
    Day05.solution,
    Day06.solution
  ]

pad :: Char -> Int -> String -> String
pad char width s = replicate (width - length s) char <> s

diffNs :: SystemTime -> SystemTime -> Integer
diffNs st end =
  toInteger (systemSeconds end - systemSeconds st) * 1000000000
    + toInteger (systemNanoseconds end - systemNanoseconds st)

runDay :: (String -> (String, String)) -> Int -> IO ()
runDay solution day =
  do
    input <- readFile ("input/day" <> pad '0' 2 (show day) <> ".txt")
    st <- getSystemTime
    (a1, a2) <- pure (solution input)
    end <- getSystemTime
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
  st <- getSystemTime
  solutions
    <#> runDay
    # zip [1 ..]
    # traverse_ (\(day, runner) -> runner day)
  end <- getSystemTime
  putStrLn ""
  putStrLn ("Total: " <> show (div (diffNs st end) 1000) <> "μs")
