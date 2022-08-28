# Write your MySQL query statement below
select least(from_id, to_id) as person1, greatest(from_id, to_id) as person2, count(*) as call_count, sum(duration) as total_duration from Calls group by person1, person2;
