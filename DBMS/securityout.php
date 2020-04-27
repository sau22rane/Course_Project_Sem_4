<!DOCTYPE html>
<html lang="en">
<title>Hello Visitor!</title>
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
    <a class="w3-bar-item w3-button1 w3-right" href="logout.php"> Logout</a>
  </div>
</div>

<!-- Sidebar -->
<nav class="w3-sidebar w3-bar-block w3-collapse w3-large w3-theme-l5 w3-animate-left" id="mySidebar">
  <a href="javascript:void(0)" onclick="w3_close()" class="w3-right w3-xlarge w3-padding-large w3-hover-black w3-hide-large" title="Close Menu">
    <i class="fa fa-remove"></i>
  </a>
  <h4 class="w3-bar-item"><b>Menu</b></h4>
  <a class="w3-bar-item w3-button w3-hover-black" href="security.php">Visitor Form</a>
  <a class="w3-bar-item w3-button w3-hover-black" href="logout.php">Logout</a>
</nav>

<!-- Overlay effect when opening sidebar on small screens -->
<div class="w3-overlay w3-hide-large" onclick="w3_close()" style="cursor:pointer" title="close side menu" id="myOverlay"></div>

<!-- Main content: shift it to the right by 250 pixels when the sidebar is visible -->

<div class="w3-main" style="margin-left:250px">

  <div class="w3-row w3-padding-64">
    <div class="w3-call.m12 w3-container">
      <h1 class="w3-text-black">Hello Visitor!</h1>
      
    <form action="securityout.php" method="post">
    <div class= "w3-container">
      <label for="vname"><b>Name:</b></label></br>
      <input type="text" placeholder="Enter your full name" name="vname" required></br>
      <button type="submit" name = "submit"> Submit </button><br>
      </div>
    </form>
    <?php
        $servername = "localhost";
        $username = "root";
		$dbname = "hsm";  
        // Database connection
        
        $conn = new mysqli($servername,$username, "", $dbname);
        
        if (isset($_POST["submit"]))
        {
            $vname = $_POST["vname"];
            $sql2 = "SELECT * FROM visitor WHERE name like ('$vname');";
            $result = mysqli_query($conn, $sql2);

            if (mysqli_num_rows($result) > 0)
            {
                echo "<br><table border='1'>
                <tr>
                <th>Visitor Id</th>
                <th>Name</th>		
                <th>Contact number</th>
                <th>Vehicle</th>
                <th>Address</th>
                </tr>";
                $sr = 1;
                
                while($row = mysqli_fetch_assoc($result))
                {
                    echo "<tr>";
                    echo "<td>" . $row['visitor_id']. "</td>";
                    echo "<td>" . $row['name'] . "</td>";
                    echo "<td>" . $row['contact_no'] . "</td>";
                    echo "<td>" . $row['vehicle_no'] . "</td>";
                    echo "<td>" . $row['address'] . "</td>";
                    echo "</tr>";
                    $sr += 1;
                }
                echo "</table>";
            }
        }

        if (isset($_POST["submit2"]))
        {
            $id = $_POST["vid"];
            $sql2 = "UPDATE visitor_all SET  time_out = now() WHERE visitor_id = '$id';";
            $sql3 = "DELETE FROM visitor WHERE visitor_id = '$id';";
            $result1 = mysqli_query($conn, $sql2);
            $result2 = mysqli_query($conn, $sql3);

            if ($result1)
            {
                if ($result2)
                {
                    echo '<script type="text/javascript">';
                    echo ' alert("Visitor Status changed Successfully")';   
                    echo '</script>';
                }

                else
                {
                    echo '<script type="text/javascript">';
                    echo ' alert("Please try again")';   
                    echo '</script>';
                }
            }

            else
            {
                echo '<script type="text/javascript">';
                echo ' alert("Please try again")';   
                echo '</script>';
            }
        }

        mysqli_close($conn);
    ?>

<form action="securityout.php" method="post">
    <div class= "w3-container">
      <label for="vname"><b><br>Please choose your Visitor ID from above:</b></label></br>
      <input type="text" placeholder="Enter your Visitor ID" name="vid" required></br>
      <button type="submit" name = "submit2"> Submit </button><br>
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

</body>
</html>

