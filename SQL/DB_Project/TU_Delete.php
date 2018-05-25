
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
	<form method="post" action="TU_Delete_Code.php"> 

		<fieldset>
			<legend>Select a Ticket for Upgrade Deletion</legend>
			
						<select name="TicketID">
<?php
if(!($stmt = $mysqli->prepare(
	"SELECT
	TicketUpgrade.TicketID,
	COUNT(TicketUpgrade.UpgradeID) AS Ucount,
	Passenger.LastName,
	Passenger.FirstName,
	Ticket.FlightID,
	Flight.FlightDate,
	Flight.Origin,
	Flight.Destination
	FROM TicketUpgrade
	LEFT JOIN Ticket
	ON TicketUpgrade.TicketID = Ticket.TicketID
	LEFT JOIN Passenger
	ON Ticket.PsgrID = Passenger.PsgrID
	LEFT JOIN Flight
	ON Ticket.FlightID = Flight.FlightID
	GROUP BY TicketID;"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($rs1,$rs2,$rs3,$rs4,$rs5,$rs6,$rs7,$rs8)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" ' . $rs1 . ' ">' . $rs1 . '-' 
	. $rs2 . ' - ' . $rs3 . ' - ' . $rs4 . ', ' . $rs5 
	.' - ' . $rs6 .' - ' . $rs7 .' - ' . $rs8 . '</option>\n';
}
$stmt->close();
?>

					</select>
			
			
			
		</fieldset>

		<p><input type="submit" /></p>
	</form>
</div>

</body>
</html>