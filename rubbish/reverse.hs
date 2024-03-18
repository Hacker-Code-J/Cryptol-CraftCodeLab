class FiniteSequence s where
    isEmpty :: s a -> Bool
    first :: s a -> a
    rest :: s a -> s a

instance FiniteSequence [] where
    isEmpty = null
    first = head
    rest = tail

genericReverse :: (FiniteSequence s) => s a -> s a
genericReverse seq
    | isEmpty seq = seq
    | otherwise = genericReverse (rest seq) `append` (first seq)

append :: (FiniteSequence s) => s a -> a -> s a

append seq x = seq ++ [x]
