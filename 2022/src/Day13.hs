module Day13 (solution) where

import qualified Data.List as List
import Lib
import Text.Parsec

data Nested
  = L [Nested]
  | I Int
  deriving (Read, Show)

comp :: Nested -> Nested -> Ordering
comp (I a) (I b) = compare a b
comp int@(I _) list@(L _) = comp (L [int]) list
comp list@(L _) int@(I _) = comp list (L [int])
comp (L []) (L []) = EQ
comp (L []) (L _) = LT
comp (L (_)) (L []) = GT
comp (L (a : as)) (L (b : bs)) =
  case comp a b of
    LT -> LT
    EQ -> comp (L as) (L bs)
    GT -> GT

group2 :: [a] -> [(a, a)]
group2 (a : b : xs) = (a, b) : group2 xs
group2 _ = []

solution :: String -> (String, String)
solution input =
  let parseNested =
        L <$> (char '[' *> (parseNested `sepBy` (char ',')) <* char ']')
          <|> I . read <$> many1 digit

      parsed :: [Nested]
      parsed =
        input # lines # filter (/= "")
          # concatMap
            ( \v -> case runParser parseNested () "" v of
                Right n -> [n]
                _ -> []
            )

      ans1 :: Int
      ans1 =
        parsed
          # group2
          # zip [1 ..]
          # filter (\(_, (a, b)) -> comp a b == LT)
          <#> fst
          # sum

      ans2 :: Int
      ans2 =
        (L [L [I 2]] : L [L [I 6]] : parsed)
          # List.sortBy comp
          # zip [1 ..]
          # foldl
            ( \ans (i, v) -> case v of
                L [L [I 2]] -> ans * i
                L [L [I 6]] -> ans * i
                _ -> ans
            )
            1
   in (show ans1, show ans2)
