# Write your MySQL query statement below
select max(first_col) as first_col, max(second_col) as second_col from ((select first_col, null as second_col, (row_number() over(order by first_col asc)) as id from Data) union all (select null as first_col, second_col, (row_number() over(order by second_col desc)) as id from Data)) T2 group by id order by id;
