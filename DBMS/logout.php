<?php

    $servername = "localhost";
    $username = "root";
    $dbname = "hsm";

    // Database connection
    $conn = new mysqli($servername,$username, "", $dbname);
    session_start();

    $id = session_id();
    $sql = "UPDATE session SET status = 0 WHERE id = '$id';";
    mysqli_query ($conn, $sql);

    session_unset();
    session_destroy();
    echo "You have been Logged out Successfully";
    header("Location:web.php");
?>
