# Write your MySQL query statement below
with recursive T as ((select task_id, subtasks_count as subtask_id from Tasks) union all (select task_id, subtask_id - 1 from T where subtask_id > 1)) select * from T where not exists(select * from Executed A where T.task_id = A.task_id and T.subtask_id = A.subtask_id);
