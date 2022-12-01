module Lib
  ( (#),
    (<#>),
  )
where

infixl 1 #

infixl 1 <#>

(#) :: a -> (a -> b) -> b
v # f = f v

(<#>) :: Functor f => f a -> (a -> b) -> f b
v <#> f = fmap f v
