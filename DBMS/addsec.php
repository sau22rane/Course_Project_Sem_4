
<?php 
    $id = $_POST['gid'];
	$name = $_POST['gname'];
	$cno = $_POST['gcno'];
	$doj = $_POST['gdoj'];

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
		
	$sql = "INSERT INTO guard (guard_id, name, contact_no, doj) VALUES ('$id','$name' ,'$cno', '$doj');";

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