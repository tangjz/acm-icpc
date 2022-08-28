# Write your MySQL query statement below
select airport_id from (select airport_id, (rank() over(order by sum(flights_count) desc)) as rnk from ((select departure_airport as airport_id, flights_count from Flights) union all (select arrival_airport as airport_id, flights_count from Flights)) T1 group by airport_id) T2 where rnk = 1;
