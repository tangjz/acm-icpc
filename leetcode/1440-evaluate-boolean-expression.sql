# Write your MySQL query statement below
select A.left_operand, A.operator, A.right_operand, if((case A.operator when '<' then B.value < C.value when '>' then B.value > C.value else B.value = C.value end), "true", "false") as value from (Expressions A inner join Variables B on A.left_operand = B.name) inner join Variables C on A.right_operand = C.name;
