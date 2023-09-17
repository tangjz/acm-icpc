# Write your MySQL query statement below
select order_date, round(100 * sum(order_date = customer_pref_delivery_date) / count(order_date), 2) as immediate_percentage from Delivery group by order_date order by order_date;
