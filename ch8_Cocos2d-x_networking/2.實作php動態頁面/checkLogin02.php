<?php
//取得客户端傳遞過來的參數
$us=$_GET["uname"];
$ps=$_GET["upass"];
//註冊新用户到資料庫
//1連接資料庫
$conn=mysql_connect("127.0.0.1","root","root");
//2.打開資料庫
mysql_select_db("newsdb");
//3.建立查詢
$sql="select * from newsuser where uname='".$us."' and upass='".$ps."';";
//4.執行這個查詢
$result=mysql_query($sql);
$n=mysql_num_rows($result);
//5.關閉資料庫
mysql_close($conn);
if($n>0)
{session_start();
 $row=mysql_fetch_array($result);
 $_SESSION["uid"]=$row["id"];
  echo "1";
}else
{
	echo "0";
}
?>