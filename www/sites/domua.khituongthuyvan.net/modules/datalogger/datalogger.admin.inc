<?php
  
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
    "gprs_network_time_synchronization" => t(
      "GPRS Network Time Synchronization"),
    "date_time_set" => t("Date & Time Set"),
    "set_id" => t("Set ID"),
    "get_id" => t("Get ID"),
    "set_password" => t("Set Password"),
    "get_password" => t("Get Password"),
    "all_database_buffer_clear" => t("All Database Buffer Clear"),
    "specific_date_database_buffer_clear" => t(
      "Specific Date Database Buffer Clear"),
    "accumulated_rain_fall_value_set" => t("Accumulated Rain Fall Value Set"),
    "set_rain_fall_clear_time" => t("Set Rain Fall Clear Time"),
    "get_rain_fall_clear_time" => t("Get Rain Fall Clear Time"),
    "self_power_reset" => t("Self Power Reset"),
    "set_active_deactive_battery_power_volt" => t(
      "Set Active/Deactive Battery Power Volt"),
    "get_active_deactive_battery_power_volt" => t(
      "Get Active/Deactive Battery Power Volt"),
    "set_battery_volt_offset" => t("Set Battery Volt Offset"),
    "get_battery_volt_offset" => t("Get Battery Volt Offset"),
    "set_auto_power_management_nable" => t(
      "Set Auto Power Management Enable/Disable"),
    "get_auto_power_management_nable" => t(
      "Get Auto Power Management Enable/Disable"),
    "goto_sleep_mode" => t("Goto Sleep Mode"),
    "set_data_send_interval_minutes" => t("Set Data Send Interval Minutes"),
    "get_data_send_interval_minutes" => t("Get Data Send Interval Minutes"),
    "set_communication_type" => t("Set Communication Type"),
    "get_communication_type" => t("Get Communication Type"),
    "set_gprs_network_setting" => t("Set GPRS Network Setting"),
    "get_gprs_network_setting" => t("Get GPRS Network Setting"),
    "set_host_netword_information" => t("Set Host Netword Information"),
    "get_host_netword_information" => t("Get Host Netword Information"),
    "set_host_phone_number" => t("Set Host Phone Number"),
    "get_host_phone_number" => t("Get Host Phone Number"),
    "get_data_logger_firmware" => t("Get Data Logger Firmware Version")
  );

  $form["command_selects"] = array(
    "#type" => "select",
    "#title" => t("Command"),
    "#options" => $options_commands,
    "#ajax" => array(
      "callback" => "_datalogger_command_form_ajax_callback",
      "wrapper" => "command_form_replace_textfield_div"
    )
  );

  switch ($form_state["values"]["command_selects"]) {
    case "gprs_network_time_synchronization":
      $title = t("GPRS Network Time Synchronization");
      break;
    case "date_time_set":
      $title = t("Date & Time Set");
      break;
    case "set_id":
      $title = t("Set ID");
      break;
    // case "get_id":
    // $title = t("Get ID");
    // break;
    case "set_password":
      $title = t("Set Password");
      break;
    // case "get_password":
    // $title = t("Get Password");
    // break;
    case "all_database_buffer_clear":
      $title = t("All Database Buffer Clear");
      break;
    case "specific_date_database_buffer_clear":
      $title = t("Specific Date Database Buffer Clear");
      break;
    case "accumulated_rain_fall_value_set":
      $title = t("Accumulated Rain Fall Value Set");
      break;
    // case "set_rain_fall_clear_time" :
    // $title = t("Set Rain Fall Clear Time");
    // break;
    // case "get_rain_fall_clear_time" :
    // $title = t("Get Rain Fall Clear Time");
    // break;
    case "self_power_reset":
      $title = t("Self Power Reset");
      break;
    case "set_active_deactive_battery_power_volt":
      $title = t("Set Active/Deactive Battery Power Volt");
      break;
    // case "get_active_deactive_battery_power_volt":
    // $title = t("Get Active/Deactive Battery Power Volt");
    // break;
    case "set_battery_volt_offset":
      $title = t("Set Battery Volt Offset");
      break;
    // case "get_battery_volt_offset":
    // $title = t("Get Battery Volt Offset");
    // break;
    case "set_auto_power_management_nable":
      $title = t("Set Auto Power Management Enable/Disable");
      break;
    // case "get_auto_power_management_nable":
    // $title = t("Get Auto Power Manager Enable/Disable");
    // break;
    case "goto_sleep_mode":
      $title = t("Goto Sleep Mode");
      break;
    case "set_data_send_interval_minutes":
      $title = t("Set Data Send Interval Minutes");
      break;
    // case "get_data_send_interval_minutes":
    // $title = t("Get Data Send Interval Minutes");
    // break;
    case "set_communication_type":
      $title = t("Set Communication Type");
      break;
    // case "get_communication_type":
    // $title = t("Get Communication Type");
    // break;
    case "set_gprs_network_setting":
      $title = t("Set GPRS Network Setting");
      break;
    // case "get_gprs_network_setting":
    // $title = t("Get GPRS Network Setting");
    // break;
    case "set_host_netword_information":
      $title = t("Set Host Netword Information");
      break;
    // case "get_host_netword_information":
    // $title = t("Get Host netword Information");
    // break;
    // case "get_host_phone_number":
    // $title = t("Get Host Phone Number");
    // break;
    // case "get_data_logger_firmware":
    // $title = t("Get Data Logger Firmware");
    // break;
    case "date_time_set":
      $title = t("Date Time");
      break;
    case "set_host_phone_number":
      $title = t("Host Phone Number");
      break;
    default:
      $title = t("Parameter");
  }

  // This entire form element will be replaced whenever "changethis" is updated.
  $form["replace_textfield"] = array(
      "#type" => "textfield",
      "#title" => t($title),
      // The prefix/suffix provide the div that we"re replacing, named by
      // #ajax["wrapper"] above.
      "#prefix" => "<div id='command_form_replace_textfield_div'>",
      "#suffix" => "</div>"
  );   

  /*
   * $form["host_phone_number"] = array( "#type" => "textfield", "#title" =>
   * t("Host Phone Number"), "#cols" => 30, "#rows" => 1 );
   */

  $form["submit"] = array(
      "#type" => "submit",
      "#value" => t("Send Now!"),
      "#submit" => array(
          "deductible_submit"
      )
  );

  return $form;
}

/**
 * Callback for ajax_example_simplest.
 *
 * On an ajax submit, the form builder function is called again, then the $form
 * and $form_state are passed to this callback function so it can select which
 * portion of the form to send on to the client.
 *
 * @return renderable array (the textfield element)
 */
function _datalogger_command_form_ajax_callback($form, $form_state) {
  // The form has already been submitted and updated. We can return the replaced
  // item as it is.
  $form['set_parameter'] = array(
    '#type' => 'fieldset',
    '#title' => 'Set parameter',
    '#description' => 'Set parameter',
  );
  switch ($form_state["values"]["command_selects"]) {
    case "gprs_network_time_synchronization":
      $title = t("GPRS Network Time Synchronization");
       $form['set_parameter'][''] = array(
    '#type' => 'fieldset',
    '#title' => 'Set parameter',
    '#description' => 'Set parameter',
  );
      break;
    case "date_time_set":
      $title = t("Date & Time Set");
      break;
    case "set_id":
      $title = t("Set ID");
      $form['set_id'] = array(
        '#type' => 'fielset',
        '#title' => $title,
        '#description' => 'Set ID for Station.',        
      );
      
      $form['set_id'] = array(
        '#title' => $title,
        '#type' => 'textfield',
        '#description' => 'Set ID for Station.',        
      );
      return $form;
      break;
    // case "get_id":
    // $title = t("Get ID");
    // break;
    case "set_password":
      $title = t("Set Password");
      break;
    // case "get_password":
    // $title = t("Get Password");
    // break;
    case "all_database_buffer_clear":
      $title = t("All Database Buffer Clear");
      break;
    case "specific_date_database_buffer_clear":
      $title = t("Specific Date Database Buffer Clear");
      break;
    case "accumulated_rain_fall_value_set":
      $title = t("Accumulated Rain Fall Value Set");
      break;
    // case "set_rain_fall_clear_time" :
    // $title = t("Set Rain Fall Clear Time");
    // break;
    // case "get_rain_fall_clear_time" :
    // $title = t("Get Rain Fall Clear Time");
    // break;
    case "self_power_reset":
      $title = t("Self Power Reset");
      break;
    case "set_active_deactive_battery_power_volt":
      $title = t("Set Active/Deactive Battery Power Volt");
      break;
    // case "get_active_deactive_battery_power_volt":
    // $title = t("Get Active/Deactive Battery Power Volt");
    // break;
    case "set_battery_volt_offset":
      $title = t("Set Battery Volt Offset");
      break;
    // case "get_battery_volt_offset":
    // $title = t("Get Battery Volt Offset");
    // break;
    case "set_auto_power_management_nable":
      $title = t("Set Auto Power Management Enable/Disable");
      break;
    // case "get_auto_power_management_nable":
    // $title = t("Get Auto Power Manager Enable/Disable");
    // break;
    case "goto_sleep_mode":
      $title = t("Goto Sleep Mode");
      break;
    case "set_data_send_interval_minutes":
      $title = t("Set Data Send Interval Minutes");
      break;
    // case "get_data_send_interval_minutes":
    // $title = t("Get Data Send Interval Minutes");
    // break;
    case "set_communication_type":
      $title = t("Set Communication Type");
      break;
    // case "get_communication_type":
    // $title = t("Get Communication Type");
    // break;
    case "set_gprs_network_setting":
      $title = t("Set GPRS Network Setting");
      break;
    // case "get_gprs_network_setting":
    // $title = t("Get GPRS Network Setting");
    // break;
    case "set_host_netword_information":
      $title = t("Set Host Netword Information");
      break;
    // case "get_host_netword_information":
    // $title = t("Get Host netword Information");
    // break;
    // case "get_host_phone_number":
    // $title = t("Get Host Phone Number");
    // break;
    // case "get_data_logger_firmware":
    // $title = t("Get Data Logger Firmware");
    // break;
    case "date_time_set":
      $title = t("Date Time");
      break;
    case "set_host_phone_number":
      $title = t("Host Phone Number");
      break;
    default:
      $title = t("Parameter");
  }
  // return $form["replace_textfield"];
}
/*
 * Implementation of hook_action_info().
 */
function datalogger_action_info() {
  dpm('into go');
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
            dpm($view);
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