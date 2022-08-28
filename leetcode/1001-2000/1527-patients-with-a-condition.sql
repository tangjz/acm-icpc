# Write your MySQL query statement below
select * from Patients where regexp_like(conditions, '(^| )DIAB1');
