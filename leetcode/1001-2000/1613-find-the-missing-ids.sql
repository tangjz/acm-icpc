# Write your MySQL query statement below
select rnk as ids from json_table(concat('[{}', repeat(',{}', @upp - 1), ']'), '$[*]' columns(rnk for ordinality)) A, (select @upp := (select max(customer_id) from Customers)) B where A.rnk not in (select customer_id from Customers);
