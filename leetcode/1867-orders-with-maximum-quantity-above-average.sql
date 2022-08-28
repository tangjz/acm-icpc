# Write your MySQL query statement below
select order_id from OrdersDetails group by order_id having max(quantity) > (select avg(quantity) as avg_quantity from OrdersDetails group by order_id order by avg_quantity desc limit 1);
