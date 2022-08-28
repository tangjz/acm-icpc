# Write your MySQL query statement below
with tmp as (select product_id, year(purchase_date) as purchase_year from Orders group by product_id, purchase_year having count(order_id) >= 3) select distinct A.product_id from tmp A inner join tmp B on A.product_id = B.product_id and A.purchase_year = B.purchase_year + 1;
