# Write your MySQL query statement below
select A.product_id, round(sum(A.price * B.units) / sum(B.units), 2) as average_price from Prices A inner join UnitsSold B on A.product_id = B.product_id and (B.purchase_date between A.start_date and A.end_date) and B.units > 0 group by A.product_id;
