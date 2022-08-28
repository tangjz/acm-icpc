# Write your MySQL query statement below
select A.product_name, B.year, B.price from Product A inner join Sales B on A.product_id = B.product_id;
