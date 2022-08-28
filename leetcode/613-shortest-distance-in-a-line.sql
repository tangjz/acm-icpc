# Write your MySQL query statement below
select min(abs(A.x - B.x)) as shortest from Point A, Point B where A.x <> B.x;
