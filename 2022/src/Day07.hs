module Day07 (solution) where

import qualified Data.List as List
import qualified Data.Map as Map
import Data.Maybe (fromMaybe)
import Lib

data FileType
  = Dir
  | File Int
  deriving (Show)

data Tree
  = D [Tree]
  | F Int
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

      tree :: Tree
      tree =
        let build dir =
              parsed
                # Map.lookup dir
                <#> fmap
                  ( \(name, ty) -> case ty of
                      Dir -> build name
                      File size -> F size
                  )
                # fromMaybe []
                # D
         in build "/"

      sumMostTenThousand :: Tree -> (Int, Int)
      sumMostTenThousand t =
        case t of
          D xs ->
            xs
              <#> sumMostTenThousand
                # foldl (\(accTot, accCur) (tot, cur) -> (accTot + tot, accCur + cur)) (0, 0)
                # (\(tot, cur) -> if cur <= 100000 then (tot + cur, cur) else (tot, cur))
          F size -> (0, size)

      ans1 = sumMostTenThousand tree

      spaceNeeded = 30000000 - (70000000 - snd ans1)

      findSmallest :: Tree -> (Int, Int)
      findSmallest t =
        case t of
          D xs ->
            xs
              <#> findSmallest
                # foldl
                  ( \(accTot, accCur) (tot, cur) ->
                      (min accTot tot, accCur + cur)
                  )
                  (70000000, 0)
                # ( \(tot, cur) ->
                      if cur >= spaceNeeded
                        then (min tot cur, cur)
                        else (tot, cur)
                  )
          F size -> (70000000, size)

      ans2 = findSmallest tree
   in (show $ fst ans1, show $ fst ans2)
