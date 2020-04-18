
<?php 
    $flat = $_POST['rfno'];
	$wing = $_POST['rw'];
	$name = $_POST['rname'];
    $cno = $_POST['rcno'];
    $acno = $_POST['racno'];
    $nm = $_POST['rnm'];
	$un = $_POST['run'];
	$psw = $_POST['rpsw'];
	$cpsw = $_POST["rcpsw"];
	$login_type =0;

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
			
		$sql1 = "INSERT INTO resident (flat_no, wing, name, contact_no, members, alternate_contact, username) VALUES ('$flat','$wing' ,'$name', '$cno', '$nm', '$acno', '$un');";
		$sql2 = "INSERT INTO login (username, password, login_type) VALUES ('$un','$cpsw' ,'$login_type');";

		if (mysqli_query($conn, $sql1)) 
		{
			echo "New record created successfully";
			header ("Location: security.html?entry=success");
			if (mysqli_query($conn, $sql2)) 
			{
				echo "New record created successfully";
				header ("Location: addRes.html?entry=success");
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
		header ("Location: addRes.html?entry=fail");
	}
?>