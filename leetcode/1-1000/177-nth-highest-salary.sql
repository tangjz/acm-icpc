CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  declare N1 int;
  set N1=N-1;
  RETURN (
      # Write your MySQL query statement below.
      select distinct salary from Employee order by salary desc limit 1 offset N1
  );
END
