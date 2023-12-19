# Write your MySQL query statement below
with cte as (select A.seller_id, count(distinct B.item_id) as num_items from Users A inner join (Orders B inner join Items C on B.item_id = C.item_id) on A.seller_id = B.seller_id and A.favorite_brand <> C.item_brand group by A.seller_id) select * from cte where num_items = (select max(num_items) from cte) order by seller_id asc;
