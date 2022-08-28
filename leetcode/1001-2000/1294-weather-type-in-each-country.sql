# Write your MySQL query statement below
select A.country_name, (case when avg(B.weather_state) <= 15 then 'Cold' when avg(B.weather_state) >= 25 then 'Hot' else 'Warm' end) as weather_type from Countries A inner join Weather B on A.country_id = B.country_id where date_format(B.day, '%Y-%m') = '2019-11' group by A.country_id;
