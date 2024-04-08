newton_sqrt :: Double -> Double
newton_sqrt x = newton_sqrt' x 1
    where newton_sqrt' x y = let y' = (y + x/y) / 2
                             in if abs (y - y') < 0.0001
                                then y'
                                else newton_sqrt' x y'

main = do
    print "Newton's method"
    loop 1
    where loop n = do
            print Enter a number (exit to exit):
            input <- getLine
            if input == "exit"
                then return ()
                else do
                    let x = read input :: Double
                    print $ newton_sqrt x
                    loop (n+1)
