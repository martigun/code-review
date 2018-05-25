
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

<h2>Passenger Database</h2>
<div>
	<table>
		<tr>
			<td style="font-weight:bold">Passenger ID|</td>
			<td style="font-weight:bold">First Name|</td>
			<td style="font-weight:bold">Last Name|</td>
			<td style="font-weight:bold">Date of Birth|</td>
		</tr>
		
<?php
if(!($stmt = $mysqli->prepare(
	"SELECT
	Passenger.PsgrID,
	Passenger.FirstName,
	Passenger.LastName,
	Passenger.DOB
	FROM Passenger;"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}

if(!$stmt->bind_result($rs1,$rs2,$rs3,$rs4)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}

while($stmt->fetch()){
 echo "<tr><td>"
 . $rs1 . "</td><td>"
 . $rs2 . "</td><td>"
 . $rs3 . "</td><td>"
 . $rs4 . "</td></tr>\n";
}

$stmt->close();
?>

	</table>
</div>

<br>







</body>
</html>