# Write your MySQL query statement below
with cte1 as (select country, sum(points) as points, winery from Wineries group by country, winery), cte2 as (select country, concat(winery, " (", points, ")") as rep, (row_number() over(partition by country order by points desc, winery asc)) as rnk from cte1), cte3 as (select country, rep from cte2 where rnk = 1), cte4 as (select country, rep from cte2 where rnk = 2), cte5 as (select country, rep from cte2 where rnk = 3) select A.country, A.rep as top_winery, ifnull(B.rep, "No second winery") as second_winery, ifnull(C.rep, "No third winery") as third_winery from (cte3 A left join cte4 B on A.country = B.country) left join cte5 C on A.country = C.country order by country asc;