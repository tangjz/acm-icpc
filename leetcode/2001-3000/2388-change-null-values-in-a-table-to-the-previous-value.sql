# Write your MySQL query statement below
with cte as (select id, drink, (row_number() over()) as row_id from CoffeeShop), cte2 as (select id, drink, row_id, ((sum(drink is not null) over(order by row_id))) as pre_ctr from cte), cte3 as (select drink, pre_ctr from cte2 where drink is not null) select A.id, B.drink from cte2 A inner join cte3 B on A.pre_ctr = B.pre_ctr;
