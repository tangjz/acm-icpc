# Write your MySQL query statement below
select round(100 * sum(if(order_date = customer_pref_delivery_date, 1, 0)) / count(*), 2) as immediate_percentage from Delivery;
