# Write your MySQL query statement below
select visited_on, amount, round(amount / 7.0, 2) as average_amount from (select visited_on, (sum(sum(amount)) over(order by visited_on range between interval 6 day preceding and current row)) as amount, (rank() over(order by visited_on)) as rnk from Customer group by visited_on order by visited_on) T where rnk >= 7;
