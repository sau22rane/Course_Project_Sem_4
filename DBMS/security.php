
<?php
	$name = $_POST['vname'];
	$vno = $_POST['vvno'];
	$cno = $_POST['vcno'];
	$add = $_POST['vadd'];
	$wing = $_POST['vwing'];
	$flat = $_POST['vflat'];

	$servername = "localhost";
	$username = "root";
	$dbname = "hsm";
	
	// Database connection
	$conn = new mysqli($servername,$username, "", $dbname);

	// Check connection
	if (!$conn) 
	{
		die("Connection failed: " . mysqli_connect_error());
	}
		
	$sql = "INSERT INTO visitor (name, contact_no, vehicle_no, address, wing, flat_no) VALUES ('$name', '$cno', '$vno', '$add', '$wing', '$flat');";

	if (mysqli_query($conn, $sql)) 
	{
		echo "New record created successfully";
		header ("Location: security.html?entry=success");
	} 
	else 
	{
		echo "Error: " . $sql . "<br>" . mysqli_error($conn);
	}

?>