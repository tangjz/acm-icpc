# Write your MySQL query statement below
select A.id, A.company, A.salary from (select id, company, salary, (row_number() over(partition by company order by salary asc, id asc)) as low, (row_number() over(partition by company order by salary desc, id desc)) as upp from Employee) as A where A.low + 1 >= A.upp and A.low <= A.upp + 1;
