
<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","martigun-db","C3ffN7b6zMGsZycs","martigun-db");

if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>
<head>
<title>Skywalker Airlines</title>
</head>
<body>

<h1>Skywalker Airlines</h1>
<a href="Main.html">|   HOME   |</a>

<div>
	<form method="post" action="Passenger_Add_Code.php"> 

		<fieldset>
			<legend>New Passenger</legend>
			<p>First Name: <input type="text" name="inp1" /></p>
			<p>Last Name: <input type="text" name="inp2" /></p>
			<p>Date of Birth (YYYY-MM-DD): <input type="text" name="inp3" /></p>
		</fieldset>

		<p><input type="submit" /></p>
	</form>
</div>


</body>
</html>