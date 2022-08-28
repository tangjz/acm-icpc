# Write your MySQL query statement below
select seller_name from Seller where seller_id not in (select distinct seller_id from Orders where year(sale_date) = 2020) order by seller_name asc;
