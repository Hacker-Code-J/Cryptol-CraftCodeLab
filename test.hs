zipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith f list1 list2

list1 :: [Int]
list1 = [1, 2, 3, 4]

list2 :: [Int]
list2 = [10, 20, 30, 40]

-- Using zipWith to add corresponding elements
resultList :: [Int]
resultList = zipWith (+) list1 list2

names :: [String]
names = ["Alice", "Bob", "Charlie"]

ages :: [Int]
ages = [25, 30, 35]

-- Pairing names with ages
people :: [(String, Int)]
people = zipWith (,) names ages
