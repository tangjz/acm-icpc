# Write your MySQL query statement below
select round(min(sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y))), 2) as shortest from Point2D A inner join Point2D B where A.x <> B.x or A.y <> B.y;
