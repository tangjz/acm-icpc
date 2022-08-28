# Write your MySQL query statement below
select person_name from (select person_name, turn, (sum(weight) over(order by turn asc)) as agg_weight from Queue) T where agg_weight <= 1000 order by turn desc limit 1;
