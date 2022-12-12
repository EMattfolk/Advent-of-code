module Day11 (solution) where

import Data.Bifunctor (bimap)
import qualified Data.List as List
import Data.Map (Map)
import qualified Data.Map as Map
import Data.Maybe (fromMaybe)
import Lib

data Monkey = Monkey [Int] (Int -> Int) (Int -> Int)

doRound :: Map Int Monkey -> (Map Int Monkey, [Int])
doRound state =
  [0 .. length state - 1]
    # foldl
      ( \(s, scores) i ->
          Map.lookup i s
            # fromMaybe (Monkey [] (const 0) (const 0))
            # ( \(Monkey values changer next) ->
                  ( values
                      # foldl
                        ( \s' v ->
                            let newV = div (changer v) 3
                             in s'
                                  # Map.update
                                    ( \(Monkey vals ch nx) ->
                                        Just (Monkey (vals <> [newV]) ch nx)
                                    )
                                    (next newV)
                        )
                        s,
                    length values : scores
                  )
              )
            # bimap
              ( Map.update
                  ( \(Monkey _ ch nx) ->
                      Just (Monkey [] ch nx)
                  )
                  i
              )
              id
      )
      (state, [])

doRound2 :: Map Int Monkey -> (Map Int Monkey, [Int])
doRound2 state =
  [0 .. length state - 1]
    # foldl
      ( \(s, scores) i ->
          Map.lookup i s
            # fromMaybe (Monkey [] (const 0) (const 0))
            # ( \(Monkey values changer next) ->
                  ( values
                      # foldl
                        ( \s' v ->
                            let newV = mod (changer v) (2 * 3 * 5 * 7 * 11 * 13 * 17 * 19)
                             in s'
                                  # Map.update
                                    ( \(Monkey vals ch nx) ->
                                        Just (Monkey (vals <> [newV]) ch nx)
                                    )
                                    (next newV)
                        )
                        s,
                    length values : scores
                  )
              )
            # bimap
              ( Map.update
                  ( \(Monkey _ ch nx) ->
                      Just (Monkey [] ch nx)
                  )
                  i
              )
              id
      )
      (state, [])

solution :: String -> (String, String)
solution input =
  let parse (_ : items : operation : test : true : false : xs) =
        Monkey
          ( items
              # filter (/= ',')
              # words
              # drop 2
              <#> read
          )
          ( operation
              # words
              # drop 4
              # ( \a ->
                    let op =
                          if (a !! 0) == "+"
                            then (+)
                            else (*)
                     in if (a !! 1) == "old"
                          then (\v -> op v v)
                          else op (read (a !! 1))
                )
          )
          ( let d = test # words # last # read
             in ( \v ->
                    if mod v d == 0
                      then true # words # last # read
                      else false # words # last # read
                )
          ) :
        parse (drop 1 xs)
      parse _ = []

      parsed = input # lines # parse

      ans1 =
        [1 :: Int .. 20]
          # foldl
            ( \(state, activities) _ ->
                let (s, a) = doRound state
                 in (s, List.zipWith (+) a activities)
            )
            ( parsed
                # zip [0 ..]
                # Map.fromList,
              List.replicate (length parsed) 0
            )
          # snd
          # List.sort
          # List.reverse
          # take 2
          # product

      ans2 =
        [1 :: Int .. 10000]
          # foldl
            ( \(state, activities) _ ->
                let (s, a) = doRound2 state
                 in (s, List.zipWith (+) a activities)
            )
            ( parsed
                # zip [0 ..]
                # Map.fromList,
              List.replicate (length parsed) 0
            )
          # snd
          # List.sort
          # List.reverse
          # take 2
          # product
   in (show ans1, show ans2)
