
<?php 
    $id = $_POST['gid'];
	$name = $_POST['gname'];
	$cno = $_POST['gcno'];
	$doj = $_POST['gdoj'];
	$un = $_POST['grun'];
	$psw = $_POST['gpsw'];
	$cpsw = $_POST["gcpsw"];
	$login_type =1;

	$servername = "localhost";
	$username = "root";
	$dbname = "hsm";
	
	// Database connection
	$conn = new mysqli($servername,$username, "", $dbname);

	// Check connection
	if ($psw == $cpsw)
	{
		if (!$conn) 
		{
			die("Connection failed: " . mysqli_connect_error());
		}
			
		$sql1 = "INSERT INTO guard (guard_id, name, contact_no, doj) VALUES ('$id','$name' ,'$cno', '$doj');";
		$sql2 = "INSERT INTO login (username, password, login_type) VALUES ('$un','$cpsw' ,'$login_type');";

		if (mysqli_query($conn, $sql1)) 
		{
			echo "New record created successfully";
			header ("Location: security.html?entry=success");
			if (mysqli_query($conn, $sql2)) 
			{
				echo "New record created successfully";
				header ("Location: addSec.html?entry=success");
			} 
		} 
		else 
		{
			echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	}

	else
	{
		echo '<script type="text/javascript">';
		echo ' alert("password does not match")';  //not showing an alert box.
		echo '</script>';
		header ("Location: addSec.html?entry=fail");
	}
?>