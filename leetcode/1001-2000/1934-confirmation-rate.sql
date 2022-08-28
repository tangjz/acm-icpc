# Write your MySQL query statement below
select A.user_id, round(ifnull(sum(B.action = 'confirmed') / count(B.action), 0), 2) as confirmation_rate from Signups A left join Confirmations B on A.user_id = B.user_id group by A.user_id;
