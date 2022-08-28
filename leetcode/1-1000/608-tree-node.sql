# Write your MySQL query statement below
select id, (case when p_id is null then "Root" when not exists (select id from Tree t2 where t2.p_id = t1.id) then "Leaf" else "Inner" end) as type from Tree t1 order by id asc;
