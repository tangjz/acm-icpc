# Write your MySQL query statement below
with cte1 as (select city, avg(price) as avg_price from Listings group by city), cte2 as (select avg(price) as avg_price from Listings) select A.city from cte1 A inner join cte2 B on A.avg_price > B.avg_price order by A.city asc;
