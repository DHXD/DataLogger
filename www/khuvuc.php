<?php 

  global $khuvuc;
  global $admin_khuvuc;
  
  switch($_SERVER['SERVER_NAME']) {
  case '113.160.225.111':  
    $khuvuc = array('mid_central_region','KHU VỰC TRUNG TRUNG BỘ');
    $admin_khuvuc = array('khuvuctrungtrungbo', 'root');
    break;
 
  case '113.160.248.129':
  case 'namtrungbo.domua.khituongthuyvan.net':
    $khuvuc = array('south_central_region','KHU VỰC NAM TRUNG BỘ');
    $admin_khuvuc = array('khuvucnamtrungbo', 'root');
    break;
   
  case '117.6.129.235':
  case 'bactrungbo.dnsdynamic.net':
    $khuvuc = array('north_central_region','KHU VỰC BẮC TRUNG BỘ');
    $admin_khuvuc = array('khuvucbactrungbo', 'root');
    break;
   
  case '210.245.110.1':
  case 'nambo.domua.khituongthuyvan.net':
   $khuvuc = array('south_region','KHU VỰC NAM BỘ');
    $admin_khuvuc = array('khuvucnambo', 'root');
    break;
    
   case '113.162.141.98':
  case 'kttvtaynguyen.dyndns.org':
   $khuvuc = array('central_highlands','KHU VỰC TÂY NGUYÊN');
    $admin_khuvuc = array('khuvuctaynguyen', 'root');
    break; 
  default:
    die('Khong truy cap duoc phan mem Do mua theo ten mien nay. Hay lien he voi quan tri he thong de duoc ho tro.');
  }
  
  //$khuvuc = array('north_central_region','KHU VỰC BẮC TRUNG BỘ');
  


  
  
  
  