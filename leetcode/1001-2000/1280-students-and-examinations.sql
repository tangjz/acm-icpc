# Write your MySQL query statement below
select A.student_id, A.student_name, C.subject_name, count(B.subject_name) as attended_exams from (Students A join Subjects C) left join Examinations B on A.student_id = B.student_id and B.subject_name = C.subject_name group by A.student_id, C.subject_name order by A.student_id, C.subject_name;
