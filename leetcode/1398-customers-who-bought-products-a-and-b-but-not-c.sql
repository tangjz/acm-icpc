# Write your MySQL query statement below
select A.customer_id, A.customer_name from Customers A left join Orders B on A.customer_id = B.customer_id group by A.customer_id having sum(B.product_name = 'A') > 0 and sum(B.product_name = 'B') > 0 and sum(B.product_name = 'C') = 0 order by A.customer_id;
