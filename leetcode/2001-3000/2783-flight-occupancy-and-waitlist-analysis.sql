# Write your MySQL query statement below
with cte as (select flight_id, count(flight_id) as tot from Passengers group by flight_id) select A.flight_id as flight_id, if((B.flight_id is not null) and (A.capacity < B.tot), A.capacity, ifnull(B.tot, 0)) as booked_cnt, if((B.flight_id is not null) and (A.capacity < B.tot), B.tot - A.capacity, 0) as waitlist_cnt from Flights A left join cte B on A.flight_id = B.flight_id order by flight_id asc;