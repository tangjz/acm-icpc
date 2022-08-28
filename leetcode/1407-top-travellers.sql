# Write your MySQL query statement below
select A.name as name, ifnull(sum(B.distance), 0) as travelled_distance from Users A left join Rides B on A.id = B.user_id group by A.id order by travelled_distance desc, A.name asc;
