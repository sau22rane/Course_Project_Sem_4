
<?php
	$name = $_POST['name'];
	$vno = $_POST['vno'];
	$cno = $_POST['cno'];
	$add = $_POST['add'];
	$flat = $_POST['flat'];

	$servername = "localhost";
	$username = "root";
	$dbname = "HSM";
	
	// Database connection
	$conn = new mysqli($servername,$username, "", $dbname);

	// Check connection
	if (!$conn) 
	{
		die("Connection failed: " . mysqli_connect_error());
	}
		
	$sql = "INSERT INTO visitor (nam, vno, cno, addre, flat) VALUES ('$name', '$vno', '$cno', '$add', '$flat');";

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