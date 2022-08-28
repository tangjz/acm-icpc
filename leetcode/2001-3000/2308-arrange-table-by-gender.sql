# Write your MySQL query statement below
select user_id, gender from (select user_id, gender, ((row_number() over(partition by gender order by user_id)) * 3 + (case gender when 'female' then 0 when 'other' then 1 else 2 end)) as rnk from Genders) T order by rnk;
