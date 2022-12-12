module Day11 (solution) where

import Data.Bifunctor (bimap)
import qualified Data.List as List
import Lib

update :: (a -> a) -> Int -> [a] -> [a]
update _ _ [] = []
update f 0 (x : xs) = f x : xs
update f i (x : xs) = x : update f (i - 1) xs

data Monkey = Monkey [Int] (Int -> Int) (Int -> Int)

doRound :: (Int -> Int) -> [Monkey] -> ([Monkey], [Int])
doRound modifier state =
  [0 .. length state - 1]
    # foldl
      ( \(s, scores) i ->
          (s !! i)
            # ( \(Monkey values changer next) ->
                  ( values
                      # foldl
                        ( \s' v ->
                            let newV = modifier (changer v)
                             in s'
                                  # update
                                    ( \(Monkey vals ch nx) ->
                                        Monkey (vals <> [newV]) ch nx
                                    )
                                    (next newV)
                        )
                        s,
                    length values : scores
                  )
              )
            # bimap
              ( update
                  ( \(Monkey _ ch nx) ->
                      Monkey [] ch nx
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

      solve rounds performRound =
        [1 :: Int .. rounds]
          # foldl
            ( \(state, activities) _ ->
                let (s, a) = performRound state
                 in (s, List.zipWith (+) a activities)
            )
            (parsed, List.replicate (length parsed) 0)
          # snd
          # List.sort
          # List.reverse
          # take 2
          # product

      ans1 = solve 20 (doRound (flip div 3))
      ans2 = solve 10000 (doRound (flip mod (2 * 3 * 5 * 7 * 11 * 13 * 17 * 19)))
   in (show ans1, show ans2)
