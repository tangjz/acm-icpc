# Write your MySQL query statement below
(select product_id, 10 as price from Products group by product_id having min(change_date) > '2019-08-16') union (select A.product_id, A.new_price as price from (select product_id, new_price, (rank() over(partition by product_id order by change_date desc)) as row_rank from Products where change_date <= '2019-08-16') A where A.row_rank = 1);
