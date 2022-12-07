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
  = D Int [Tree]
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

      sizes :: [Int]
      sizes =
        let build dir =
              parsed
                # Map.lookup dir
                <#> foldl
                  ( \(acc, contents) (name, ty) -> case ty of
                      Dir ->
                        let tr@(D size _) = build name
                         in (acc + size, tr : contents)
                      File size -> (acc + size, contents)
                  )
                  (0, [])
                # fromMaybe (-99999, [])
                # (\(s, c) -> D s c)

            flatten :: Tree -> [Int]
            flatten (D size []) = [size]
            flatten (D size dir) = size : List.concatMap flatten dir
         in build "/" # flatten

      ans1 =
        sizes
          # filter (<= 100000)
          # sum

      spaceNeeded = 30000000 - (70000000 - maximum sizes)

      ans2 =
        sizes
          # filter (>= spaceNeeded)
          # minimum
   in (show ans1, show ans2)
