# Write your MySQL query statement below
select sale_date, sum(if(fruit = 'apples', sold_num, -sold_num)) as diff from Sales group by sale_date;
