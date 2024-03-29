# Write your MySQL query statement below
with cte as (select A.passenger_id as passenger_id, B.capacity as cap, (row_number() over(partition by B.flight_id order by A.booking_time)) as rnk from Passengers A inner join Flights B on A.flight_id = B.flight_id) select passenger_id, if(rnk > cap, 'Waitlist', 'Confirmed') as Status from cte order by passenger_id asc;
