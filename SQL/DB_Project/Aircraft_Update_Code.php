<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","martigun-db","C3ffN7b6zMGsZycs","martigun-db");

if(!($stmt = $mysqli->prepare("UPDATE Aircraft SET LastService =  ? WHERE AircraftID = ?;"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("si",$_POST['LastService'],$_POST['AircraftID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Updated " . $stmt->affected_rows . " rows to Aircraft.";
}

?>
<br>
<br>
<a href="Main.html">Back to Home</a>