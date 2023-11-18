module Main where

input = readFile "./input.txt"
ruleset = []
part1 = words <$> input
state = (0,0)
-- state is x,y
-- [(Y+1), (X+1), (Y-1), (X-1)], if R, +1, if L, -1 (looping)  

main :: IO ()
main = putStrLn "hi!"
