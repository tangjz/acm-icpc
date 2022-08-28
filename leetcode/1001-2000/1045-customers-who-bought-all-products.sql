# Write your MySQL query statement below
select customer_id from Customer group by customer_id having count(distinct product_key) = (select count(*) from Product);
