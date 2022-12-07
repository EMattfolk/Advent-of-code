module Day07 (solution) where

import qualified Data.List as List
import qualified Data.Map as Map
import Data.Maybe (fromMaybe)
import Lib

data FileType
  = Dir
  | File Int
  deriving (Show)

solution :: String -> (String, String)
solution input =
  let accum (currentPath, fileTree) line =
        case line !! 0 of
          "$" ->
            if line !! 1 == "cd"
              then case line !! 2 of
                "/" -> ("/", fileTree)
                ".." -> (currentPath # List.dropWhile (/= '/') # List.drop 1, fileTree)
                dir -> (List.reverse dir <> "/" <> List.dropWhile (== '/') currentPath, fileTree)
              else (currentPath, fileTree)
          "dir" ->
            ( currentPath,
              fileTree
                # Map.alter
                  ( \v ->
                      Just $ fromMaybe [] v <> [(List.reverse (List.dropWhile (== '/') currentPath) <> "/" <> (line !! 1), Dir)]
                  )
                  (List.reverse currentPath)
            )
          size ->
            ( currentPath,
              fileTree
                # Map.alter
                  ( \v ->
                      Just $ fromMaybe [] v <> [(line !! 1, File (read size))]
                  )
                  (List.reverse currentPath)
            )

      parsed =
        input
          # lines
          <#> words
          # foldl accum ("", Map.empty)
          # snd

      sumMostTenThousand :: String -> (Int, Int)
      sumMostTenThousand dir =
        parsed
          # Map.lookup dir
          <#> fmap
            ( \(name, ty) -> case ty of
                Dir -> sumMostTenThousand name
                File size -> (0, size)
            )
          <#> foldl (\(accTot, accCur) (tot, cur) -> (accTot + tot, accCur + cur)) (0, 0)
          # fromMaybe (-999999, -999999)
          # (\(tot, cur) -> if cur <= 100000 then (tot + cur, cur) else (tot, cur))

      ans1 = sumMostTenThousand "/"

      spaceNeeded = 30000000 - (70000000 - snd ans1)

      findSmallest :: String -> (Int, Int)
      findSmallest dir =
        parsed
          # Map.lookup dir
          <#> fmap
            ( \(name, ty) -> case ty of
                Dir -> findSmallest name
                File size -> (0, size)
            )
          <#> foldl (\(accTot, accCur) (tot, cur) -> (accTot + tot, accCur + cur)) (spaceNeeded, 0)
          # fromMaybe (-999999, -999999)
          # (\(tot, cur) -> if cur <= 100000 then (tot + cur, cur) else (tot, cur))

      ans2 = ""
   in (show ans1, show spaceNeeded)
