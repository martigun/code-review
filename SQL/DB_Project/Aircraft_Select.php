
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

<h2>Fleet of Aircraft</h2>
<div>
	<table>
		<tr>
			<td style="font-weight:bold">Aircraft ID|</td>
			<td style="font-weight:bold">Aircraft Type|</td>
			<td style="font-weight:bold">Last Service Date|</td>
			<td style="font-weight:bold">Year Manufactured|</td>
		</tr>
		
<?php
if(!($stmt = $mysqli->prepare(
	"SELECT
	Aircraft.AircraftID,
	Aircraft.AcType,
	Aircraft.LastService,
	Aircraft.YearBuilt
	FROM Aircraft;"))){
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