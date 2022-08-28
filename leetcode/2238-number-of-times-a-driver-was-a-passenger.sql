# Write your MySQL query statement below
select A.driver_id, count(B.ride_id) as cnt from (select distinct driver_id from Rides) A left join Rides B on A.driver_id = B.passenger_id group by A.driver_id;
