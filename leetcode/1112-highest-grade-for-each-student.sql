# Write your MySQL query statement below
select A.student_id, A.course_id, A.grade from (select student_id, course_id, grade, (row_number() over (partition by student_id order by grade desc, course_id asc)) as row_rank from Enrollments) as A where A.row_rank = 1 order by A.student_id asc;
