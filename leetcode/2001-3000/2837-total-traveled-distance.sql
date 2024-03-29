# Write your MySQL query statement below
select A.user_id as user_id, A.name as name, ifnull(sum(B.distance), 0) as 'traveled distance' from Users A left join Rides B on A.user_id = B.user_id group by user_id order by user_id asc;
