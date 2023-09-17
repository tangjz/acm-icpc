# Write your MySQL query statement below
(select employee_id, department_id from Employee where primary_flag = 'Y') union (select employee_id, department_id from Employee group by employee_id having count(primary_flag) = 1);
