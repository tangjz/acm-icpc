# Write your MySQL query statement below
(select * from Orders where order_type = 0) union all (select * from Orders A where A.order_type = 1 and not exists(select * from Orders B where A.customer_id = B.customer_id and B.order_type = 0));
