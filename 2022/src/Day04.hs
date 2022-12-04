module Day04 (solution) where

import qualified Data.List as List
import Lib

solution :: String -> (String, String)
solution input =
  let parse line =
        let v1 = line # List.takeWhile (/= '-') # read
            v2 = line # List.takeWhile (/= ',') # List.dropWhile (/= '-') # List.tail # read
            v3 = line # List.dropWhile (/= ',') # List.tail # List.takeWhile (/= '-') # read
            v4 = line # List.dropWhile (/= ',') # List.dropWhile (/= '-') # List.tail # read
         in (v1, v2, v3, v4)

      parsed :: [(Int, Int, Int, Int)]
      parsed =
        input
          # lines
          <#> parse

      ans1 =
        parsed
          # filter
            ( \(v1, v2, v3, v4) ->
                v1 <= v3 && v4 <= v2 || v3 <= v1 && v2 <= v4
            )
          # List.length

      ans2 =
        parsed
          # filter
            ( \(v1, v2, v3, v4) ->
                v1 <= v3 && v3 <= v2
                  || v1 <= v4 && v4 <= v2
                  || v3 <= v1 && v1 <= v4
                  || v3 <= v2 && v2 <= v4
            )
          # List.length
   in (show ans1, show ans2)
