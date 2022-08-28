# Write your MySQL query statement below
select round(avg(A.num), 1) as median from (select num, frequency, (sum(frequency) over(order by num asc)) as low, (sum(frequency) over(order by num desc)) as upp from Numbers) A where A.frequency >= abs(A.low - A.upp);
