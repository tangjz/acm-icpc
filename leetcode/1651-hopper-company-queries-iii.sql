# Write your MySQL query statement below
with A as (select * from json_table('[{},{},{},{},{},{},{},{},{},{},{},{}]', '$[*]' columns(month for ordinality)) T), B as (select A.month, ifnull(sum(T2.ride_distance), 0) as dis, ifnull(sum(T2.ride_duration), 0) as dur from A left join (Rides T1 inner join AcceptedRides T2 on T1.ride_id = T2.ride_id) on A.month = month(T1.requested_at) and year(T1.requested_at) = 2020 group by A.month)
select month, round(avg(dis) over(order by month rows between current row and 2 following), 2) as average_ride_distance, round(avg(dur) over(order by month rows between current row and 2 following), 2) as average_ride_duration from B order by month limit 10;
