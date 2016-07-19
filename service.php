<?php
header("Content-Type: text/html; charset=utf-8");
header("Connection: close");
require './client.php';
$cli = new client();
if(isset($_POST['d'])):
	$txt = $cli->send_data($_POST['d']);
	echo $txt;
endif;
?>
