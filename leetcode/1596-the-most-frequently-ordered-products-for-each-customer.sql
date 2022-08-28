# Write your MySQL query statement below
select B.customer_id, B.product_id, C.product_name from (select A.customer_id, A.product_id, (rank() over(partition by A.customer_id order by count(A.order_id) desc)) as rnk from Orders A group by A.customer_id, A.product_id) B inner join Products C on B.rnk = 1 and B.product_id = C.product_id;
