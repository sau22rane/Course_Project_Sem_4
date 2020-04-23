<html> 
  <body>
  <h1>Put your HTML content before insertion of b.js.</h1>

  <?php
      
      if(isset($_POST['button1'])) { 
        echo "Button1";
      } 
      if(isset($_POST['button2'])) { 
          echo "This is Button2 that is selected"; 
      } 
      
  ?>
  <button type="submit" name = "button1"> Edit1 </button>&nbsp
  <button type="submit" name = "button2"> Edit2 </button>

  <p>And whatever content you want afterwards.</p>
  </body>
</html>