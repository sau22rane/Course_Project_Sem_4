<?php

$servername = "localhost";

$dbUsername = "root";
$dbPassword = "";
$dbname = "hsm";

$conn = mysqli_connect($servername,$dbUsername,$dbPassword,$dbname);

if(!$conn){
    die("Connection Failed :".mysqli_connect_error()); 
}

if(isset($_POST["login-submit"]))
{
    $username = $_POST["uname"];
    $password = $_POST["psw"];
    
    $sql = "SELECT * FROM login where username = ?;";
    $stmt = mysqli_stmt_init($conn);

    if (!mysqli_stmt_prepare($stmt,$sql))
    {
        header("Location: login.html?error=SQLERROR");
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
               header("Location: login.html?error=wrongpassword");
               
            }
            else   // If password is correct
            {

                session_start();
                $_SESSION['userId'] = $row['username'];
                
                if($row['login_type']==0)
                {
                    header("Location: resident.html?login=success");
                }

                else if($row['login_type']==1)
                {
                    header("Location: security.html?login=success");
                }

                else if($row['login_type']==2)
                {
                    header("Location: admin.html?login=success");
                }
                

            }
        }
    }

}

else
{
    header("Location: login.html");
}
?>