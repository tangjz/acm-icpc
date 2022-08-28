# Write your MySQL query statement below
select A.name as customer_name, T.customer_id, T.order_id, T.order_date from (select order_id, order_date, customer_id, (row_number() over(partition by customer_id order by order_date desc)) as rnk from Orders) T inner join Customers A on T.rnk <= 3 and A.customer_id = T.customer_id order by A.name asc, T.customer_id asc, T.order_date desc;
