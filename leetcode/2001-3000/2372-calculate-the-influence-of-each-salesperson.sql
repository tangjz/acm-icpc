# Write your MySQL query statement below
select A.salesperson_id, A.name, ifnull(sum(C.price), 0) as total from Salesperson A left join (Customer B inner join Sales C on B.customer_id = C.customer_id) on A.salesperson_id = B.salesperson_id group by A.salesperson_id;
