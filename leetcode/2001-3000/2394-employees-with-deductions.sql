# Write your MySQL query statement below
select A.employee_id from Employees A left join (select employee_id, sum(ceil(timestampdiff(second, in_time, out_time) / 60)) as accumulated_minutes from Logs group by employee_id) B on A.employee_id = B.employee_id where B.employee_id is null or A.needed_hours * 60 > B.accumulated_minutes;
