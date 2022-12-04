module Day04 (solution) where

import qualified Data.List as List
import Lib

solution :: String -> (String, String)
solution input =
  let parse line =
        let pairs = line # split (\c -> c == '-' || c == ',') <#> read
         in (pairs !! 0, pairs !! 1, pairs !! 2, pairs !! 3)

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
