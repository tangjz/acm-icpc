# Write your MySQL query statement below
select A.buyer_id from Sales A inner join Product B on A.product_id = B.product_id group by A.buyer_id having sum(B.product_name = 'S8') > 0 and sum(B.product_name = 'iPhone') = 0;
