# Write your MySQL query statement below
select A.dept_name, count(B.student_id) as student_number from Department A left join Student B on A.dept_id = B.dept_id group by A.dept_id order by student_number desc, dept_name asc;
