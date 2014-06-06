<?php
//取得客户端傳遞過來的參數

$us=$_GET["uname"];

$ps=$_GET["upass"];
//註冊新用户到資料庫

//1連接資料庫

$conn=mysql_connect("127.0.0.1","root","123");

//2.打開資料庫

mysql_select_db("game");

//3.建立查詢

$sql="insert into newsuser (uname,upass) values('".$us."','".$ps."')";

//4.執行這個查詢

mysql_query($sql);

//5.關閉資料庫

mysql_close($conn);

echo "1,insertok";

?>
