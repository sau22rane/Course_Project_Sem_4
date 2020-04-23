<!DOCTYPE html>
<?php
   session_start();
?>
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
.w3-sidebar {
  z-index: 3;
  width: 250px;
  top: 43px;
  bottom: 0;
  height: inherit;
}
/* Full-width input fields */
input[type=text], input[type=password] {
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
    <a class="w3-bar-item w3-button1 w3-right" href="login.html"> Logout</a>
  </div>
</div>

<!-- Sidebar -->
<nav class="w3-sidebar w3-bar-block w3-collapse w3-large w3-theme-l5 w3-animate-left" id="mySidebar">
  <a href="javascript:void(0)" onclick="w3_close()" class="w3-right w3-xlarge w3-padding-large w3-hover-black w3-hide-large" title="Close Menu">
    <i class="fa fa-remove"></i>
  </a>
  <h4 class="w3-bar-item"><b>Menu</b></h4>
  <a class="w3-bar-item w3-button w3-hover-black" href="resident.php">Residents Info</a>
  <a class="w3-bar-item w3-button w3-hover-black" href="rguests.php">View guest history</a>
  <a class="w3-bar-item w3-button w3-hover-black" href="login.php">Logout</a>
</nav>

<!-- Overlay effect when opening sidebar on small screens -->
<div class="w3-overlay w3-hide-large" onclick="w3_close()" style="cursor:pointer" title="close side menu" id="myOverlay"></div>

<!-- Main content: shift it to the right by 250 pixels when the sidebar is visible -->
<form method = "post">
<div class="w3-main" style="margin-left:250px">

  <div class="w3-row w3-padding-64">
    <div class="w3-call.m12 w3-container">
      <h1 class="w3-text-black">Change Password</h1>
      <p class="w3-justify"><br/>
    <div class="w3-container">
      <label for="op"><b>Old Password:</b></label></br>
      <input type="password" placeholder="Enter old password" name="op" required id = "op"></br>
      <label for="np"><b>New Password:</b></label></br>
      <input type="password" placeholder="Enter new password" name="np" required id = "np"></br>
      <label for="cnp"><b>Confirm New Password:</b></label></br>
      <input type="password" placeholder="Confirm new password" name="cnp" required id = "cnp"></br>
      <p id = "error"></p></br>
      <button type = "Submit" class="w3-button1"  style="width:100px;" name = "change-password">Submit</button>
    </div>
 <footer id="myFooter">
    <div class="w3-container w3-bottom w3-theme-l1">
      <p>Powered by Roll Nos. 72,73,76,79 of SY CS-B</a></p>
    </div>
 </footer>


<!-- END MAIN -->
</div>
</form>
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

function myFunction(){
    var np = document.getElementById("np");
    var cnp = document.getElementById("cnp");
    if(np.value!=cnp.value){
        np.style.backgroundColor = "red";
        cnp.style.backgroundColor = "red";
        document.getElementById("error").innerHTML = "Password doesn't match";
    }
    else{
        np.style.backgroundColor = "green";
        cnp.style.backgroundColor = "green";
        
        document.getElementById("error").innerHTML = "";
    }
}


</script>

<?php
	if(isset($_POST["change-password"]))
	{
		include_once 'includes/connection.php';

		$op = $_POST["op"];
		$np = $_POST["np"];
		$cnp = $_POST["cnp"];
		
		
        
        if($np != $cnp){
            echo '<script type="text/javascript">';
            echo ' alert("Password doesn\'t match")';   
            echo '</script>';
        }
        else{
            $sql = 'SELECT * FROM login where username like (\''.$_SESSION["userId"].'\');';
		    $result = mysqli_query($conn, $sql);
            if($row = mysqli_fetch_assoc($result))   // If query is not empty
            {    
                if($op != $row['pwd'])
                {
                    echo '<script type="text/javascript">';
                    echo ' alert("Wrong Password")';   
                    echo '</script>';
                }
                else{
                    $password_update = 'UPDATE login SET pwd = \''.$np.'\' WHERE username like(\''.$_SESSION["userId"].'\');';
                    $result = mysqli_query($conn, $password_update);

                        echo '<script type="text/javascript">';
                        echo ' alert("Password changed Successfully")';   
                        echo '</script>';
                }

            }
        }
	}

?>


</body>
</html>
