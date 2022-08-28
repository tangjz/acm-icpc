# Write your MySQL query statement below
select distinct A.seat_id from Cinema A inner join Cinema B on A.seat_id = B.seat_id - 1 or A.seat_id = B.seat_id + 1 where A.free = 1 and B.free = 1;
