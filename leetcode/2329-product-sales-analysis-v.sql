# Write your MySQL query statement below
select A.user_id, sum(A.quantity * B.price) as spending from Sales A inner join Product B on A.product_id = B.product_id group by user_id order by spending desc, A.user_id asc;
