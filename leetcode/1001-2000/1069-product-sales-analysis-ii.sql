# Write your MySQL query statement below
select A.product_id, sum(B.quantity) as total_quantity from Product A inner join Sales B on A.product_id = B.product_id group by A.product_id;
