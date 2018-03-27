 <?php
  require_once("dbconfig.php");
  if (isset($_GET["page"]))
    $page = (int)$_GET["page"] ;
  else
    $page = 1 ;
  if (isset($_POST["search"]))
      $search = $_POST["search"] ;
  else
      $search = null;
  include("footer.html");


?>

<!DOCTYPE html>
<html>

  <head>
    <meta charset="utf-8">
    <title>21500766 - ChuEugene</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="list.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  </head>

  <body>
    <h1>4</h1>
    <div class="container">
      <table class="table table-hover">
        <thead>
          <tr>
            <th id="number">#</th>
            <th id="title">Title</th>
            <th id="writer">Writer</th>
            <th id="date">Date</th>
          </tr>
        </thead>
        <tbody>
          <?php

            $query = "SELECT id, title, writer, write_date FROM content where delete_backUp='false' order by id limit ".(($page - 1) * 10).",10;";
            //삭제되지 않는것만 불러올것
            $result = mysqli_query($conn, $query);
            while($row = mysqli_fetch_array($result)) {

              //midelterm 2
              $time = strtotime($row["write_date"]);
              $myFormatForView = date("d/m/Y g:i A", $time);

              echo "<tr>";
              echo "<td>".$row["id"]."</td>";
              echo "<td>".$row["title"]."</td>";
              echo "<td>".$row["writer"]."</td>";
              echo "<td>".$myFormatForView."</td>";
              echo "</tr>";
            }
          ?>
        </tbody>
      </table>


      <button id="btn" class="btn btn-default" type="button">Write</button>


      <div class="text-center">
        <ul class="pagination col-md-12">
          <?php
            $query = "SELECT id FROM content where delete_backUp='false';";
            $result = mysqli_query($conn, $query);
            $rows = mysqli_num_rows($result)-1;
            if (!($rows < 10)) {

              if ($page == 1)
                echo "<li class='disabled'><a href='#'><span>&laquo;</span></a></li>";
              else
                echo "<li><a href='list.php?page=".($page - 1)."'><span>&laquo;</span></a></li>";


              for ($i = 1; $i <= (int)($rows / 10 + 1); $i++) { //write all page numbers

                if ($page == $i)
                  echo "<li class='active'><a href='list.php?page=".$i."'>".$i."</a></li>";
                else
                  echo "<li><a href='list.php?page=".$i."'>".$i."</a></li>";
              }

              if ($page == (int)($rows / 10 + 1))
                echo "<li class='disabled'><a href='#'><span>&raquo;</span></a></li>";
              else
                echo "<li><a href='list.php?page=".($page + 1)."'><span>&raquo;</span></a></li>";
            }

            echo "row =".$rows.",page= ".(int)(($rows / 10) + 1).",search= ".$search;
          ?>
        </ul>
      </div>


      <form class="form-horizontal" action="list.php" method="post">
        <div class="form-group">
          <select class="col-md-1 control-label">
            <option value="title">제목</option>
            <option value="writer">글쓴이</option>
          </select>
          <div class="col-md-6">
            <input class="form-control" type="text" name="search">
          </div>
          <div class="col-md-1">
            <input type="submit" value="Search">
          </div>
        </div>
      </form>


      <script>
        $(function() {
          $("table > tbody > tr").click(function() {
            var number = $(this).find("td").eq(0).text();
            var url = "detail.php?id=" + number;
            location.href = url;
          });
          $("#btn").click(function() {
            location.href = "write.html";
          });
        });
      </script>



    </div>
  </body>
</html>
