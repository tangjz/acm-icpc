# Write your MySQL query statement below
select A.user_id as buyer_id, A.join_date as join_date, count(B.order_id) as orders_in_2019 from Users A left join Orders B on A.user_id = B.buyer_id and year(B.order_date) = '2019' group by user_id;
