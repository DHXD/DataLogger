<?php 

  global $khuvuc;
  global $admin_khuvuc;
  
  switch($_SERVER['SERVER_NAME']) {
  case '113.160.225.111':
    $khuvuc = array('mid_central_region','KHU VỰC TRUNG TRUNG BỘ');
    $admin_khuvuc = array('khuvuctrungtrungbo', 'root');
    break;
  default:
    die('Khong truy cap duoc phan mem Do mua theo ten mien nay. Hay lien he voi quan tri he thong de duoc ho tro.');
  }
  
  //$khuvuc = array('north_central_region','KHU VỰC BẮC TRUNG BỘ');
  


  
  
  
  