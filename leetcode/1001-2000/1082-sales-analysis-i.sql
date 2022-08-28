# Write your MySQL query statement below
select seller_id from Sales A group by seller_id having sum(price) = (select sum(price) as tot from Sales A group by seller_id order by tot desc limit 1);
