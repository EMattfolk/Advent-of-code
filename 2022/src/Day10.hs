module Day10 (solution) where

import qualified Data.List as List
import Lib

solution :: String -> (String, String)
solution input =
  let parsed =
        input
          # lines
          <#> words
          # foldl
            ( \(v, acc) l -> case l !! 0 of
                "noop" -> (v, v : acc)
                "addx" -> let newV = v + read (l !! 1) in (newV, newV : v : acc)
                _ -> (v, acc)
            )
            (1, [1])
          # snd
          # List.reverse

      ans1 :: Int
      ans1 =
        (parsed !! 19) * 20
          + (parsed !! 59) * 60
          + (parsed !! 99) * 100
          + (parsed !! 139) * 140
          + (parsed !! 179) * 180
          + (parsed !! 219) * 220

      render index (during : after : rest) =
        let lineIndex = mod (index - 1) 40
            newl =
              if lineIndex == 39
                then "\n"
                else ""
         in if during - 1 <= lineIndex && lineIndex <= during + 1
              then '#' : newl <> render (index + 1) (after : rest)
              else ' ' : newl <> render (index + 1) (after : rest)
      render _ _ = ""

      ans2 = render 1 parsed
   in (show ans1, "See below\n" <> ans2)
