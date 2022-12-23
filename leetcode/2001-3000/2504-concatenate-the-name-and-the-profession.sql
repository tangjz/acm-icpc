# Write your MySQL query statement below
select person_id, concat(name, '(', left(profession, 1), ')') as name from Person order by person_id desc;
