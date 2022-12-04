module Lib
  ( (#),
    (<#>),
    split,
  )
where

import qualified Data.List as List

infixl 1 #

infixl 1 <#>

(#) :: a -> (a -> b) -> b
v # f = f v

(<#>) :: Functor f => f a -> (a -> b) -> f b
v <#> f = fmap f v

split :: (a -> Bool) -> [a] -> [[a]]
split _ [] = []
split p xs =
  let h = xs # List.takeWhile (not . p)
      t = xs # List.dropWhile (not . p) # List.dropWhile p
   in h : split p t
