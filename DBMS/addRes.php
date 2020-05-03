<!DOCTYPE html>
<html lang="en">
<title>Welcome to Housing Society Management System</title>
<link rel = "icon" type = "image/png" href = "pics/logo.png">
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="css/w3.css">
<link rel="stylesheet" href="css/w3-theme-black.css">
<link rel="stylesheet" href="css/font.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">

<style>
html,body,h1,h4 {font-family: "Roboto", sans-serif;}
.w3-sidebar 
{
  z-index: 3;
  width: 250px;
  top: 43px;
  bottom: 0;
  height: inherit;
}
/* Full-width input fields */
input[type=text], input[type=password] 
{
  width: 100%;
  padding: 15px;
  margin: 5px 0 22px 0;
  display: inline-block;
  border: none;
  background: #f1f1f1;
}
</style>
<body>


<!-- Navbar -->
<div class="w3-top">
<div class="w3-bar w3-theme w3-top w3-left-align w3-large">
    <a class="w3-bar-item w3-button w3-left w3-hide-large w3-hover-white w3-large w3-theme-l1" href="javascript:void(0)" onclick="w3_open()"><i class="fa fa-bars"></i></a>
    <a class="w3-bar-item"> <img src="pics/logo.png" style="width:25px;height:25px;"> HSMS</a>
    <a class="w3-bar-item w3-button1 w3-right" href="logout.php"> Logout</a>
  </div>
</div>

<!-- Sidebar -->
<nav class="w3-sidebar w3-bar-block w3-collapse w3-large w3-theme-l5 w3-animate-left" id="mySidebar">
  <a href="javascript:void(0)" onclick="w3_close()" class="w3-right w3-xlarge w3-padding-large w3-hover-black w3-hide-large" title="Close Menu">
    <i class="fa fa-remove"></i>
  </a>
  <h4 class="w3-bar-item"><b>Menu</b></h4>
  <a class="w3-bar-item w3-button w3-hover-black" href="admin.php">New Action</a>
  <a class="w3-bar-item w3-button w3-hover-black" href="logout.php">Logout</a>
</nav>

<!-- Overlay effect when opening sidebar on small screens -->
<div class="w3-overlay w3-hide-large" onclick="w3_close()" style="cursor:pointer" title="close side menu" id="myOverlay"></div>

<!-- Main content: shift it to the right by 250 pixels when the sidebar is visible -->

<div class="w3-main" style="margin-left:250px">

  <div class="w3-row w3-padding-64">
    <div class="w3-call.m12 w3-container">
      <h1 class="w3-text-black">Resident Registration</h1>
      <p class="w3-justify">Please fill up the form below:<br/><br/>
  <form action = "addRes.php" method = "post">
    <div class="w3-container">
      <label for="rfno"><b>Flat Number:</b></label></br>
      <input type="number" placeholder="Enter flat number" name="rfno" required></br><br>
      <label for="rw"><b>Wing:</b></label></br>
      <input type="text" placeholder="Enter wing" name="rw" required></br>
      <label for="rname"><b>Name:</b></label></br>
      <input type="text" placeholder="Enter full name" name="rname" required></br>
      <label for="rcno"><b>Contact Number:</b></label></br>
      <input type="number" placeholder="Enter contact number" name="rcno" required></br><br>
      <label for="racno"><b>Alternate Contact Number:</b></label></br>
      <input type="number" placeholder="Enter alternate contact number" name="racno" required></br><br>
      <label for="rnm"><b>Number of members:</b></label></br>
      <input type="number" placeholder="Enter number of members staying in flat" name="rnm" required></br><br>
      <label for="run"><b>Username:</b></label></br>
      <input type="text" placeholder="Enter username" name="run" required></br>
      <label for="rpsw"><b>Password:</b></label></br>
      <input type="password" placeholder="Enter Password" name="rpsw" required></br>
      <label for="rcpsw"><b>Confirm Password:</b></label></br>
      <input type="password" placeholder="Confirm Password" name="rcpsw" required></br>
      <button type="submit" name = "submit" > Submit </button>
    </div>
  </form>
 <footer id="myFooter">
    <div class="w3-container w3-bottom w3-theme-l1">
      <p>Powered by Roll Nos. 72,73,76,79 of SY CS-B</a></p>
    </div>
 </footer>

<!-- END MAIN -->
</div>

<script>
// Get the Sidebar
var mySidebar = document.getElementById("mySidebar");

// Get the DIV with overlay effect
var overlayBg = document.getElementById("myOverlay");

// Toggle between showing and hiding the sidebar, and add overlay effect
function w3_open() {
  if (mySidebar.style.display === 'block') {
    mySidebar.style.display = 'none';
    overlayBg.style.display = "none";
  } else {
    mySidebar.style.display = 'block';
    overlayBg.style.display = "block";
  }
}

// Close the sidebar with the close button
function w3_close() {
  mySidebar.style.display = "none";
  overlayBg.style.display = "none";
}
</script>


<?php 
	if (isset($_POST["submit"]))
	{
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
				if (mysqli_query($conn, $sql2)) 
				{
					echo '<script type="text/javascript">';
					echo ' alert("Successfully Added to the Database")';   
					echo '</script>';
				} 

				else
				{
					echo '<script type="text/javascript">';
					echo ' alert("Could not add to the Database")';   
					echo '</script>';
				}
      } 
      
			else 
			{
				echo '<script type="text/javascript">';
				echo ' alert("Could not add to the Database")';   
				echo '</script>';
			}
		}

		else
		{
			echo '<script type="text/javascript">';
			echo ' alert("password does not match")';   
			echo '</script>';
			header ("Location: addRes.php?entry=fail");
		}
	}
?>

</body>
</html>

