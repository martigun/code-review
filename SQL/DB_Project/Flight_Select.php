
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

<h2>Flight Schedule</h2>
<div>
	<table>
		<tr>
			<td style="font-weight:bold">Flight Number|</td>
			<td style="font-weight:bold">Aircraft ID|</td>
			<td style="font-weight:bold">Aircraft Type|</td>
			<td style="font-weight:bold">Flight Date|</td>
			<td style="font-weight:bold">Origin|</td>
			<td style="font-weight:bold">Destination|</td>
		</tr>
		
<?php
if(!($stmt = $mysqli->prepare(
	"SELECT
	Flight.FlightID,
	Flight.AircraftID,
	Aircraft.AcType,
	Flight.FlightDate,
	Flight.Origin,
	Flight.Destination
	FROM Flight
	LEFT JOIN Aircraft
	ON Flight.AircraftID = Aircraft.AircraftID
	ORDER BY Flight.FlightDate ASC;"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}

if(!$stmt->bind_result($FlightID, $AircraftID, $AcType, $FlightDate, $Origin, $Destination)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}

while($stmt->fetch()){
 echo "<tr><td>"
 . $FlightID . "</td><td>"
 . $AircraftID . "</td><td>"
 . $AcType . "</td><td>"
 . $FlightDate . "</td><td>"
 . $Origin . "</td><td>"
 . $Destination . "</td></tr>\n";
}

$stmt->close();
?>

	</table>
</div>

<br>







</body>
</html>