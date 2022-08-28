# Write your MySQL query statement below
select concat(group_concat(item order by power desc separator ''), '=0') as equation from (select concat((case when factor < 0 then concat('', factor) else concat('+', factor) end), (case when power > 1 then concat('X^', power) when power = 1 then 'X' else '' end)) as item, power from Terms) T;
