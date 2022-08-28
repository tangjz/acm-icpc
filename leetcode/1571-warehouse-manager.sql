# Write your MySQL query statement below
select A.name as warehouse_name, sum(A.units * B.Width * B.Length * B.Height) as volume from Warehouse A inner join Products B on A.product_id = B.product_id group by A.name;
