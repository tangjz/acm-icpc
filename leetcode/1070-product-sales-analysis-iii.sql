# Write your MySQL query statement below
select A.product_id, A.year as first_year, A.quantity, A.price from (select product_id, year, quantity, price, (rank() over(partition by product_id order by year asc)) as rnk from Sales) A where A.rnk = 1;
