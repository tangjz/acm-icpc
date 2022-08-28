# Write your MySQL query statement below
select round(sum(tiv_2016), 2) as tiv_2016 from Insurance where tiv_2015 in (select tiv_2015 from Insurance group by tiv_2015 having count(*) > 1) and concat(lat, lon) in (select concat(lat, lon) as state from Insurance group by state having count(*) = 1);
