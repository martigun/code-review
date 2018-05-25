
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
	<form method="post" action="Ticket_Add_Code.php"> 

		<fieldset>
			<legend>Book New Ticket</legend>
			<p>Passenger
						<select name="inp1">
<?php
if(!($stmt = $mysqli->prepare("SELECT PsgrID, LastName, FirstName FROM Passenger"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($rs1,$rs2,$rs3)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" ' . $rs1 . ' ">
	' . $rs1 . ' - ' . $rs2 . ', ' . $rs3 . '</option>\n';
}
$stmt->close();
?>

			</select></p>
			<p>Flight ID
						<select name="inp2">
<?php
if(!($stmt = $mysqli->prepare("SELECT FlightID, FlightDate, Origin, Destination FROM Flight"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($rs1,$rs2,$rs3,$rs4)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" ' . $rs1 . ' ">
	' . $rs1 . ' - ' . $rs2 . ' - ' . $rs3 . ' - ' . $rs4 .'</option>\n';
}
$stmt->close();
?>

			</select></p>
			<p>Price: <input type="text" name="inp3" /></p>
		</fieldset>

		<p><input type="submit" /></p>
	</form>
</div>




</body>
</html>