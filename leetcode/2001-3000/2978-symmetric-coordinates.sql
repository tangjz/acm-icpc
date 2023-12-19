# Write your MySQL query statement below
with cte as (select A.X, A.Y, (row_number() over()) as id from Coordinates A) select A.X, A.Y from cte A inner join cte B on A.X <= A.Y and A.X = B.Y and A.Y = B.X and A.id <> B.id group by A.X, A.Y order by A.X asc, A.Y asc;
