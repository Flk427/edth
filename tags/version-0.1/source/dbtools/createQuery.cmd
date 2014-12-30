del goodsnames.sql
FOR /F "usebackq eol=; tokens=1* delims=" %%i IN (goods.list) DO (
	echo insert into goodsnames ^(name, legal^) values ^("%%i", 1^); >> goodsnames.sql
)
