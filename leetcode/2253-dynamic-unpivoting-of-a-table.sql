CREATE PROCEDURE UnpivotProducts()
BEGIN
	# Write your MySQL query statement below.
    set @@session.group_concat_max_len = 1000000;
    set @cmd := (select group_concat(concat('(select product_id, "', column_name, '" as store, ', column_name, ' as price from Products where ', column_name, ' is not null)') separator ' union all ') from information_schema.columns where table_schema = 'test' and table_name = 'Products' and column_name <> 'product_id');
    prepare exec_cmd from @cmd;
    execute exec_cmd;
    deallocate prepare exec_cmd;
END
