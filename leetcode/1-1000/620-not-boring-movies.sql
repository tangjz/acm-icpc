# Write your MySQL query statement below
select * from Cinema where description <> 'boring' and id % 2 = 1 order by rating desc;
