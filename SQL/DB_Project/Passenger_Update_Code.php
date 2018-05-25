<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","martigun-db","C3ffN7b6zMGsZycs","martigun-db");

if(!($stmt = $mysqli->prepare("UPDATE Passenger SET FirstName =  ?, LastName = ? WHERE PsgrID = ?;"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("ssi",$_POST['FirstName'],$_POST['LastName'],$_POST['PsgrID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Updated " . $stmt->affected_rows . " rows to Passenger.";
}

?>
<br>
<br>
<a href="Main.html">Back to Home</a>