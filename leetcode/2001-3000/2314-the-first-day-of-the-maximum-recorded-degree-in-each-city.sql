# Write your MySQL query statement below
with A as (select city_id, max(degree) as degree from Weather group by city_id) select A.city_id, min(B.day) as day, A.degree from A inner join Weather B on A.city_id = B.city_id and A.degree = B.degree group by A.city_id order by A.city_id asc;
