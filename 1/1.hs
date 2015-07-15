myLast :: [a] -> a
myLast [] = error "No last element"
myLast [x] = x
myLast (_:xs) = myLast xs
