# Write your MySQL query statement below
select B.product_name, A.product_id, A.order_id, A.order_date from (select order_id, order_date, product_id, (rank() over(partition by product_id order by order_date desc)) as rnk from Orders) A inner join Products B on A.rnk = 1 and A.product_id = B.product_id order by B.product_name, A.product_id, A.order_id;
