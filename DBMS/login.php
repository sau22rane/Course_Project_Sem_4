<!DOCTYPE html>
<html lang="en">
<title>HSMS Login</title>
<link rel = "icon" type = "image/png" href = "pics/logo.png">
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="css/w3.css">
<link rel="stylesheet" href="css/w3-theme-black.css">
<link rel="stylesheet" href="css/font.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
<style>
html,body,h1,h4 {font-family: Roboto, sans-serif;}
.w3-sidebar {
  z-index: 3;
  width: 250px;
  top: 43px;
  bottom: 0;
  height: inherit;
}
input[type=text], input[type=password] {
  width: 300px;
  padding: 12px 20px;
  margin: 8px ;
  display: inline-block;
  border: 1px solid #ccc;
  box-sizing: border-box;
}
</style>
<body>

<!-- Navbar -->
<div class="w3-top">
  <div class="w3-bar w3-theme w3-top w3-left-align w3-large">
    <a class="w3-bar-item w3-button w3-left w3-hide-large w3-hover-white w3-large w3-theme-l1" href="javascript:void(0)" onclick="w3_open()"><i class="fa fa-bars"></i></a>
    <a class="w3-bar-item w3-button" href="web.php"> <img src="pics/logo.png" style="width:25px;height:25px;"> HSMS</a>
    <a class="w3-bar-item w3-button1 w3-right" href="login.php"> Login</a>
  </div>
</div>

<!-- Sidebar -->
<nav class="w3-sidebar w3-bar-block w3-collapse w3-large w3-theme-l5 w3-animate-left" id="mySidebar">
  <a href="javascript:void(0)" onclick="w3_close()" class="w3-right w3-xlarge w3-padding-large w3-hover-black w3-hide-large" title="Close Menu">
    <i class="fa fa-remove"></i>
  </a>
  <h4 class="w3-bar-item"><b>Menu</b></h4>
  <a class="w3-bar-item w3-button w3-hover-black" href="login.php">Login</a>
  <a class="w3-bar-item w3-button w3-hover-black" href="rules.php">Rules</a>
  <a class="w3-bar-item w3-button w3-hover-black" href="aboutus.php">About Us</a>
</nav>

<!-- Overlay effect when opening sidebar on small screens -->
<div class="w3-overlay w3-hide-large" onclick="w3_close()" style="cursor:pointer" title="close side menu" id="myOverlay"></div>

<!-- Main content: shift it to the right by 250 pixels when the sidebar is visible -->
<form action="login.php" method = "post">
    
    <div class="w3-main w3-row w3-padding-64 w3-display-topmiddle" style="margin-left:150px">
    <div class="w3-container">
      <h1 class="w3-text-black">Login</h1></br>
      <label for="uname"><b>Username</b></label></br>
      <input type="text" placeholder="Enter Username" name="uname" required></br>

    <label for="psw"><b>Password</b></label></br>
    <input type="password" placeholder="Enter Password" name="psw" required></br></br>
    <button type="submit" name ="login-submit"> Submit </button>
    <label>
    <input type="checkbox" checked="checked" name="remember"> Remember me
    </label></br></br>
  </div>

</form>
<!-- END MAIN -->
</div>

  <footer id="myFooter">
    <div class="w3-container w3-bottom w3-theme-l1" style="margin-left:250px">
      <p>Powered by Roll Nos. 72,73,76,79 of SY CS-B</a></p>
    </div>
  </footer>



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
	if(isset($_POST["login-submit"]))
	{
		$servername = "localhost";
		$username = "root";
		$dbname = "hsm";
		
		// Database connection
		$conn = new mysqli($servername,$username, "", $dbname);

		$username = $_POST["uname"];
		$password = $_POST["psw"];
		
		$sql = "SELECT * FROM login where username = ?;";
		$stmt = mysqli_stmt_init($conn);

		if (!mysqli_stmt_prepare($stmt,$sql))
		{
			header("Location: login.php?error=SQLERROR");
			exit();
		}

		else
		{
			mysqli_stmt_bind_param($stmt,"s",$username);
			mysqli_stmt_execute($stmt);
			$result = mysqli_stmt_get_result($stmt);

			if($row = mysqli_fetch_assoc($result))   // If query is not empty
			{    
				if($password != $row['password'])
				{
					echo '<script type="text/javascript">';
					echo ' alert("Wrong Password")';   
					echo '</script>';
				}
				else   // If password is correct
				{

					session_start();
          $_SESSION['userId'] = $row['username'];
          $_SESSION['login_time'] = time();
					
					if($row['login_type']==0)
					{
						header("Location: resident.php?login=success");	
					}

					else if($row['login_type']==1)
					{
						header("Location: security.php?login=success");
					}

					else if($row['login_type']==2)
					{
						header("Location: admin.php?login=success");
					}
				}
			}
		}
	}
?>

</body>
</html>

