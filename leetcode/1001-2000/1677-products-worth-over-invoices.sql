# Write your MySQL query statement below
select A.name, ifnull(sum(B.rest), 0) as rest, ifnull(sum(B.paid), 0) as paid, ifnull(sum(B.canceled), 0) as canceled, ifnull(sum(B.refunded), 0) as refunded from Product A left join Invoice B on A.product_id = B.product_id group by A.product_id order by A.name;
