<?php
  
/**
*begin: 28-09-12
*
*/

function _insert_outbox($phone, $sms){
  dsm('phone '.$phone);
  dsm('sms '.$sms);
  
  /*cach 1:*/
  // db_insert('datalogger.outbox')
    // ->fields(array(
      // 'UpdatedInDB' => CURRENT_TIMESTAMP, 
      // 'InsertIntoDB' => date('Y-m-d','0000-00-00 00:00:00'), 
      // 'SendingDateTime' => date('Y-m-d','0000-00-00 00:00:00'), 
      // 'SendBefore' => date('H:i:s','23:59:59'), 
      // 'SendAfter' => date('H:i:s','00:00:00'), 
      // 'Text' => NULL, 
      // 'DestinationNumber' => $phone, 
      // 'Coding' => 'Default_No_Compression', 
      // 'UDH' => NULL, 
      // 'Class'=> -1, 
      // 'TextDecoded' => $sms,
      // 'ID' => NULL, 
      // 'MultiPart' => false, 
      // 'RelativeValidity' => -1, 
      // 'SenderID' => NULL, 
      // 'SendingTimeOut' => '0000-00-00 00:00:00', 
      // 'DeliveryReport' => 'default', 
      // 'CreatorID' => '',
      // 'DestinationNumber' => '01664597466',
      // 'TextDecoded' => 'hello world',
    // ))
    // ->execute();
    
  /*cach 2:*/ 
  // db_query('INSERT INTO datalogger.outbox(DestinationNumber, TextDecoded)VALUES(:phone, :sms)',
    // array(':phone' => $phone,
          // ':sms' => $sms));
  
  
  /*cach 3:*/
  $nid = db_insert('datalogger.outbox')
    ->fields(array('DestinationNumber', 'TextDecoded'))
    ->values(array(
      'DestinationNumber' =>  $phone,
      'TextDecoded' => $sms,
    ))
    ->execute();
  dsm('Inserted '.$nid);
}

/**
*begin: 25-09-12
*/

function _convert_strdate_to_date($strFormat = 'ymdhis', $strDate){
  return date($strFormat, strtotime($strDate));
}

/**
*begin: 11-09-12
*/

function _user_form(){
  $form['u_nameLogin'] = array(
    '#type' => 'textfield',
    '#title' => t('Tên đăng nhập: '),
  );
  
  $form['u_lastName'] = array(
    '#type' => 'textfield',
    '#title' => t('Họ: '),
  );
  
  $form['u_firstname'] = array(
    '#type' => 'textfield',
    '#title' => t('Tên: '),
  );
  
   $form['u_nameDisplay'] = array(
    '#type' => 'textfield',
    '#title' => t('Tên hiển thị: '),
  );
  
  $form['u_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Địa chỉ Email: '),
  );
  
  $form['u_createDate'] = array(
    '#type' => 'item',
    '#title' => t('Ngày được tạo: '.date('d/m/Y h:m:s')),
  );
  
  $form['u_loginDate'] = array(
    '#type' => 'item',
    '#title' => t('Ngày đăng nhập gần nhất: '.date('d/m/Y h:m:s')),
  );
  
  $form['u_actionDate'] = array(
    '#type' => 'item',
    '#title' => t('Ngày hoạt động gần nhất: '.date('d/m/Y h:m:s')),
  );
  
  $form['u_changePassDate'] = array(
    '#type' => 'item',
    '#title' => t('Thời điểm thay đổi password: '.date('d/m/Y h:m:s')),
  );
  
  $form['u_lockDate'] = array(
    '#type' => 'item',
    '#title' => t('Ngày bị khóa gần nhất:never'),
  );
  
  $form['u_isOnl'] = array(
    '#type' => 'item',
    '#title' => t('Người dùng đang online: true'),
  );
  
  $form['u_isLock'] = array(
    '#type' => 'item',
    '#title' => t('Bị khóa:false'),
  );
  
  $form['u_isAccept'] = array(
    '#type' => 'item',
    '#title' => t('Chấp nhận:false'),
  );
  
  $form['u_updatePass'] = array(
    '#type' => 'item',
    '#title' => t('Cập nhật password:false'),
  );
  
  $form['u_delete'] = array(
    '#type' => 'item',
    '#title' => t('Xóa bỏ:false'),
  );
  
  $form['sub_add'] = array(
     '#type' => 'submit',
     '#value' => t('Cập nhật'),    
  );
  
  $form['sub_cancel'] = array(
     '#type' => 'submit',
     '#value' => t('Xóa'),    
  );
  
  
  return $form;  
}

function _user_pass_form(){
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Quản lý password'),
  );
  
  $form['submitExportData'] = array(
     '#type' => 'submit',
     '#value' => t('Cập nhật'),    
  );
  
  return $form;  
}

function _user_profile_form(){
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Quản lý profile'),
  );
  
  $form['submitExportData'] = array(
     '#type' => 'submit',
     '#value' => t('Cập nhật'),    
  );
  
  return $form;  
}

function _user_group_form(){
  $form['u_gr_power'] = array(
    '#type' => 'select',
    '#title' => t('Quyền hạn: '),
    '#options' => array(
      1 => 'Admin',
      2 => 'Register user',
      3 => 'Quản lý', 
    ),
  );
  
  $form['u_pr_eff'] = array(
    '#type' => 'date_popup',
    '#title' => t('Ngày áp dụng: '),
  );
  
  $form['u_pr_exp'] = array(
    '#type' => 'date_popup',
    '#title' => t('Ngày hết hiệu lực: '),
  );
  
  $form['u_gr_add'] = array(
    '#type' => 'submit',
    '#value' => t('Thêm quyền hạn: '),
  );
  
  return $form;  
}

function _user_add_form(){
  drupal_set_title('Quản lý thông tin người dùng');
  $form['u_nameLogin'] = array(
    '#type' => 'textfield',
    '#title' => t('Tên đăng nhập: '),
  );
  
  $form['u_lastName'] = array(
    '#type' => 'textfield',
    '#title' => t('Họ: '),
  );
  
  $form['u_firstname'] = array(
    '#type' => 'textfield',
    '#title' => t('Tên: '),
  );
  
  $form['u_nameDisplay'] = array(
    '#type' => 'textfield',
    '#title' => t('Tên hiển thị: '),
  );
  
  $form['u_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Địa chỉ Email: '),
  );
  
  $form['u_accept'] = array(
    '#type' => 'checkbox',
    '#title' => t('Chấp nhận: '),
  );   
  
  $form['u_notice'] = array(
    '#type' => 'checkbox',
    '#title' => t('Thông báo: '),
  );
  
  $form['u_item'] = array(
    '#type' => 'item',
    '#title' => t('Tùy chọn nhập một password cho thành viên này, hoặc cho phép hệ thống tạo ra một password ngẫu nhiên: '),
  );
  
  $form['u_rand_pass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Password ngẫu nhiên: '),
  );    
  
  $form['u_pass_confirm'] = array(
    '#type' => 'password_confirm',
  );
  
  $form['sub_add'] = array(
     '#type' => 'submit',
     '#value' => t('Tạo người dùng'),    
  );
  
  $form['sub_cancel'] = array(
     '#type' => 'submit',
     '#value' => t('Hủy bỏ'),    
  );
  return $form;  
}

/**
*begin: 11-09-12
*/

function _log_rainfall_form(){
  $form['logStation'] = array(
     '#type' => 'select',
     '#title' => t('Chọn trạm: '),
     '#options' => array(
       0 => t('Tất cả các trạm'),
       1 => t('Kỳ Trinh'),
     ),
  ); 
  
   $form['logDate'] = array(
     '#type' => 'date_popup',
     '#title' => t('Chọn ngày: '),
  );
  
  $form['logSubmit'] = array(
     '#type' => 'submit',
     '#value' => t('Xem nhật ký'),    
  );
  
  $headers = array(
    1 => 'STT',
    2 => 'Thời gian',
    3 => 'Tên file xử lý',
    4 => 'Trạng thái',
    5 => 'Mô tả',
  );
  
  $rows = array(
    array(1,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(2,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(3,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(4,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(5,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(6,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(7,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(8,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(9,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(10,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(11,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(12,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(13,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(14,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(15,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(16,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(17,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(18,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(19,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(20,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(21,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(22,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(23,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(24,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(25,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(26,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(27,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(28,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
    array(29,'18/08/2012 16:17:00','D:\SETUP\devc++\binutils-2.15.91-20040904-1\include\091253_20120818165827','Thành công',''),    
   
  );
  
  $form['table'] = array(
    '#theme' => 'table',
    '#header' => $headers,
    '#rows' => $rows,
    '#empty' => t('Hiện tại không có thông tin trong ngay'),
  );
  
  return $form;
}

function _report_rainfall_form(){
  $form['selectReport'] = array(
    '#type' => 'select',
    '#title' => t('Chọn loại hình báo cáo: '),
    '#options' => array(
      0 => t('Báo cáo số liệu mưa theo mẫu báo cáo BKt-5'),
      1 => t('Báo cáo số liệu mưa theo mẫu báo cáo BKt-14'),
     ),
  );
  $form['selectArea'] = array(
    '#type' => 'select',
    '#title' => t('Chọn khu vực: '),
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
    ),
  );
   
  $form['selectProvince'] = array(
     '#type' => 'select',
     '#title' => t('Chọn Tỉnh/ Thành phố: '),
     '#options' => array(
        0 => t('No'),
       1 => t('Yes'),
     ),
  ); 
   
  $form['selectStation'] = array(
     '#type' => 'select',
     '#title' => t('Chọn trạm: '),
     '#options' => array(
        0 => t('Tất cả các trạm'),
       1 => t('Kỳ Trinh'),
     ),
  );         
  
  $form['txtNameQTV'] = array(
     '#type' => 'textfield',
     '#title' => t('Họ tên quan trắc viên: '),
  );  
  
  $form['txtNameNLB'] = array(
     '#type' => 'textfield',
     '#title' => t('Họ tên người lập bảng: '),
  );    
  
  $form['txtNameKS'] = array(
     '#type' => 'textfield',
     '#title' => t('Họ tên người kiểm soát: '),
  );    
  
  $form['txtNamePT'] = array(
     '#type' => 'textfield',
     '#title' => t('Họ tên người phúc thẩm: '),
  );
  
  $form['submit'] = array(
     '#type' => 'submit',
     '#value' => t('Xuất báo cáo: '),
  );    
  
  return $form;
}

function _init_rainfall_node($title, $time, $rainfall, $stationCode) {
  $node = new stdClass();
  $node->title = $title;
  $node->type = "rainfall";
  $node->created = time();
  $node->changed = $node->created;
  $node->status = 1; // Published?
  $node->promote = 0; // Display on front page?
  $node->sticky = 0; // Display top of page?
  $node->format = 1; // Filtered HTML?
  $node->uid = 1; // Content owner uid (author)?
  $node->language = "und";

  node_object_prepare($node);
  $node->field_rainfall_obsrp[$node->language][0]["value"] = $time;
  $node->field_rainfall_rp[$node->language][0]["value"] = $rainfall;
  $node->field_station_code[$node->language][0]["value"] = $stationCode;  

  $node = node_submit($node);
  node_save($node);
}

function _insert_rainfall_nodes() {
  // for ($i = 1; $i < 500; $i ++) {
  // _init_rainfall_node("Lượng mưa - " . date('d/m/Y'), 
                      // 10,
                      // mt_rand(0,2),
                      // mt_rand(0.1, 226));
  // }
  return "Hoàn thành tạo dữ liệu mưa";

}

/**
*begin: 10-09-12
*/

// function _datalogger_menu_access_callback($permission, $node) {
  // //dpm($permission);
  // //dpm($node);
  
  // return user_access($permission) && $node->type == 'station';
// }

// function _datalogger_station_title_callback($node) {
  // if ($node->type == 'station') {
    // return 'Thông tin trạm';
  // }
  // else {
    // return 'View';
  // }
// }

/**
*begin: 09-09-12
*/

function _manage_data(){
    return 'Quản lý dữ liệu';
}

function _manage_statistics_form() {
  $nid = intval(arg(1));
  $node = node_load($nid);
  drupal_set_title('Trạm đo mưa: '.$node->title);
  $form['tieude'] = array(
    '#type' => 'item',
    '#title' => t('Thống kê khối lượng mưa ngày: ').date('d:m:Y'),
  );
  $form['ao'] = array(
    '#type' => 'item',
    '#title' => t('Tổng lượng mưa quan trắc gần nhất:0.4mm'),
  );$form['bo'] = array(
    '#type' => 'item',
    '#title' => t('Tổng lượng mưa từ 19h đến thời điểm hiện tại:1.7mm'),
  );
  $nid = intval(arg(1));
  $node = node_load($nid);
  drupal_set_title('Trạm đo mưa: '.$node->title);
  $headers = array(
    1 => 'Thời điểm',
    2 => 'ObsRp (phút)',
    3 => 'Rp (mm)',
  );
  
  $rows = array(
    array('18/08/2012 16:16:00','1','0,8'),    
    array('18/08/2012 16:17:00','1','0,8'),    
    array('18/08/2012 16:18:00','1','0,8'),    
    array('18/08/2012 16:19:00','1','0,8'),    
    array('18/08/2012 16:20:00','1','0,8'),    
    array('18/08/2012 16:21:00','1','0,8'),     
  );
  
  $form['table'] = array(
    '#theme' => 'table',
    '#header' => $headers,
    '#rows' => $rows,
    '#empty' => t('Hiện tại không có thông tin trong ngay'),
  );
  
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Tổng lượng mưa: 1,7mm'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Xuất dữ liệu'),
  );
  return $form;
}
function _manage_chart_form() {
  $nid = intval(arg(1));
  $node = node_load($nid);
  drupal_set_title('Trạm đo mưa: '.$node->title);
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Biểu đồ lượng mưa theo giờ'),
  );
  $nid = intval(arg(1));
  $node = node_load($nid);
  drupal_set_title('Trạm đo mưa: '.$node->title);
  $headers = array(
    1 => 'Thời điểm',
    2 => 'ObsRp (phút)',
    3 => 'Rp (mm)',
  );
  
  $rows = array(
    array('18/08/2012 16:16:00','1','0,8'),    
    array('18/08/2012 16:17:00','1','0,8'),    
    array('18/08/2012 16:18:00','1','0,8'),    
    array('18/08/2012 16:19:00','1','0,8'),    
    array('18/08/2012 16:20:00','1','0,8'),    
    array('18/08/2012 16:21:00','1','0,8'),    
    array('18/08/2012 16:22:00','1','0,8'),    
    array('18/08/2012 16:23:00','1','0,8'),    
    array('18/08/2012 16:24:00','1','0,8'),    
    array('18/08/2012 16:25:00','1','0,8'),    
  );
  
  $form['table'] = array(
    '#theme' => 'table',
    '#header' => $headers,
    '#rows' => $rows,
    '#empty' => t('Hiện tại không có thông tin trong ngay'),
  );
  
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Tổng lượng mưa: 1,7mm'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Xuất dữ liệu'),
  );
  return $form;
}
function _manage_rainfall_form($form, &$form_state) {
  // $node = node_load($nid);
  $nid = intval(arg(1));
  $node = node_load($nid);
  drupal_set_title('Trạm đo mưa: '.$node->title);
  $headers = array(
    1 => 'Thời điểm',
    2 => 'ObsRp (phút)',
    3 => 'Rp (mm)',
  );
  
  $rows = array(
    array('18/08/2012 16:16:00','1','0,8'),    
    array('18/08/2012 16:17:00','1','0,8'),    
    array('18/08/2012 16:18:00','1','0,8'),    
    array('18/08/2012 16:19:00','1','0,8'),      
  );
  
  $form['table'] = array(
    '#theme' => 'table',
    '#header' => $headers,
    '#rows' => $rows,
    '#empty' => t('Hiện tại không có thông tin trong ngay'),
  );
  
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Tổng lượng mưa: 1,7mm'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Xuất dữ liệu'),
  );
  return $form;
}
function _manage_info_form() {
  // $node = node_load($nid);
  $nid = intval(arg(1));
  $node = node_load($nid);
  drupal_set_title('Trạm đo mưa: '.$node->title);
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Thông tin tram'),
  );
  
  return $form;
}

/**
*begin: 08 - 08 - 2012
*/

function _datalogger_init_node($title, $field_station_code,
    $field_station_sim_number, $field_station_address, $field_station_longitude,
    $field_station_latitude, $field_station_password,
    $field_station_transmission_speed, $field_station_power,
    $field_station_diagnostic_error) {
  $node = new stdClass();
  $node->title = $title;
  $node->type = "station";
  $node->created = time();
  $node->changed = $node->created;
  $node->status = 1; // Published?
  $node->promote = 0; // Display on front page?
  $node->sticky = 0; // Display top of page?
  $node->format = 1; // Filtered HTML?
  $node->uid = 1; // Content owner uid (author)?
  $node->language = "und";

  node_object_prepare($node);
  $node->field_station_code[$node->language][0]["value"] = $field_station_code;
  $node->field_station_address[$node->language][0]["value"] = $field_station_address;
  $node->field_station_diagnostic_error[$node->language][0]["value"] = $field_station_diagnostic_error;
  $node->field_station_latitude[$node->language][0]["value"] = $field_station_latitude;
  $node->field_station_longitude[$node->language][0]["value"] = $field_station_longitude;
  $node->field_station_password[$node->language][0]["value"] = $field_station_password;
  $node->field_station_power[$node->language][0]["value"] = $field_station_power;
  $node->field_station_sim_number[$node->language][0]["value"] = $field_station_sim_number;
  $node->field_station_transmission_speed[$node->language][0]["value"] = $field_station_transmission_speed;

  $node = node_submit($node);
  node_save($node);
}

function _log_init_node($title, $event) {
  $node = new stdClass();
  $node->title = $title;
  $node->type = "log";
  $node->created = time();
  $node->changed = $node->created;
  $node->status = 1; // Published?
  $node->promote = 0; // Display on front page?
  $node->sticky = 0; // Display top of page?
  $node->format = 1; // Filtered HTML?
  $node->uid = 1; // Content owner uid (author)?
  $node->language = "und";

  node_object_prepare($node);
  // $node->field_[$node->language][0]["value"] = $body;
  $node->field_event_type[$node->language][0]["value"] = $event;

  $node = node_submit($node);
  node_save($node);

}

function _datalogger_nodes() {
  // for ($i = 1; $i < 227; $i ++) {
  // _datalogger_init_node("Station - " . $i, "Code - " . $i, "Address - " . $i,
  // 1, $i, $i,
  // "Password" . $i, $i, "0168123456" . (78 + $i), $i);
  // }
  return "Finished Create Stations.";

}

function _log_nodes() {
  // for ($i = 1; $i < 10; $i ++) {
  // // _log_init_node("Log - ".$i,"Description - ".$i,"Event type - ".$i);
  // _log_init_node("Log - ".$i,"Set Auto Power Management Nable");
  // }
  return "Finished Create Logs.";

}

function _command_form($form, &$form_state) {
  $options_commands = array(
    //Data call command
    1 => t('Real Data Call'),
    2 => t('Save Data Call'),
    //Date and Time Set
    3 => t('Date $ Time Set'),
    4 => t('GPRS Network Time Synchronization'),
    //ID $ Password Set
    5 => t('Set ID'),
    6 => t('Get ID'),
    7 => t('Set Password'),
    8 => t('Get Password'),
    //database Buffer Clear
    9 => t('All Database Buffer Clear'),
    10 => t('Specific Date Database Buffer Clear'),
    //Rain fall config
    11 => t('Accumulated Rain Fall Value Set'),
    12 => t('Set Rain Fall Clear Time'),
    13 => t('Get Rain Fall Clear Time'),
    //Datalogger config
    14 => t('Self Power Reset'),
    15 => t('Set Active / De-Active Battery Power Voltage'),
    16 => t('Get Active / De-Active Battery Power Voltage'),
    17 => t('Set Battery Voltage Offset'),
    18 => t('Get Battery Voltage Offset'),
    19 => t('Set Auto Power Management Enable'),
    20 => t('Set Auto Power Management Disable'),
    21 => t('Get Auto Power Management Enable / Disable'),
    22 => t('Go To Sleep Mode'),
    //Communication setting
    23 => t('Set Data Send Interval Minutes'),
    24 => t('Get Data Send Interval Minutes'),
    25 => t('Set Communication Type GSM'),
    26 => t('Set Communication Type GPRS'),
    27 => t('Set Communication Type Auto'),
    28 => t('Get Communication Type'),
    //GPRS network setting
    29 => t('Set GPRS Network Setting'),
    30 => t('Get GPRS Network Setting'),
    31 => t('Set Host Network Infomation'),
    32 => t('Get Host Network Infomation'),
    33 => t('Set Host Phone Number'),
    34 => t('Get Host Phone Number'),
    //Get datalogger firmware version
    35 => t('Get Datalogger Firmware Version'),
  );

  $default = !empty($form_state['values']['command_selects']) ? $form_state['values']['command_selects'] : 1;
  switch ($form_state["values"]["command_selects"]) {
    //Data call command
    case 1 :
      $title =  t('Real Data Call');
      break;
    case 2 :
      $title =  t('Save Data Call');
      break;
    //Date and Time Set
    case 3 : 
      $title =  t('Date $ Time Set');
      break;
    case 4 : 
      $title =  t('GPRS Network Time Synchronization');
      break;
    //ID $ Password Set
    case 5 :
      $title =  t('Set ID');
      break;
    case 6 :
      $title =  t('Get ID');
      break;
    case 7 :
      $title =  t('Set Password');
      break;
    case 8 :
      $title =  t('Get Password');
      break;
    //database Buffer Clear
    case 9 :
      $title =  t('All Database Buffer Clear');
      break;
    case 10 :
      $title =  t('Specific Date Database Buffer Clear');
      break;
    //Rain fall config
    case 11 :
      $title =  t('Accumulated Rain Fall Value Set');
      break;
    case 12 :
      $title =  t('Set Rain Fall Clear Time');
      break;
    case 13 :
      $title =  t('Get Rain Fall Clear Time');
      break;
    //Datalogger config
    case 14 :
      $title =  t('Self Power Reset');
      break;
    case 15 :
      $title =  t('Set Active / De-Active Battery Power Voltage');
      break;
    case 16 :
      $title =  t('Get Active / De-Active Battery Power Voltage');
      break;
    case 17 :
      $title =  t('Set Battery Voltage Offset');
      break;
    case 18 :
      $title =  t('Get Battery Voltage Offset');
      break;
    case 19 :
      $title =  t('Set Auto Power Management Enable');
      break;
    case 20 :
      $title =  t('Set Auto Power Management Disable');
      break;
    case 21 :
      $title =  t('Get Auto Power Management Enable / Disable');
      break;
    case 22 :
      $title =  t('Go To Sleep Mode');
      break;
    //Comunication setting
    case 23 :
      $title =  t('Set Data Send Interval Minutes');
      break;
    case 24 :
      $title =  t('Get Data Send Interval Minutes');
      break;
    case 25 :
      $title =  t('Set Communication Type GSM');
      break;
    case 26 :
      $title =  t('Set Communication Type GPRS');
      break;
    case 27 :
      $title =  t('Set Communication Type Auto');
      break;
    case 28 :
      $title =  t('Get Communication Type');
      break;
    //GPRS network setting
    case 29 :
      $title =  t('Set GPRS Network Setting');
      break;
    case 30 :
      $title =  t('Get GPRS Network Setting');
      break;
    case 31 :
      $title =  t('Set Host Network Infomation');
      break;
    case 32 :
      $title =  t('Get Host Network Infomation');
      break;
    case 33 :
      $title =  t('Set Host Phone Number');
      break;
    case 34 :
      $title =  t('Get Host Phone Number');
      break;
    //Get datalogger firmware version
    case 35 :
      $title =  t('Get Datalogger Firmware Version');
      break;
    default:
       $title =  t('Real Data Call');
  }   
 
  $form['command_selects'] = array(
    "#type" => "select",
    "#title" => t("Command"),
    '#options' => $options_commands,
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => '_command_callback',
      'wrapper' => '_command-div',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  
  $form['command_fieldset'] = array(
    '#title' => t("Parameter of ". $title),
    '#prefix' => '<div id="_command-div">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
  );

  $num__command = !empty($form_state['values']['command_selects']) ? $form_state['values']['command_selects'] : 1;
  
  switch ($num__command) {
    //Data call command
    case 1 :     
      break;
    case 2 :
      $form['command_fieldset']['description'] = array(
        '#type' => 'item',
        // '#title' => 'a',
        '#description' => t('<b>Khoảng thời gian không được cách nhau quá 24h</b>'),
      );
      $form['command_fieldset']['date_time_from']= array(
        '#type' => 'date_popup',
        '#title' => 'Từ Ngày', 
        '#date_format' => 'd/m/Y H:i:s', 
        '#default_value' => date('d/m/Y H:i:s', $_SERVER['REQUEST_TIME']),
        '#required' => TRUE,
      );
      
      $form['command_fieldset']['date_time_to']= array(
        '#type' => 'date_popup',
        '#title' => 'Tới Ngày', 
        '#date_format' => 'd/m/Y H:i:s', 
        '#default_value' => date('d/m/Y H:i:s', $_SERVER['REQUEST_TIME']),    
        '#required' => TRUE,
      );
      break;
    case 3 : 
      $form['command_fieldset']['date_time_set']= array(
      '#type' => 'date_popup',
      '#title' => 'Date $ Time', 
      '#date_format' => 'd/m/Y H:i:s',      
      );
      break;
    case 4 : 
      break;
    //ID $ Password Set
    case 5 :
      $form['command_fieldset']['set_input_id']= array(
      '#type' => 'textfield',
      '#title' => 'ID',
      '#maxlength' => '6',
      '#default_value' => '123456',
      '#required' => TRUE,
      );
      break;
    case 6 :
      break;
    case 7 :
      $form['command_fieldset']['set_pass'] = array(
        '#type' => 'password_confirm', 
        '#size' => 25,
        '#required' => TRUE,
      );
      break;
    case 8 :
      break;
    //database Buffer Clear
    case 9 :
      break;
    case 10 :
      $form['command_fieldset']['date_buffer_clear']= array(
      '#type' => 'date_popup',
      '#date_format' => 'd/m/Y',
      );
      break;
    //Rain fall config
    case 11 :
      // $title =  t('Accumulated Rain Fall Value Set');
      $form['command_fieldset']['accumulated_rain_fall']= array(
      '#type' => 'textfield',
      '#title' => t('Accumulated Rain Fall Value'),
      '#default_value' => '100',
      '#maxlength' => '5',
      '#required' => TRUE,
      );
      break;
    case 12 :
      // $title =  t('Set Rain Fall Clear Time');
      $form['command_fieldset']['set_rain_fall_clear_time']= array(
      '#type' => 'date_popup',
      '#date_format' => 'd:m:Y H:i',
      );
      break;
    case 13 :
      // $title =  t('Get Rain Fall Clear Time');
      break;
    //Datalogger config
    case 14 :
      // $title =  t('Self Power Reset');
      break;
    case 15 :
      // $title =  t('Set Active / De-Active Battery Power Voltage');
      $form['command_fieldset']['bat_on']= array(
      '#type' => 'textfield',
      '#title' => 'Active Battery Power Voltage (V)',
      '#default_value' => 0011.0,
      '#maxlength' => 5,
      '#description' => t('Dạng phải nhập: xxx.x'),
      '#required' => TRUE,
      );
      $form['command_fieldset']['bat_off']= array(
      '#type' => 'textfield',
      '#title' => 'De-Active Battery Power Voltage (V)',
      '#default_value' => 0013.0,
      '#maxlength' => 5,
      '#description' => t('Dạng phải nhập: xxx.x'),
      '#required' => TRUE,
      );
      break;
    case 16 :
      // $title =  t('Get Active / De-Active Battery Power Voltage');
      break;
    case 17 :
      // $title =  t('Set Battery Voltage Offset');
      $form['command_fieldset']['set_bat_vol']= array(
      '#type' => 'textfield',
      '#title' => 'Battery Voltage Offset (V)',
      '#default_value' => 1.5,
      '#maxlength' => 5,
      '#description' => t('Dạng phải nhập: xx.x'),
      '#required' => TRUE,
      );
      break;
    case 18 :
      // $title =  t('Get Battery Voltage Offset');
      $form['command_fieldset']['get_bat_vol']= array(
      '#type' => 'textfield',
      '#title' => 'Battery Voltage Offset (V)',
      '#default_value' => 1.5,
      '#maxlength' => 5,
      '#description' => t('Dạng phải nhập: xx.x'),
      '#required' => TRUE,
      );
      break;
    case 19 :
      // $title =  t('Set Auto Power Management Enable');
      break;
    case 20 :
      // $title =  t('Set Auto Power Management Disable');
      break;
    case 21 :
      // $title =  t('Get Auto Power Management Enable / Disable');
      break;
    case 22 :
      // $title =  t('Go To Sleep Mode');
      break;
    //Comunication setting
    case 23 :
      // $title =  t('Set Data Send Interval Minutes');
      $form['command_fieldset']['set_interval']= array(
      '#type' => 'textfield',
      '#title' => 'Data Send Interval Minutes',
      '#default_value' => 10,
      '#maxlength' => 5,
      '#required' => TRUE,
      );
      break;
    case 24 :
      // $title =  t('Get Data Send Interval Minutes');
      break;
    case 25 :
      // $title =  t('Set Communication Type GSM');
      break;
    case 26 :
      // $title =  t('Set Communication Type GPRS');
      break;
    case 27 :
      // $title =  t('Set Communication Type Auto');
      break;
    case 28 :
      // $title =  t('Get Communication Type');
      break;
    //GPRS network setting
    case 29 :
      // $title =  t('Set GPRS Network Setting');
      $form['command_fieldset']['host_gprs']= array(
        '#type' => 'textfield',
        '#title' => 'Host',
        '#default_value' => '192.168.151.255',
        '#maxlength' => 15,
        '#required' => true,
      );
      
      $form['command_fieldset']['id_gprs']= array(
        '#type' => 'textfield',
        '#title' => 'ID',
        '#default_value' => 123456,
        '#maxlength' => 6,
        '#required' => true,
      );
      $form['command_fieldset']['pass_gprs'] = array(
        '#type' => 'password_confirm',
        '#maxlength' => 25,
        '#required' => true,
      );
      break;
    case 30 :
      // $title =  t('Get GPRS Network Setting');
      break;
    case 31 :
      // $title =  t('Set Host Network Infomation');
      $form['command_fieldset']['set_host']= array(
      '#type' => 'textfield',
      '#title' => 'Host',
      '#default_value' => '192.168.151.255',
      '#maxlength' => 15,
      '#required' => true,
      );
      
      $form['command_fieldset']['set_port']= array(
      '#type' => 'textfield',
      '#title' => 'Port',
      '#default_value' => 8000,
      '#maxlength' => 6,
      '#required' => true,
      );    
      break;
    case 32 :
      // $title =  t('Get Host Network Infomation');
      break;
    case 33 :
      // $title =  t('Set Host Phone Number');
      $form['command_fieldset']['host_phone']= array(
      '#type' => 'textfield',
      '#title' => 'Host Phone Number',
      '#default_value' => '800010001',
      '#maxlength' => 15,
      '#required' => true,
      );
      break;
    case 34 :
      // $title =  t('Get Host Phone Number');
      break;
    //Get datalogger firmware version
    case 35 :
      // $title =  t('Get Datalogger Firmware Version');
      break;
  }
  
  $form["submit"] = array(
      "#type" => "submit",
      "#value" => t("Send Now!"),
      "#submit" => array(
          "_send_command_submit"
      )
  );

  $form['#validate'][] = '_command_validate';
  
  return $form;
}

function _command_callback($form, &$form_state) {
  return $form['command_fieldset'];
}

function _command_validate($form, &$form_state) {
  switch ($form_state["values"]["command_selects"]) {
    case 2 :
      $dt_from = $form_state['values']['date_time_from'];
      $dt_to = $form_state['values']['date_time_to'];
      $interval = (strtotime($dt_to) - strtotime($dt_from))/(24*60*60);
      if($interval < 0) {
        form_set_error('command_fieldset[date_time_to]',t("Thời gian <b>Tới ngày</b> không được nhỏ hơn <b>Từ ngày</b>"));
      }
      else{
        if($interval > 1) {
          form_set_error('command_fieldset[date_time_to]',t("Thời gian <b>Tới ngày</b> không được lớn hơn <b>Từ ngày</b> quá 24h"));
        }
      }
      break;
    //Date and Time Set
    case 3 : 
      break;
    case 4 : 
      break;
    //ID $ Password Set
    case 5 :
      $id = $form_state['values']['set_input_id'];
      if (preg_match('/[^a-zA-Z0-9]/i',$id)){
         form_set_error('command_fieldset[set_input_id]',t('Trường <b>ID</b> không được chứa kí tự đặc biệt.<br>Chỉ được chứa chữ cái, và số'));
      }
      else{
        if(strlen($id) != 6) {
          form_set_error('command_fieldset[set_input_id]',t('Trường <b>ID</b> không đúng định dạng.Bắt buộc phải chứa 6 kí tự'));
        }
      }
      break;
    case 6 :
      break;
    case 7 :
      break;
    case 8 :
      break;
    //database Buffer Clear
    case 9 :
      break;
    case 10 :
      break;
    //Rain fall config
    case 11 :
    // ['command_fieldset']['accumulated_rain_fall']
      $number = $form_state['values']['accumulated_rain_fall'];
      if(empty($number)){
        form_set_error('command_fieldset[accumulated_rain_fall]',t('Trường <b>').t('Accumulated Rain Fall Value').t('</b> không được để trống'));
      }
      else{
        if(($number%10) != 0){
          form_set_error('command_fieldset[accumulated_rain_fall]',t('Giá trị trường <b>').t('Accumulated Rain Fall Value').t('</b> phải là bội của 10'));
        }
      }
      break;
    case 12 :
      break;
    case 13 :
      break;
    //Datalogger config
    case 14 :
      break;
    case 15 :
      // $title =  t('Set Active / De-Active Battery Power Voltage');
      $batOn = $form_state['values']['bat_on'];
      $batOff = $form_state['values']['bat_off'];
      
      if(empty($batOn)){
        form_set_error('command_fieldset[bat_on]',t('Trường <b>').t('Active Battery Power Voltage (V)').t('</b> không được để trống'));
      }
      else if (preg_match('/[^0-9.]/i',$batOn)){
         form_set_error('command_fieldset[bat_on]',t('Trường <b>').t('Active Battery Power Voltage (V)').t('</b> chỉ được chứa số.'));
      }
      
      if(empty($batOff)){
        form_set_error('command_fieldset[bat_on]',t('Trường <b>').t('De-Active Battery Power Voltage (V)').t('</b> không được để trống'));
      }
      else if (preg_match('/[^0-9.]/i',$batOff)){
         form_set_error('command_fieldset[bat_off]',t('Trường <b>').t('De-Active Battery Power Voltage (V)').t('</b> chỉ được chứa số.'));
      }
      break;
    case 16 :
      // $title =  t('Get Active / De-Active Battery Power Voltage');
      break;
    case 17 :
      // $title =  t('Set Battery Voltage Offset');   
      // set_bat_vol
      $vol = $form_state['values']['set_bat_vol'];
      if(empty($vol)){
        form_set_error('command_fieldset[set_bat_vol]',t('Trường <b>').t('Battery Voltage Offset (V)').t('</b> không được để trống.'));
      }
      // else if (preg_match('/[^0-9{1,2}.?0-9$/i',$vol)){
         // form_set_error('command_fieldset[set_bat_vol]',t('Trường <b>').t('Battery Voltage Offset (V)').t('</b> không đúng định dạng.'));
      // }
      break;
    case 18 :
      $vol = $form_state['values']['get_bat_vol'];
      if(empty($vol)){
        form_set_error('command_fieldset[get_bat_vol]',t('Trường <b>').t('Battery Voltage Offset (V)').t('</b> không được để trống.'));
      }
      break;
    case 19 :
      // $title =  t('Set Auto Power Management Enable');
      break;
    case 20 :
      // $title =  t('Set Auto Power Management Disable');
      break;
    case 21 :
      // $title =  t('Get Auto Power Management Enable / Disable');
      break;
    case 22 :
      // $title =  t('Go To Sleep Mode');
      break;
    //Comunication setting
    case 23 :
      // $title =  t('Set Data Send Interval Minutes');
      $interval = $form_state['values']['set_interval'];
      if(empty($interval)){
        form_set_error('command_fieldset[set_interval]',t('Trường <b>').t('Data Send Interval Minutes').t('</b> không được để trống.'));
      }
      else{
        if($interval > 60 || $interval < 0){
          form_set_error('command_fieldset[set_interval]',t('Trường <b>').t('Data Send Interval Minutes').t('</b> không được đặt lớn hơn 60.'));
        }
      }
      break;
    case 24 :
      // $title =  t('Get Data Send Interval Minutes');
      break;
    case 25 :
      // $title =  t('Set Communication Type GSM');      
      break;
    case 26 :
      // $title =  t('Set Communication Type GPRS');
      break;
    case 27 :
      // $title =  t('Set Communication Type Auto');
      break;
    case 28 :
      // $title =  t('Get Communication Type');
      break;
    //GPRS network setting
    case 29 :
      // $title =  t('Set GPRS Network Setting');
      $host = $form_state['values']['host_gprs'];
      if(empty($host)){
        form_set_error('command_fieldset[id_gprs]',t('Trường <b>').t('Host').t('</b> không được để trống.'));
      }
      $id = $form_state['values']['id_gprs'];
      if(empty($id)){
        form_set_error('command_fieldset[id_gprs]',t('Trường <b>').t('ID').t('</b> không được để trống.'));
      }
      break;
    case 30 :
      // $title =  t('Get GPRS Network Setting');
      break;
    case 31 :
      break;
    case 32 :
      // $title =  t('Get Host Network Infomation');
      break;
    case 33 :
      // $title =  t('Set Host Phone Number');
      $host = $form_state['values']['host_phone'];
      if(empty($host)){
        form_set_error('command_fieldset[host_phone]',t('Trường <b>').t('Host Phone Number').t('</b> không được để trống.'));
      }
      break;
    case 34 :
      // $title =  t('Get Host Phone Number');
      break;
    //Get datalogger firmware version
    case 35 :
      // $title =  t('Get Datalogger Firmware Version');
      break;
  }
}

function _send_command_submit($form, &$form_state) {
  define('DT', date('ymdHis',time()));  
  define('DT2', date('ymdHi',time()));  
  define('DT3', date('YmdHi',time()));  
  $nid = intval(arg(1)) ? intval(arg(1)) : $form_state['values']['nid'];
  
  if($nid) {  
    $node = node_load($nid);
    // dsm($node);
    $id = $node->field_station_code['und']['0']['value'];
    $phone = $node->field_station_sim_number['und']['0']['value'];
    // dsm($phone);
    define('ID',$id);
    define('PHONE',$phone);
  }
    
  $form['nid'] = array(
    '#type' => 'hidden', 
    '#value' => $nid,
  );
  
  switch ($form_state["values"]["command_selects"]) {
    //Data call command
    case 1 :
      // $message = $form_state['complete form']['command_fieldset']['real_data_call']['#markup'];
      $message = 'HS'.ID.'GET   '.DT.'S:STATUS                                                      xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 2 :
      $dt_from = $form_state['values']['date_time_from'];
      $from = _convert_strdate_to_date('ymdHis',$dt_from);
      $dt_to = $form_state['values']['date_time_to'];
      $to = _convert_strdate_to_date('ymdHis',$dt_to);
      $message = 'HS'.ID.'GET  '.DT.'I:'.$from.'~'.$to.'                                   xx;';
      _insert_outbox(PHONE, $message);
      break;
    //Date and Time Set
    case 3 : 
      $date = _convert_strdate_to_date($strFormat = 'Ymdhis', $form_state['values']['date_time_set']);
      $message = 'HS'.ID.'SET  '.DT.'T:'.$date.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 4 : 
      // $title =  t('GPRS Network Time Synchronization');
      $message = 'HS'.ID.'SET  '.DT.'T:NITZ                                                        xx;';
      _insert_outbox(PHONE, $message);
      break;
    //ID $ Password Set
    case 5 :
      // $title =  t('Set ID');
      $id = $form_state['values']['set_input_id'];
      $message = 'HS'.ID.'SET  '.DT.'D:'.$id.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 6 :
      // $title =  t('Get ID');
      $message = 'HS'.ID.'GET  '.DT.'D:?                                                           xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 7 :
      $pass = $form_state['values']['set_pass'];
      $message = 'HS'.ID.'SET '.DT.'P:'.$pass.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 8 :
      // $title =  t('Get Password');
      $message = 'HS'.ID.'GET  '.DT.'P:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    //database Buffer Clear
    case 9 :
      // $title =  t('All Database Buffer Clear');
      $message = 'HS'.ID.'SET '.DT.'R:FORMAT_ALL                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 10 :
      // $title =  t('Specific Date Database Buffer Clear');
      $day = _convert_strdate_to_date('ymd',$form_state['values']['date_buffer_clear']);
      $message = 'HS'.ID.'SET '.DT.'R:FORMAT_DAY:'.$day.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    //Rain fall config
    case 11 :
      // $title =  t('Accumulated Rain Fall Value Set');
      $number = $form_state['values']['accumulated_rain_fall'];
      $message = 'HS'.ID.'SET '.DT.'R:SET:'.$number.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 12 :
      // $title =  t('Set Rain Fall Clear Time');
      $time = _convert_strdate_to_date('Hi',$form_state['values']['set_rain_fall_clear_time']);
      $message = 'HS'.ID.'SET '.DT.'R:CLEAR:'.$time.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 13 :
      // $title =  t('Get Rain Fall Clear Time');
      $message = 'HS'.ID.'GET  '.DT.'R:CLEAR:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    //Datalogger config
    case 14 :
      // $title =  t('Self Power Reset');
      $message = 'HS'.ID.'SET '.DT.'P:RESET                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 15 :
      // $title =  t('Set Active / De-Active Battery Power Voltage');
      $batOn = $form_state['values']['bat_on'];
      // dsm($batOn);
      $batOff = $form_state['values']['bat_off'];
      // dsm($batOff);
      $message = 'HS'.ID.'SET '.DT.'P:BAT_ON'.$batOn.'V,_OFF:'.$batOff.'V                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 16 :
      // $title =  t('Get Active / De-Active Battery Power Voltage');
      $message = 'HS'.ID.'GET  '.DT.'P:BAT_ON:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 17 :
      // $title =  t('Set Battery Voltage Offset');
      $vol = $form_state['values']['set_bat_vol'];
      $message = 'HS'.ID.'SET '.DT.'P:BAT_OFFSET:+'.$vol.'V                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 18 :
      // $title =  t('Get Battery Voltage Offset');
      $vol = $form_state['values']['get_bat_vol'];
      $message = 'HS'.ID.'GET  '.DT.'P:BAT_OFFSET:+'.$vol.'V                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 19 :
      // $title =  t('Set Auto Power Management Enable');
      $message = 'HS'.ID.'SET '.DT.'P:AUTO_PWR_MANAGEMENT:ON                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 20 :
      // $title =  t('Set Auto Power Management Disable');
      $message = 'HS'.ID.'SET '.DT.'P:AUTO_PWR_MANAGEMENT:OFF                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 21 :
      // $title =  t('Get Auto Power Management Enable / Disable');
      $message = 'HS'.ID.'GET  '.DT.'P:AUTO_PWR_MANAGEMENT:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 22 :
      // $title =  t('Go To Sleep Mode');
      $message = 'HS'.ID.'SET '.DT.'P:GOTO_SLEEP_MODE                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    //Comunication setting
    case 23 :
      // $title =  t('Set Data Send Interval Minutes');
      $interval = $form_state['values']['set_interval'];
      $message = 'HS'.ID.'SET '.DT.'C:INTERVAL: '.$interval.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 24 :
      // $title =  t('Get Data Send Interval Minutes');
      $message =  'HS'.ID.'GET  '.DT.'C:INTERVAL:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 25 :
      // $title =  t('Set Communication Type GSM');
      $message = 'HS'.ID.'SET '.DT.'C:COMM:GSM                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 26 :
      // $title =  t('Set Communication Type GPRS');
      $message = 'HS'.ID.'SET '.DT.'C:COMM:GPRS                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 27 :
      // $title =  t('Set Communication Type Auto');
      $message = 'HS'.ID.'SET '.DT.'C:COMM:AUTO                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 28 :
      // $title =  t('Get Communication Type');     
      $message = 'HS'.ID.'GET  '.DT.'C:COMM:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    //GPRS network setting
    case 29 :
      // $title =  t('Set GPRS Network Setting');
      $host = $form_state['values']['host_gprs'];
      $id = $form_state['values']['id_gprs'];
      $pass = $form_state['values']['pass_gprs'];
      $message = 'HS'.ID.'SET '.DT.'G:APN'.$host.'ID:'.$id.'PW:'.$pass.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 30 :
      // $title =  t('Get GPRS Network Setting');
      $message = 'HS'.ID.'GET  '.DT.'G:APN?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 31 :
      // $title =  t('Set Host Network Infomation');
      $host = $form_state['values']['set_host'];
      $port = $form_state['values']['set_port'];
      $message = 'HS'.ID.'SET '.DT.'N:HOST'.$host.':'.$port.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 32 :
      // $title =  t('Get Host Network Infomation');      
      $message = 'HS'.ID.'GET  '.DT.'N:HOST:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 33 :
      // $title =  t('Set Host Phone Number');
      $sim = $form_state['values']['host_phone'];
      $message = 'HS'.ID.'SET '.DT.'H:HOST_PHONE_NO:+84'.$sim.'                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    case 34 :
      // $title =  t('Get Host Phone Number');
      $message = 'HS'.ID.'SET '.DT.'H:HOST_PHONE_NO:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
    //Get datalogger firmware version
    case 35 :
      // $title =  t('Get Datalogger Firmware Version');
      $message = 'HS'.ID.'SET '.DT.'V:VERSION:?                                                     xx;';
      _insert_outbox(PHONE, $message);
      break;
  }
  drupal_set_message($message.'<br>Gửi lệnh thành công!');
}

// function _datalogger_command_form_ajax_callback($form, $form_state) {
  // return $form["replace_textfield"];
// }

/*
 * Implementation of hook_action_info().
 */

function datalogger_action_info() {
  return array(
    "datalogger_command_action" => array(
      "type" => "comment",
      "label" => t("Send Command Multiple Stations"),
      "configurable" => FALSE,
      "behavior" => array(
        "changes_property"
      ),
      "triggers" => array(
        "comment_presave",
        "comment_insert",
        "comment_update"
      )
    )
  );
}

function datalogger_command_action(){
  // _command_form();
}

// function datalogger_views_data_alter(&$data) {
// // // $view = views_get_view("list_all_datalogger");
// // // switch ($node->language) {
// // // case "en":
// // // $data[$view]['nid']['options']['label'] = array(
// // // "title" => ""
// // // );
// // // $data[$view]['node_title'] = array(
// // // "title" => "No."
// // // );
// // // $data[$view]['nid'] = array(
// // // "title" => "No."
// // // );
// // // break;
// // // case "vi":

// // // break;
// // // }
// dpm($data);
// }
function _view_translate_station() {
  return digipro_views_get_view_result("list_all_datalogger", "page", null,
      true, false);
  // return digipro_views_get_view_result("logs_management", null, null, false,
// false);
}

function _view_translate_log() {
  return digipro_views_get_view_result("logs_management", null, null, true,
      false);

}

function digipro_views_get_view_result($viewname, $display_id = NULL, $args = NULL,
    $content_only = false, $data_only = false) {
  $view = views_get_view($viewname);
  if(is_object($view)) {
    if(is_array($args)) {
      $view->set_arguments($args);
    }

    if(is_string($display_id)) {
      $view->set_display($display_id);
    } else {
      $view->init_display();
    }
    $view->pre_execute();
    $view->execute();
    // dpm($view);
    global $language_content;
    switch ($language_content->language) {
      case "en":
        switch ($view->name) {
          case "logs_management":
            // dpm($view);
            // dpm($view);
            $view->field['title']->options['label'] = 'Name Log';
            $view->field['field_event_type']->options['label'] = 'Event Type';
            $view->field['created']->options['label'] = 'Post Date';
            $view->field['counter']->options['label'] = 'No.';
            break;
          case "list_all_datalogger":
            $view->field['views_bulk_operations']->options['label'] = 'Select';
            $view->field['title']->options['label'] = 'Station Name';
            $view->field['counter']->options['label'] = 'No.';
            $view->field['nid']->options['label'] = 'Send Command';
            break;
        }
        break;
      case "vi":
        break;
    }

    if($data_only)
      return $view;
    $count = $view->total_rows;

    if($content_only)
      return $view->preview();
    else
      return array(
          'count' => $count,
          'content' => $view->preview()
      );
  } else {
    return t('View %viewname not found.', array(
        '%viewname' => $viewname
    ));
  }
}