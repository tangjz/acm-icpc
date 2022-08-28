# Write your MySQL query statement below
select bus_id, passengers_cnt from (select C.bus_id, (C.agg_cnt - @las_cnt) as passengers_cnt, @las_cnt := C.agg_cnt from (select B.bus_id, count(A.passenger_id) as agg_cnt from Buses B left join Passengers A on A.arrival_time <= B.arrival_time group by B.bus_id order by B.arrival_time) C, (select @las_cnt := 0) T) D order by bus_id;
