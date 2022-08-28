# Write your MySQL query statement below
select user_id, product_id from (select user_id, product_id, (rank() over(partition by user_id order by cost desc)) as rnk from (select A.user_id, A.product_id, sum(A.quantity * B.price) as cost from Sales A inner join Product B on A.product_id = B.product_id group by A.user_id, A.product_id) C) D where rnk = 1;
