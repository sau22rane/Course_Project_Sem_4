<?php
    session_start();
    session_unset();
    session_destroy();
    echo "You have been Logged out Successfully";
    header("Location:web.php");
?>
