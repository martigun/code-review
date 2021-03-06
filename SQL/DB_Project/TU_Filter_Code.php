<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>
<head>
<title>Skywalker Airlines</title>
</head>
<body>

<h1>Skywalker Airlines</h1>
<a href="Main.html">|   HOME   |</a>
</br>

<div>

<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","martigun-db","C3ffN7b6zMGsZycs","martigun-db");

if(!($stmt = $mysqli->prepare("SELECT
	TicketUpgrade.TicketID,
	TicketUpgrade.UpgradeID,
	Upgrade.UpgradeName,
	Passenger.LastName,
	Passenger.FirstName,
	Ticket.FlightID,
	Flight.FlightDate,
	Flight.Origin,
	Flight.Destination
	FROM TicketUpgrade
	LEFT JOIN Ticket
	ON TicketUpgrade.TicketID = Ticket.TicketID
	LEFT JOIN Upgrade
	ON TicketUpgrade.UpgradeID = Upgrade.UpgradeID
	LEFT JOIN Passenger
	ON Ticket.PsgrID = Passenger.PsgrID
	LEFT JOIN Flight
	ON Ticket.FlightID = Flight.FlightID
	WHERE Ticket.PsgrID = ?
	ORDER BY TicketUpgrade.TicketID ASC;"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['TicketID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Query Results:";
}

if(!$stmt->bind_result($rs1,$rs2,$rs3,$rs4,$rs5,$rs6,$rs7,$rs8,$rs9)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
?>
	</br>
	<table>
		<tr>
			<td style="font-weight:bold">Ticket Nbr|</td>
			<td style="font-weight:bold">Psgr ID|</td>
			<td style="font-weight:bold">Last Name|</td>
			<td style="font-weight:bold">First Name|</td>
			<td style="font-weight:bold">Flight ID|</td>
			<td style="font-weight:bold">Flight Date|</td>
			<td style="font-weight:bold">Origin|</td>
			<td style="font-weight:bold">Destination|</td>
			<td style="font-weight:bold">Price|</td>
		</tr>

		<?php
while($stmt->fetch()){
 echo "<tr><td>"
 . $rs1 . "</td><td>"
 . $rs2 . "</td><td>"
 . $rs3 . "</td><td>"
 . $rs4 . "</td><td>"
 . $rs5 . "</td><td>"
 . $rs6 . "</td><td>"
 . $rs7 . "</td><td>"
 . $rs8 . "</td><td>"
 . $rs9 . "</td></tr>\n";
}

echo "</table>"

?>


</div>

</body>
</html>

