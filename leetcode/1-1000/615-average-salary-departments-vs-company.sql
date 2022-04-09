# Write your MySQL query statement below
select A.pay_month, A.department_id, (case when A.avg_amount < B.avg_amount then 'lower' when A.avg_amount > B.avg_amount then 'higher' else 'same' end) as comparison from (select date_format(C.pay_date, '%Y-%m') as pay_month, D.department_id, avg(amount) as avg_amount from Salary C inner join Employee D on C.employee_id = D.employee_id group by pay_month, D.department_id) A inner join (select date_format(pay_date, '%Y-%m') as pay_month, avg(amount) as avg_amount from Salary group by pay_month) B on A.pay_month = B.pay_month;