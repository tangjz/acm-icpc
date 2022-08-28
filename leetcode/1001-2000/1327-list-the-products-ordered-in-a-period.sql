# Write your MySQL query statement below
select A.product_name, sum(B.unit) as unit from Products A inner join Orders B on A.product_id = B.product_id and date_format(B.order_date, '%Y-%m') = '2020-02' group by A.product_id having unit >= 100;
