# Write your MySQL query statement below
select A.student_name as member_A, B.student_name as member_B, C.student_name as member_C from (SchoolA A inner join SchoolB B on A.student_id <> B.student_id and A.student_name <> B.student_name) inner join SchoolC C on A.student_id <> C.student_id and A.student_name <> C.student_name and B.student_id <> C.student_id and B.student_name <> C.student_name;
