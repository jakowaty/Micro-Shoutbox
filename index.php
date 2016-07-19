<?php
echo <<<FORM
<!DOCTYPE html>
<html>
	<head>
		<title>test</title>
		<script type="text/javascript" src="./asynccli.js"></script>
	</head>
	<body>
	<div id="test_d" style="width:70%; min-height: 500px; border: 1px dotted black"></div>
	<form  method="POST" id="test_f" accept="text/plain" accept-charset="UTF-8" action="./index.php" >
		<textarea name="d" id="d" cols="60" rows="4"></textarea><br/>
		<input type="reset" value="Popraw" /><input type="submit" value="Wyślij" />
	</form>
	
	<script tpe="text/javascript">
		var displ = document.getElementById("test_d");
		var ttform = document.getElementById("test_f");
		var tform = document.getElementById("d");
		ttform.onsubmit = fsub;
		setInterval("esub()" , 1000);
	</script>

	</body>
</html>
FORM;
?>
