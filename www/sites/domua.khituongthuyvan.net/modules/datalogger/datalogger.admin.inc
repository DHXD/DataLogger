<?php
$stations = views_get_view_result('list_all_datalogger');
GLOBAL $station_name;
$station_name = array();
foreach($stations as $station){
	$station_name[$station->nid] = $station->node_title;
}
global $timeInterval;
$timeInterval = array('10', '20', '30', '60', '120', '180', '360');

global $clearTime;
$clearTime = array('00:00','01:00','02:00','03:00','04:00','05:00','06:00','07:00','08:00','09:00','10:00','11:00','12:00','13:00','14:00','15:00','16:00','17:00','18:00','19:00','20:00','21:00','22:00','23:00');

global $clearTime2;
$clearTime2 = array('0000','0100','0200','0300','0400','0500','0600','0700','0800','0900','1000','1100','1200','1300','1400','1500','1600','1700','1800','1900','2000','2100','2200','2300');

global $datalogger_pattern;
$datalogger_pattern = array(
		'I:STATUS',
		'S:',
		'T:',
		'T:NITZ',
		'D:',
		//'D:?',
		// 'P:',
		'W:',
		//'P:?',
		'R:FORMAT ALL',
		'R:FORMAT DAY:',
		'R:SET:',
		'R:CLEAR TIME:',
		//'R:CLEAR:?',
		//////'P:RESET', // duplicated
		'P:BAT ON:',
		//'P:BAT ON:?',
		'P:BAT OFFSET:',
		'P:AUTO PWR MANAGEMENT:',
		//'P:AUTO PWR MANAGEMENT:?',
		'P:GOTO SLEEP MODE',
		'C:INTERVAL:',
		//'C:INTERVAL:?',
		'C:COMM:',
		//'C:COMM:?',
		'G:APN:',
		'A:ALARM INTERVAL:',
		//'G:APN:?',
		'N:HOST:',
		//'N:HOST:?',
		'H:HOST PHONE NO:',
		//'H:HOST PHONE NO:?',
		//'V:VERSION:?',
		'V:VERSION:',
		'P:RESET');

	// GLOBAL $options_commands;
	// $options_commands = array(
    // //Data call command
    // 1 => t('Real Data Call'),
    // 2 => t('Save Data Call'),
    // //Date and Time Set
    // 3 => t('Date $ Time Set'),
    // 4 => t('GPRS Network Time Synchronization'),
    // //ID $ Password Set
    // 5 => t('Set ID'),
    // 6 => t('Get ID'),
    // 7 => t('Set Password'),
    // 8 => t('Get Password'),
    // //database Buffer Clear
    // 9 => t('All Database Buffer Clear'),
    // 10 => t('Specific Date Database Buffer Clear'),
    // //Rain fall config
    // 11 => t('Accumulated Rain Fall Value Set'),
    // 12 => t('Set Rain Fall Clear Time'),
    // 13 => t('Get Rain Fall Clear Time'),
    // //Datalogger config
    // 14 => t('Self Power Reset'),
    // 15 => t('Set Active / De-Active Battery Power Voltage'),
    // 16 => t('Get Active / De-Active Battery Power Voltage'),
    // 17 => t('Set Battery Voltage Offset'),
    // 18 => t('Get Battery Voltage Offset'),
    // 19 => t('Set Auto Power Management Enable'),
    // 20 => t('Set Auto Power Management Disable'),
    // 21 => t('Get Auto Power Management Enable / Disable'),
    // 22 => t('Go To Sleep Mode'),
    // //Communication setting
    // 23 => t('Set Data Send Interval Minutes'),
    // 24 => t('Get Data Send Interval Minutes'),
    // 25 => t('Set Communication Type GSM'),
    // 26 => t('Set Communication Type GPRS'),
    // 27 => t('Set Communication Type Auto'),
    // 28 => t('Get Communication Type'),
    // //GPRS network setting
    // 29 => t('Set GPRS Network Setting'),
    // 30 => t('Get GPRS Network Setting'),
    // 31 => t('Set Host Network Infomation'),
    // 32 => t('Get Host Network Infomation'),
    // 33 => t('Set Host Phone Number'),
    // 34 => t('Get Host Phone Number'),
    // //Get datalogger firmware version
    // 35 => t('Get Datalogger Firmware Version'),
		// //Alarm Options
		// 36 => t('Set the Alarm Interval and Level for rainfall alarming'),
		// 37 => t('Get the Alarm Interval and Level for rainfall alarming'),
		// 38 => t('Reset All'),);	

/**
 *Begin: 25/11. 
 *author:hungnm0302
 *Lay ten cac tram do mua theo role khu vuc
 */
function _datalogger_ftp_server(){
	try {
		/*
		$jail = dsm(drupal_realpath('public://'));
		
		$settings['username'] = 'root';
		$settings['password'] = 'root';
		$settings['advanced']['hostname'] = 'localhost';
		$settings['advanced']['port'] = '21';
		*/
		$jail = FTP_JAIL;
		$settings = array(
				// 'username' => FTP_USER,
				// 'password' => FTP_PASS,		
				'username' => 'root',
				'password' => 'root',
				'advanced' => array(
						// 'hostname' => FTP_HOST,
						// 'port' => FTP_PORT,
						'hostname' => 'localhost',
						'port' => '21',
				),
		);
	
		// $ftpserver = FileTransferFTP::factory($jail, $settings);
		$ftpserver = FileTransferFTP::factory($jail, $settings);
		$ftpserver->connect();
		$source = '/shareFile';
		$destination = drupal_realpath('public://shareFile//');
		// $ftpserver->copyDirectory($destination,$source);
		$ftpserver->copyFile($destination.'abc.jpg',$source);
	}
	catch(Exception $e) {
	}
}
 
 /**
 *Begin: 21/11. 
 *author:hungnm0302
 *Lay ten cac tram do mua theo role khu vuc
 */
 
function _datalogger_station_name_list(){
	global $user;
	if (!in_array('administrator', array_values($user->roles)) && !in_array('control datalogger', array_values($user->roles)) && !in_array('manage data', array_values($user->roles))) {
				$account = user_load($user->uid);
				// dsm($account);
				if(isset($account->field_station_region['und'])){
					foreach($account->field_station_region['und'] as $region){
						$stations[] = views_get_view_result('view_station_filter_parameter',Null,$region['value'], 'all','all');
					}
				}
	}
	else{
		$stations[] = views_get_view_result('view_station_filter_parameter',Null,'all', 'all','all');
	}
	foreach($stations[0] as $station){
		$station_name[$station->nid] = $station->node_title;
	}
	return $station_name;
} 

/**
	*Begin: 16/11. 
 *author:Nguyễn Mạnh Hùng
 */
 /*
function _datalogger_return_area($areas){
	$regions_list = array(
		north_central_region => t('North Central Region'),
		mid_central_region  => t('Central Central Region'),  
		south_central_region  => t('South Central Region'),
		south_region => t('South Region'),
		central_highlands => t('Central Highlands Region'),
	);
	// $regions = array();
	if($areas == Null){
		return $regions_list;
	}
	else{
		foreach($areas as $area){
			$regions[] = $regions_list[$area[0]];
		}
		return $regions;
	}
}

function _datalogger_return_city($citys){
	$provinces_list = array(
		ho_chi_minh => t('Ho Chi Minh'),
		hai_phong => t('Hai Phong'),
		ha_giang => t('Ha Giang'),
		cao_bang => t('Cao Bang'),
		lai_chau => t('Lai Chau'),
		lao_cai => t('Lao Cai'),
		tuyen_quang => t('Tuyen Quang'),
		lang_son => t('Lang Son'),
		bac_kan => t('Bac Kan'),
		thai_nguyen => t('Thai Nguyen'),
		yen_bai => t('Yen Bai'),
		son_la => t('Son La'),
		phu_tho => t('Phu Tho'),
		vinh_phuc => t('Vinh Phuc'),
		quang_ninh => t('Quang Ninh'),
		bac_giang => t('Bac Giang'),
		bac_ninh => t('Bac Ninh'),
		ha_noi => t('Ha Noi'),
		hai_duong => t('Hai Duong'),
		hung_yen => t('Hung Yen'),
		hoa_binh => t('Hoa Binh'),
		ha_nam => t('Ha Nam'),
		nam_dinh => t('Nam Dinh'),
		thai_binh => t('Thai Binh'),
		ninh_binh => t('Ninh Binh'),
		dong_nai => t('Dong Nai'),
		long_an => t('Long An'),
		bac_lieu => t('Bac Lieu'),
		dien_bien => t('Dien Bien'),
		paging0 => '------------------',				
		north_central_region => array(thanh_hoa => t('Thanh Hoa'),
		nghe_an => t('Nghe An'),
		ha_tinh => t('Ha Tinh'),),
		paging1 => '------------------',
		mid_central_region => array(quang_tri => t('Quang Tri'),
		quang_binh => t('Quang Binh'),
		thua_thien_hue => t('Thua Thien - Hue'),
		da_nang => t('Da Nang'),
		quang_nam => t('Quang Nam'),
		quang_ngai => t('Quang Ngai'),),
		paging2 => '------------------',
		south_central_region => array(binh_dinh => t('Binh Dinh'),
		phu_yen => t('Phu Yen'),
		khanh_hoa => t('Khanh Hoa'),
		ninh_thuan => t('Ninh Thuan'),
		binh_thuan => t('Binh Thuan'),),
		paging3 => '------------------',
		south_region => array(binh_duong => t('Binh Duong'),
		tay_ninh => t('Tay Ninh'),
		tien_gian => t('Tien Giang'),
		tra_vinh => t('Tra Vinh'),
		can_tho => t('Can Tho'),
		soc_trang => t('Soc Trang'),
		dong_thap => t('Dong Thap'),
		binh_phuoc => t('Binh Phuoc'),
		an_giang => t('An Giang'),
		kien_giang => t('Kien Giang'),
		ca_mau => t('Ca Mau'),
		ben_tre => t('Ben Tre'),
		ba_ria_vung_tau => t('Ba Ria - Vung Tau'),
		vinh_long => t('Vinh Long'),
		hau_giang => t('Hau Giang'),),
		paging4 => '------------------',
		central_highlands  => array(lam_dong => t('Lam Dong'),
		kom_tum => t('Kon Tum'),
		giai_lai => t('Gia Lai'),
		dak_lak => t('Dak Lak'),
		dak_nong => t('Dak Nong'),),
	);
	// $provinces[] = array();
	foreach($citys as $city){
		$provinces[] = $provinces_list[$city[0]];
	}
	return array_merge($provinces);
}
/*		
		
/**
 *Begin: 19/11. 
 *author:Nguyễn Mạnh Hùng
 *description:danh sach cac tram do mưa theo khu vực/tinh/tram
 */
function _datalogger_station_ajax($area, $province,$nid){
	$stations = views_get_view_result('view_station_filter_parameter',Null, $area, $province, $nid);
	return $stations;
}
		
		
/**
 *Begin: 17/11. 
 *author:Phan Văn Tuấn
 *description:tạo form xuất báo cáo theo năm
 */
//
function _datalogger_set_station_callback($form, &$form_state){
	return $form['station'];
}

function _datalogger_set_station_options($area, $province) {
    // $options = array(
        // 'colors' => array(
            // 'red' => 'Red',
            // 'green' => 'Green',
            // 'blue' => 'Blue'
        // ),
        // 'cities' => array(
            // 'paris' => 'Paris, France',
            // 'tokyo' => 'Tokyo, Japan',
            // 'newyork' => 'New York, US'
        // ),
        // 'animals' => array(
            // 'dog' => 'Dog',
            // 'cat' => 'Cat',
            // 'bird' => 'Bird'
        // ),  
    // );
    // if (isset($options[$key])) {
        // return $options[$key];
    // }
    // else {
        $stations = views_get_view_result('view_station_filter_parameter', NULL, $area, $province, 'all');
				foreach($stations as $station){
					$titles[] = array($station->nid => $station->node_title);
				}
        return $titles;
    // }
}

function _datalogger_select_area_province_station(&$form, &$form_state){
	module_load_include('module', 'datalogger','datalogger');
	
	$form['selectReport'] = array(
    '#type' => 'select',
    '#title' => t('Select the type of report: '),
    '#options' => array(
      'bk1' => t('Reported rainfall data in report form BKT-14'),
     ),
  );
	
	global $user;
	$account = user_load($user->uid,true);
	foreach($account->field_station_region['und'] as $region){
		$regions[$region['value']] = _datalogger_return_area($region['value']);
	}
	
	$value_select_area = isset($form_state['values']['selectArea']) ? $form_state['values']['selectArea'] : key($regions);
  $form['selectArea'] = array(
    '#type' => 'select',
    '#title' => t('Chọn khu vực: '),
    '#options' => $regions,
		'#default_value' => $value_select_area,
		'#ajax' => array(
      'event'=>'change',
      'callback' =>'_datalogger_ajax_dropdown_area',
      'wrapper' => 'area-wrapper',
			'method' => 'replace',
      'effect' => 'fade',
    ),
  );
	
	$form['selectProvince'] = array(
	 '#prefix' => '<div id="area-wrapper">',
	 '#suffix' => '</div>',
	);
	
	$value_select_province = isset($form_state['values']['province']) ? $form_state['values']['province'] : key(_datalogger_return_city2($value_select_area));
	$form['selectProvince']['province'] = array(
		'#type' => 'select',
		'#title' => t('Chọn Tỉnh/ Thành phố: '),
		'#options' => _datalogger_return_city2($value_select_area),
		'#default_value' => $value_select_province,
		'#ajax' => array(
      'event'=>'change',
      'callback' =>'_datalogger_ajax_dropdown_province',
      'wrapper' => 'province-wrapper',
			'method' => 'replace',
      'effect' => 'fade',
    ),
	); 
	// dsm(key(_datalogger_return_city2($value_select_area)));
	$form['selectStation'] = array(
	// $form['selectProvince']['province']['selectStation'] = array(
	 '#prefix' => '<div id="province-wrapper">',
	 '#suffix' => '</div>',
	);
	// dsm($value_select_province);
	$stations = views_get_view_result('view_station_filter_parameter', Null, 	$value_select_area, $value_select_province, 'all');
	foreach($stations as $station){
		$station_name[$station->nid] = $station->node_title;
	}
	
	$form['selectStation']['station'] = array(
	// $form['selectProvince']['province']['selectStation']['station'] = array(
	// $form['province']['selectStation']['station'] = array(
		 '#type' => 'select',
		 '#title' => t('Select station: '),
		 '#options' => $station_name,
		 '#default_value' => isset($form_state['values']['station']) ? $form_state['values']['station']: key($station_name),
	);
	
	$years = array();
	for($i = 0; $i <30; $i++){
		$year = 2012 + $i;
		$years[$year] = $year;
	}
	
	$months = array();
	for($i = 1; $i < 13; $i++){
		$months[$i] = $i;
	}
	
	$form['year'] = array(
		 '#type' => 'select',
		 '#title' => t('Year'),
		 '#options' => $years,
		 '#default_value' => key($years),
	);
	
	$form['month'] = array(
     '#type' => 'select',
     '#title' => t('Month'),
     '#options' => $months,
  );
	
	$form['day'] = array(
     '#type' => 'date_popup',
     '#date_format' => 'd/m/Y', 
		 '#required' => TRUE,	
  );
	
  $form['txtNameQTV'] = array(
     '#type' => 'textfield',
     '#title' => t('Full name of the person observation: '),
  );  
  
  $form['txtNameNLB'] = array(
     '#type' => 'textfield',
     '#title' => t('Full name of the person creating the table: '),
  );    
  
  $form['txtNameKS'] = array(
     '#type' => 'textfield',
     '#title' => t('Full name of the person control: '),
  );    
  
  $form['txtNamePT'] = array(
     '#type' => 'textfield',
     '#title' => t('Full name of person Appeal: '),
  );
  
  
  $form["notice_excel_2007"] = array(      
      '#prefix' => '<div class="" style="margin-bottom: 15px;">',
	  '#suffix' => '</div>', 
	  "#markup" => t("For better rendering, downloaded file format will be Excel 2007. If you cannot read XLSX file format, please download and install Microsoft compability pack at: <a href='http://www.microsoft.com/en-us/download/details.aspx?id=3'>http://www.microsoft.com/en-us/download/details.aspx?id=3</a>."),      
  ); 
	
	return $from;
}

function _datalogger_report_rainfall_year_form($form, &$form_state){
	drupal_set_title(t('Report annual rainfall data'));
	
	_datalogger_select_area_province_station($form, $form_state);
	$form['month']['#access']=FALSE;
	$form['day']['#access']=FALSE;
	
	$form["submit"] = array(
      "#type" => "submit",
      "#value" => t("Report"),
      "#submit" => array(
          "_datalogger_report_rainfall_year_form_submit"
      ),
  ); 
  return $form;
}

function _datalogger_ajax_dropdown_area(&$form, &$form_state){
	return $form['selectProvince'];
}

function _datalogger_ajax_dropdown_province(&$form, &$form_state){
	return $form['selectStation'];
}

function _datalogger_report_rainfall_year_form_submit(&$form, &$form_state) {
	module_load_include('inc', 'datalogger', 'datalogger.admin.excel');
	$nid = $form_state['values']['station'];
	$area = $form_state['values']['selectArea'];
	$province = $form_state['values']['province'];
	$year = $form_state['values']['year'];
	$name_qtv = $form_state['values']['txtNameQTV'];
	$name_nlb = $form_state['values']['txtNameNLB'];
	$name_ks = $form_state['values']['txtNameKS'];
	$name_pt = $form_state['values']['txtNamePT'];
	$rainfalls = views_get_view_result('view_export_excel', Null, $nid, $year, 'all', 'all');
	if(count($rainfalls) <= 0){
		drupal_set_message(t('Trạm đo mưa trên chưa có số liệu để lập báo cáo'),'error');
	}
	else{
		$args = array($nid, $rainfalls, $name_qtv, $name_nlb, $name_ks, $name_pt);
		_export_excel($args);
	}
}

/**
 *author:Phan Văn Tuấn
 *description:tạo form xuất báo cáo theo ngày
 */
function _datalogger_report_rainfall_day_form($form, &$form_state){
	drupal_set_title(t('Reports daily rainfall data'));
	
	_datalogger_select_area_province_station($form, $form_state);
	$form['year']['#access']=FALSE;
	$form['month']['#access']=FALSE;
	
	
	
  $form["submit"] = array(
      "#type" => "submit",
      "#value" => t("Report"),
      "#submit" => array(
          "_datalogger_report_rainfall_day_form_submit"
      ),
  ); 
  return $form;
}

function _datalogger_report_rainfall_day_form_submit(&$form, &$form_state) {
	// /*
	module_load_include('inc', 'datalogger', 'datalogger.admin.excel');
	
	$nid = $form_state['values']['station'];
  $day = new DateTime($form_state['values']['day']);
  $year = dsm($day->format('Y'));
  $month = dsm($day->format('m'));
  $day = $day->format('Ymd');
	$day = new DateTime($form_state['values']['day']);
	$day1 = new DateTime($form_state['values']['day']);
	$year = $day1->format('Y');
	$day2 = new DateTime($form_state['values']['day']);
	$month = $day2->format('m');
	if($month < 10){
		$month = '0'.$month;
	}
	$day = $day->format('Ymd');
	$name_qtv = $form_state['values']['txtNameQTV'];
	$name_nlb = $form_state['values']['txtNameNLB'];
	$name_ks = $form_state['values']['txtNameKS'];
	$name_pt = $form_state['values']['txtNamePT'];
  
	// $rainfalls = views_get_view_result('view_export_excel','default', $nid, 'all', 'all', $day);
	$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year.$month, $day);
	if(count($rainfalls) <= 0){
		drupal_set_message(t('Rainfall stations in the no data to report'),'error');
	}
	else{
		$args = array($nid, $rainfalls, $name_qtv, $name_nlb, $name_ks, $name_pt);
		_export_excel($args);
	}
	// */
	
	/*
	//kiem tra luong mua theo bao cao hang ngay trong thang
	module_load_include('inic', 'datalogger', 'excel_export.admin.excel');
	$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year.$month, $day);
	$month_days_nuber = cal_days_in_month(CAL_GREGORIAN, 12, 2012);
	for($day = 1; $day <= $month_days_nuber; $day++){
		if($day < 10){
			$day = '0'.$day;
		}
		$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year.$month, $year.$month.$day);
		for($i = 0; $i < count($rainfalls); ($i = $i + 6)){
			$rainfalls_time_day_24[] = $rainfalls[$i];
		}
		$months[$i] = $rainfalls_time_day_24;
	}
	
	//ham lay gio trong ngay
	for($i = 0; $i < count($rainfalls); ($i = $i + 6)){
		$rainfalls_time_day_24[] = $rainfalls[$i];
	}
	
	// dsm($rainfalls_time);
	
	// if(count($rainfalls) <= 0){
		// drupal_set_message(t('Rainfall stations in the no data to report'),'error');
	// }
	// else{
		// $args = array($nid, $rainfalls, $name_qtv, $name_nlb, $name_ks, $name_pt);
		// // $args = array($nid, $rainfalls_time_day_24, $name_qtv, $name_nlb, $name_ks, $name_pt);
		// _export_excel($args);
	// }
	
	*/
		// _export_excel();
}

function _datalogger_language_field(&$node, $field_name, $value = 'value') {
  $all_languages = array('und', 'vi', 'en');  
  foreach($all_languages as $lang) {
    if (isset($node->{$field_name}[$lang]['0'][$value])) {
      return $node->{$field_name}[$lang]['0'][$value];      
    }
  }
  return '';
}

function _datalogger_send_command($nid, $select, $form, &$form_state) {
	// $nids = arg();
	define('DATEymdHis', date('ymdHis',time()));  
  define('DATEymdHi', date('ymdHi',time()));  
  define('DATEYmdHi', date('YmdHi',time()));  
  
  // $nids = array(0, intval($form_state['values']['station_nid']));
  $nids = $form_state['values']['station_nid'];
	
	// dsm('_datalogger_send_command :'.$form_state['values']['station_nid']);
  
	for($i_nid = 1; $i_nid < count($nids); $i_nid++ ) {
    $nid = intval($nids[$i_nid]);
    
		if($nid) {  
			$node = node_load($nid);
      dpm($node);
			$code = _datalogger_language_field($node, 'field_station_code');
      for ($i = strlen($code); $i < 6; $i++)  $code = '0' . $code;    // add 0 to max 6 chars.
      
      $phone = _datalogger_language_field($node, 'field_station_sim_number');
      
      if (!$phone) {
        drupal_set_message(t('Lỗi đọc số điện thoại trạm.'));
      }
      
      //dpm($node);
      //dpm($phone);
      
			// $modem = $node->field_station_modem['und']['0']['value'];
			$modem = node_load(_datalogger_language_field($node, 'field_station_modem', 'nid')); 
      switch ($select) {
        //Data call command
        case 1 :
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'I:STATUS ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          $arg = array('Lấy số liệu mưa hiện tại','I:STATUS', _datalogger_result($message,'I:STATUS'),'',$nid);
          $check = true;
          break;
        case 2 :
          $dt_from = $form_state['values']['date_time_from'];
          $from = _datalogger_convert_date('ymdHi',$dt_from);
          $dt_to = $form_state['values']['date_time_to'];
          $to = _datalogger_convert_date('ymdHi',$dt_to);
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'S:'.$from.'-'.$to;
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Save Data Call','2', _datalogger_result($message),'');
          $arg = array('Lấy dữ liệu đã lưu trên Datalogger','S:', _datalogger_result($message,'S:'),'',$nid);
          break;
        //Date and Time Set
        case 3 : 
				// dsm($form_state['values']['date_time_set']);
          $date = _datalogger_convert_date($strFormat = 'Ymdhis', $form_state['values']['date_time_set']);
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'T:'.$date;
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array(('Date $ Time Set'),'3', _datalogger_result($message),'');
          $arg = array(('Thiết lập thời gian'),'T:', _datalogger_result($message,'T:'),'',$nid);

          break;
        case 4 : 
          // $title =  t('GPRS Network Time Synchronization');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'T:NITZ                                                      ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('GPRS Network Time Synchronization','4', _datalogger_result($message),'');
          $arg = array('Đồng bộ thời gian mạng GPRS','T:NITZ', _datalogger_result($message,'T:NITZ'),'',$nid);
          break;
        //CODE $ Password Set
        case 5 :
          // $title =  t('Set CODE');
          $id = $form_state['values']['set_input_id'];
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'D:'.$id.'                                                    ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set CODE','5', _datalogger_result($message),'');
          $arg = array('Thiết lập ID','D:', _datalogger_result($message,'D:'),'',$nid);
          break;
        case 6 :
          // $title =  t('Get CODE');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'D:?                                                         ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          
          // $arg = array('Get CODE','6', _datalogger_result($message),'');
          $arg = array('Lấy thông tin ID','D:', _datalogger_result($message,'D:'),'',$nid);
          break;
        case 7 :
          $pass = $form_state['values']['set_pass'];
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'W:'.$pass;
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Password','7', _datalogger_result($message),'');
          $arg = array('Thiết lập mật khẩu','W:', _datalogger_result($message,'W:'),'',$nid);
          break;
        case 8 :
          // $title =  t('Get Password');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'W:?                                                         ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Password','8', _datalogger_result($message),'');
          $arg = array('Lấy thông tin mật khẩu','P:', _datalogger_result($message,'W:'),'',$nid);
          break;
        //database Buffer Clear
        case 9 :
          // $title =  t('All Database Buffer Clear');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'R:FORMAT ALL                                                ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('All Database Buffer Clear','9', _datalogger_result($message),'');
          $arg = array('Xóa bộ đệm dữ liệu','R:FORMAT ALL', _datalogger_result($message,'R:FORMAT ALL'),'',$nid);
          break;
        case 10 :
          // $title =  t('Specific Date Database Buffer Clear');
          $day = _datalogger_convert_date('ymd',$form_state['values']['date_buffer_clear']);
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'R:FORMAT DAY:'.$day.'                                         ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Specific Date Database Buffer Clear','10', _datalogger_result($message),'');
          $arg = array('Xóa bộ đệm dữ liệu theo ngày','R:FORMAT DAY:', _datalogger_result($message,'R:FORMAT DAY:'),'',$nid);
          break;
        //Rain fall config
        case 11 :
          // $title =  t('Accumulated Rain Fall Value Set');
          $number = $form_state['values']['accumulated_rain_fall'];
          $number = (float)$number * 10;
          $number = (int)$number;
          
          $len = strlen($number);
          if($len < 5 ){
            for($i = 0; $i < (5 - $len); $i++){
              $number = ' '.$number;
            }
          }
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'R:SET:'.$number.'                                                 ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Accumulated Rain Fall Value Set','11', _datalogger_result($message),'');
          $arg = array('Thiết lập gía trị lượng mưa tích lũy','R:SET:', _datalogger_result($message,'R:SET:'),'',$nid);
          break;
        case 12 :
          // $title =  t('Set Rain Fall Clear Time');
          global $clearTime2 ;
          // dsm($form_state['values']['set_rain_fall_clear_time']);
          $time = $clearTime2[$form_state['values']['set_rain_fall_clear_time']];
          // dsm($time);
          // dsm($clearTime2[0]);
          // $time = _datalogger_convert_date('Hi',$form_state['values']['set_rain_fall_clear_time']);
          // dsm($time);
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'R:CLEAR TIME:'.$time.'                                           ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Rain Fall Clear Time','12', _datalogger_result($message),'');
          $arg = array('Thiết lập thời gian xóa dữ liệu mưa','R:CLEAR:', _datalogger_result($message,'R:CLEAR:'),'',$nid);
          // dsm(strlen($message));
          // dsm($message);
          break;
        case 13 :
          // $title =  t('Get Rain Fall Clear Time');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'R:CLEAR TIME:?                                              ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Rain Fall Clear Time','13', _datalogger_result($message),'');
          $arg = array('Lấy thời gian xóa dữ liệu mưa','R:CLEAR TIME:', _datalogger_result($message,'R:CLEAR TIME:'),'',$nid);
          break;
        //Datalogger config
        /*
        case 14 :
          // $title =  t('Self Power Reset');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'P:RESET                                                     ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Self Power Reset','14', _datalogger_result($message),'');
          $arg = array('Thiết lập lại nguồn điện','P:RESET', _datalogger_result($message,'P:RESET'),'',$nid);
          break;*/
        case 15 :
          // $title =  t('Set Active / De-Active Battery Power Voltage');
          $batOn = number_format($form_state['values']['bat_on'],1);
          $lenOn = strlen($batOn);
          if($lenOn < 5){
            for($i=0; $i < (5 - $lenOn); $i++){
              $batOn = '0'.$batOn;
            }
          }
          $batOff = number_format($form_state['values']['bat_off'],1);
          $lenOff = strlen($batOff);
          if($lenOff < 5){
            for($i=0; $i < (5 - $lenOff); $i++){
              $batOff = '0'.$batOff;
            }
          }
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'P:BAT ON:'.$batOn.'V, OFF:'.$batOff.'V                                 ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Active / De-Active Battery Power Voltage','15', _datalogger_result($message),'');
          $arg = array('Thiết lập điện áp nguồn ắc quy hoạt động/ngừng hoạt động','P:BAT ON:', _datalogger_result($message,'P:BAT ON:'),'',$nid);
          break;
        case 16 :
          // $title =  t('Get Active / De-Active Battery Power Voltage');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'P:BAT ON:?                                                  ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Active / De-Active Battery Power Voltage','16', _datalogger_result($message),'');
          $arg = array('Lấy điện áp nguồn điện ắc quy hoạt độn/ngừng hoạt động','P:BAT ON:', _datalogger_result($message,'P:BAT ON:'),'',$nid);
          break;
        case 17 :
          // $title =  t('Set Battery Voltage Offset');
          $vol = number_format($form_state['values']['set_bat_vol'],1);
          $lenVol = strlen($vol);
          if($lenVol < 4){
            for($i=0; $i < (4 - $lenVol); $i++){
              $vol = '0'.$vol;
            }
          }
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'P:BAT OFFSET:+'.$vol.'V                                         ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Battery Voltage Offset','17', _datalogger_result($message),'');
          $arg = array('Thiết lập phần bù điện áp ắc quy','P:BAT OFFSET:', _datalogger_result($message,'P:BAT OFFSET:'),'',$nid);
          break;
        case 18 :
          // $title =  t('Get Battery Voltage Offset');
          // $vol = number_format($form_state['values']['get_bat_vol'],1);
          // $lenVol = strlen($vol);
          // if($lenVol < 4){
            // for($i=0; $i < (4 - $lenVol); $i++){
              // $vol = '0'.$vol;
            // }
          // }
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'P:BAT OFFSET:?                                        ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Battery Voltage Offset','18', _datalogger_result($message),'');
          $arg = array('Lấy phần bù điện áp ắc quy','P:BAT OFFSET:', _datalogger_result($message,'P:BAT OFFSET:'),'',$nid);
          // dsm($message);
          // dsm(strlen($message));
          break;
        case 19 :
          // $title =  t('Set Auto Power Management Enable');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'P:AUTO PWR MANAGEMENT:ON                                    ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Auto Power Management Enable','19', _datalogger_result($message),'');
          $arg = array('Thiết lập tự động quản lý nguồn điện áp','P:AUTO PWR MANAGEMENT:ON', _datalogger_result($message,'P:AUTO PWR MANAGEMENT:ON'),'',$nid);
          break;
        case 20 :
          // $title =  t('Set Auto Power Management Disable');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'P:AUTO PWR MANAGEMENT:OFF                                   ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Auto Power Management Disable','20', _datalogger_result($message),'');
          $arg = array('Thiết lập không tự động quản lý nguồn điện','P:AUTO PWR MANAGEMENT:OFF', _datalogger_result($message,'P:AUTO PWR MANAGEMENT:OFF'),'',$nid);
          break;
        case 21 :
          // $title =  t('Get Auto Power Management Enable / Disable');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'P:AUTO PWR MANAGEMENT:?                                     ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Auto Power Management Enable / Disable','21', _datalogger_result($message),'');
          $arg = array('Lấy thông tin quản lý nguồn','P:AUTO PWR MANAGEMENT:', _datalogger_result($message,'P:AUTO PWR MANAGEMENT:'),'',$nid);
          break;
        case 22 :
          // $title =  t('Go To Sleep Mode');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'P:GOTO SLEEP MODE                                           ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Go To Sleep Mode','22', _datalogger_result($message),'');
          $arg = array('Chuyển sang chế độ ngủ','P:GOTO SLEEP MODE', _datalogger_result($message,'P:GOTO SLEEP MODE'),'',$nid);
          break;
        //Comunication setting
        case 23 :
          // $title =  t('Set Data Send Interval Minutes');
          global $timeInterval;
          $interval = $timeInterval[$form_state['values']['set_interval']];
          // dsm($interval);
          $lenint = strlen($interval);
          if($lenint < 4){
            for($i = 0; $i < (4 - $lenint); $i++ ){
              $interval =' '.$interval;
            }
          }
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'C:INTERVAL:'.$interval.'                                             ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Data Send Interval Minutes','23', _datalogger_result($message),'');
          $arg = array('Thiết lập thời gian truyền dữ liệu','C:INTERVAL:', _datalogger_result($message,'C:INTERVAL:'),'',$nid);
          // dsm(strlen($message));
          // dsm($message);
          break;
        case 24 :
          // $title =  t('Get Data Send Interval Minutes');
          $sms =  'S' . $code . 'GET  '.DATEymdHis.'C:INTERVAL:?                                                ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Data Send Interval Minutes','24', _datalogger_result($message),'');
          $arg = array('Lấy thời gian truyền dữ liệu','C:INTERVAL:', _datalogger_result($message,'C:INTERVAL:'),'',$nid);
          break;
        case 25 :
          // $title =  t('Set Communication Type GSM');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'C:COMM:GSM                                                  ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Communication Type GSM','25', _datalogger_result($message),'');
          $arg = array('Thiết lập kết nối dạng GSM','C:COMM:GSM', _datalogger_result($message,'C:COMM:GSM'),'',$nid);
          break;
        case 26 :
          // $title =  t('Set Communication Type GPRS');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'C:COMM:GPRS                                                 ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Communication Type GPRS','26', _datalogger_result($message),'');
          $arg = array('Thiết lập kết nối dạng GPRS','C:COMM:GPRS', _datalogger_result($message,'C:COMM:GPRS'),'',$nid);
          break;
        case 27 :
          // $title =  t('Set Communication Type Auto');
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'C:COMM:AUTO                                                 ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Communication Type Auto','27', _datalogger_result($message),'');
          $arg = array('Thiết lập kết nối dạng tự động','C:COMM:AUTO', _datalogger_result($message,'C:COMM:AUTO'),'',$nid);
          break;
        case 28 :
          // $title =  t('Get Communication Type');     
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'C:COMM:?                                                    ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Communication Type','28', _datalogger_result($message),'');
          $arg = array('Lấy về trạng thái kết nối','C:COMM:', _datalogger_result($message,'C:COMM:'),'',$nid);
          break;
        //GPRS network setting
        case 29 :
          // $title =  t('Set GPRS Network Setting');
          $host = $form_state['values']['host_gprs'];
          $id = $form_state['values']['id_gprs'];
          $pass = $form_state['values']['pass_gprs'];
          
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'G:APN:'.$host.',ID:'.$id.',PW:'.$pass;
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set GPRS Network Setting','29', _datalogger_result($message),'');
          $arg = array('Thiết lập mạng GPRS','G:APN:', _datalogger_result($message,'G:APN:'),'',$nid);
          break;
        case 30 :
          // $title =  t('Get GPRS Network Setting');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'G:APN:?                                                     ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          
          // $arg = array('Get GPRS Network Setting','30', _datalogger_result($message),'');
          $arg = array('Lấy thiết lập mạng GPRS','G:APN:', _datalogger_result($message,'G:APN:'),'',$nid);
          break;
        case 31 :
          // $title =  t('Set Host Network Infomation');
          $host = $form_state['values']['set_host'];
          $port = $form_state['values']['set_port'];
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'N:HOST:'.$host.':'.$port;
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Host Network Infomation','31', _datalogger_result($message),'');
          $arg = array('Thiết lập mạng máy chủ','N:HOST:', _datalogger_result($message,'N:HOST:'),'',$nid);
          break;
        case 32 :
          // $title =  t('Get Host Network Infomation');      
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'N:HOST:?                                                    ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Host Network Infomation','32', _datalogger_result($message),'');
          $arg = array('Lấy thông tin mạng máy chủ','N:HOST:', _datalogger_result($message,'N:HOST:'),'',$nid);
          break;
        case 33 :
          // $title =  t('Set Host Phone Number');
          $sim = $form_state['values']['host_phone'];
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'H:HOST PHONE NO:'.$sim;
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Set Host Phone Number','33', _datalogger_result($message),'');
          $arg = array('Thiết lập số điện thoại máy chủ','H:HOST PHONE NO:', _datalogger_result($message,'H:HOST PHONE NO:'),'',$nid);
          break;
        case 34 :
          // $title =  t('Get Host Phone Number');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'H:HOST PHONE NO:?                                           '; 
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';
          // $arg = array('Get Host Phone Number','34', _datalogger_result($message),'');
          $arg = array('Lấy số điện thoại máy chủ','H:HOST PHONE NO:', _datalogger_result($message,'H:HOST PHONE NO:'),'',$nid);
          break;
        //Get datalogger firmware version
        case 35 :
          // $title =  t('Get Datalogger Firmware Version');
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'V:VERSION:?                                                 ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';			
          // $arg = array('Get Datalogger phiên Version','35', _datalogger_result($message),'');
          $arg = array('Lấy phiên bản Datalogger hiện tại','V:VERSION:', _datalogger_result($message,'V:VERSION:'),'',$nid);
          break;
        case 36 :
          $interval = $form_state['values']['set_alarm'];
          if(strlen($interval) < 3){
            $interval = '0'.$interval;	
          }
          $level = $form_state['values']['set_level'];
          
          $level = floatval($level) * 10;   
          $level = intval($level);
          
          if(strlen($level) < 4){
            $lenstr = strlen($level);
            for($i = 0; $i < 4-$lenstr; $i++){
              $level = ' '.$level;
            }
          }
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'A:ALARM INTERVAL:'.$interval.', LEVEL:'.$level.'                            ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';			
          // dsm($message);
          // dsm(strlen($message));
          // $arg = array('Get Datalogger phiê Version','35', _datalogger_result($message),'');
          $arg = array('Thiết lập thời gian và lượng mưa cảnh báo', 'A:ALARM INTERVAL:', _datalogger_result($message,'A:ALARM INTERVAL:'), '', $nid);
          break;
        case 37 :
          $sms = 'S' . $code . 'GET  '.DATEymdHis.'A:ALARM INTERVAL:?                                          ';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';			
          // dsm($message);
          // dsm(strlen($message));
          // $arg = array('Get Datalogger phiê Version','35', _datalogger_result($message),'');
          $arg = array('Lấy về thời gian và lượng mưa cảnh báo','A:ALARM INTERVAL:', _datalogger_result($message,'A:ALARM INTERVAL:'),'',$nid);
          break;
        case 38 :
        //reset all config			
          $sms = 'S' . $code . 'SET  '.DATEymdHis.'P:RESET';
          $sms = _datalogger_add_space($sms, 84);
          $message = 'H'.$sms._datalogger_CheckSum($sms).';';			
          $arg = array('Khởi động lại Datalogger', 'P:RESET', _datalogger_result($message,'P:RESET'),'',$nid);
          break;
      }

      
      $type = substr($sms, 7, 3);
      $arg['type'] = $type;
			
			// dsm('first '.$arg[1]);
			
			$arg[1] = str_replace(' ', '_', trim($arg[1]));
			
      $node_command = _datalogger_insert_node_command($arg);

      _datalogger_insert_outbox($phone, $message, $modem->title);	
      // if($check != true){
        // $form_state['redirect'] = 'node/' . $node_command->nid . '/refresh';
      // }else{
        // $form_state['redirect'] = 'view/rainfall/default/refresh';
      // }
    }
	}
  
	drupal_set_message(t('Command has been sent for delivering outbox.'));
  
  return $node_command;
}	

function _datalogger_submit_command_callback($form, &$form_state) {
	
  $node_command = _send_command_submit($form, $form_state);
  
  $element = &$form['submit_command_fieldset'];
  
  $form['submit_command_fieldset']['#title'] = t('Command Result') . ': ' . date('d/m/Y - H:i:s', time());
  $element['#markup'] = "Clicked submit";
  
  if ($node_command->nid) {
    $form['submit_command_fieldset']['date_time_from'] = array(    
      '#markup' => drupal_render(node_view($node_command)),    
    );
  }
  else {
    
  }
	
  return $element;
}

function datalogger_command_refresh_ajax() {

  $nid = intval(arg(4));
  $node = node_load($nid);
  echo '<div class="messages status">' . t('Updated on: !time.', array('!time' => date('d/m/Y - H:i:s', time()))) . '</div>';
  echo drupal_render(node_view($node));
  drupal_exit();
}		
	  
/**
*begin: 09-10-12
*
*/

function _datalogger_get_station($view, $number){
	$display_id = 'default';
	$result = views_get_view_result($view, $display_id, $number);
	// $result->execute();
	return $result;
}

function test_view(){
	$number = '01634766847';
	$result = _datalogger_get_station('view_command_send', $number);
	$node_command = node_load($result[0]->nid);	
	return '';
}

function _datalogger_convert_number($number){
	$sim_number = '0'.substr($number,3);
	return $sim_number;
}

function _datalogger_check_inbox() {

  $cron = (arg(3) == 'remote');
  
  $processed = ($cron ? 31 : 0);
  

  $result = db_query("SELECT * FROM inbox WHERE Processed={$processed}");
  foreach ($result as $row) {
    // //tin nhắn từ datalogger
		$id_inbox = $row->ID;
    
    print "{$row->ID}\n";
    
		$number = _datalogger_convert_number($row->SenderNumber);
		$sms = $row->TextDecoded;
    if(_datalogger_startsWith($row->TextDecoded,'HS') && _datalogger_endsWith($row->TextDecoded,';')) {
      $len_sms = strlen($row->TextDecoded);
      //Xử lý tin nhắn được yêu cầu:88byte
      if($len_sms == 88){
				//Thực hiện chèn bản tin vào bảng command
				_datalogger_separate_sms_command($sms, $number);
				//Cập nhật các bản tin đã xử lý
				_datalogger_update_process_inbox(1,$id_inbox);
      }
      //Xử lý bản tin đo mưa tự động:140byte
      elseif($len_sms == 140) {
      
        switch ($number) {
        case '01647492506': // Ham Cuong
        case '01635662128': // Mỹ Thạnh
        case '01653448055': // Phan Sơn
        case '01654635702': // Phước Hà

          if ($row-> RecipientID == 'modem13') {    // nambo server
            
            if ($cron) {
              // Move sms to Nam Trung Bo server          
              module_load_include('inc', 'datalogger', 'datalogger.admin.sms');
              if (_datalogger_sms_post_server($row)) {
                _datalogger_update_process_inbox(30, $id_inbox);   // Cập nhật các bản tin đã xử lý
              }
            }
            else _datalogger_update_process_inbox(31, $id_inbox);   // mark for cron
            
          }
          
          break;
          
        default:
          // Chèn bản tin vào bảng đo mưa
          // dsm('into 140');
          _datalogger_separate_sms($sms,$number);
          // Cập nhật các bản tin đã xử lý
          _datalogger_update_process_inbox(1, $id_inbox);
        }
      }			
			else _datalogger_update_process_inbox(2, $id_inbox);
    }
		else{
			_datalogger_update_process_inbox(2, $id_inbox);
		}
    flush (); // flush the output buffer
  }
	//return 'Ok';
  print "Ok.";
  drupal_exit();
}

function _datalogger_update_process_inbox($process, $id_inbox){
	$query="UPDATE inbox SET Processed=:process WHERE ID=:pr";
	$result = db_query($query, array(':process'=>$process, ':pr'=>$id_inbox));
}

/**
 *Cập nhật giá trị trả từ Datalogger cho node command.
 **/
function _datalogger_separate_sms_command($sms, $number){

	global $datalogger_pattern;
	$malenh = '';
	foreach ($datalogger_pattern as $pattern) {
		if (substr($sms, 25, strlen($pattern)) == $pattern) {
			$malenh = $pattern;
		}
	}
	
	//neu co ban tin canh bao luong mua
	if($malenh == 'A:ALARM INTERVAL:'){
		$stations = views_get_view_result('view_station_find', Null, $number);
		if(count($stations) >= 1){
			$station = node_load($stations[0]->nid);
			$station->field_station_alarm[$station->language][0]['value'] =  'alarm_true';	
			node_save($station);
		}
	}
	
	$malenh = str_replace(' ', '_', trim($malenh));
	
	$result = views_get_view_result('admin_command_from_phone_code', 'default', $number, $malenh);
	$nid = $result[0]->nid;
  
  
	if($nid != 0 || !empty($nid)){
		$node_command = node_load($nid);	  
  	$node_command->field_command_result["und"][0]["value"] = _datalogger_result($sms, $malenh);	
		node_save($node_command);
	}
}

/**
 *Phân tách bản tin đưa mưa tự động từ Datalogger gửi về
*/

function _datalogger_string_to_date($str){
	// $year = substr($str,0,2);
	$year = date('Y', time());
	$month = substr($str,2,2);
	$day = substr($str,4,2);
	$hour = substr($str,6,2);
	$minute = substr($str,8,2);
	$second = substr($str,10,2);
	return $day.'/'.$month.'/'.$year.' '.$hour.':'.$minute.':'.$second;
}
function _datalogger_string_to_unix_date($str){
	// $year = substr($str,0,2);
	$year = date('Y', time());
	$month = substr($str, 2, 2);
	$day = substr($str, 4, 2);
	$hour = substr($str, 6, 2);
	$minute = substr($str, 8, 2);
	$second = substr($str, 10, 2);
	return mktime($hour,$minute,$second,$month,$day,$year);
}

function _datalogger_separate_sms($sms,$number) {
  list($code, $timenow, $timestart, $arg1, $arg2, $arg3, $arg4, $arg5, $arg6, $chk) = explode(",", $sms);
	$id = substr($code,2,6);
	$is_valid = array();
	$measuaring = array();
	$accumulate = array();
	$battery = array();
	$arg = array($arg1, $arg2, $arg3, $arg4, $arg5, $arg6);
	
	for($i = 0; $i < 6; $i++){
		$opp = _datalogger_separate_opp($arg[$i]);
		$is_valid[] = $opp[0];
		$measuaring[] = $opp[1];
		$accumulate[] = $opp[2];
		$battery[] = $opp[3];
	}

	$station = _datalogger_get_station('view_station_find', $number);
	$nid = $station[0]->nid;
	$title = $station[0]->node_title;
	$arg = array($timestart, $nid, $is_valid, $measuaring, $accumulate, $battery);

	_datalogger_insert_node_rainfall($arg);
}

function _datalogger_separate_opp($sms){
  $arg = array(substr($sms,0,1), substr($sms,1,5), substr($sms,6,5), substr($sms,11,5));
	return $arg;
}

/**
 *Lấy dữ liệu datalogger trả về.
 */

function _datalogger_result($sms, $pa = ''){	
	global $datalogger_pattern;
	
	$pattern = $datalogger_pattern;
	
	if(empty($pa) || $pa == '') {
		for($i = 0; $i < count($pattern); $i++ ){
			$len = strlen($pattern[$i]);
			$pos =  strpos($sms, $pattern[$i]);
			if(!empty($pos)){
				return trim(substr($sms,$pos+$len,-3));
			}
		}
	}
	else {
		$len = strlen($pa);
		$pos =  strpos($sms, $pa);
		if(!empty($pos)) {
			return trim(substr($sms, $pos + $len, -3));
		}
	}
	return '';
}

function _datalogger_return_str($sms, $pa){
	$pos =  strpos($sms, $pa[$i]);
	return trim(substr($sms,$pos,-3));	
}

/*Chèn node mới vào bàng command*/

function _datalogger_insert_node_command($arg){
	$node = new stdClass();
  $node->title = $arg[0];
  $node->type = 'command';
  $node->created = time();
  $node->changed = $node->created;
  $node->status = 1; // Published?
  $node->promote = 0; // Display on front page?
  $node->sticky = 0; // Display top of page?
  $node->format = 1; // Filtered HTML?
  $node->uid = 1; // Content owner uid (author)?
  $node->language = 'und';
	
  node_object_prepare($node);
  $node->field_command_code[$node->language][0]['value'] = $arg[1];
  $node->field_command_parameter[$node->language][0]['value'] = $arg[2];
  $node->field_command_result[$node->language][0]['value'] = $arg[3]; 
  $node->field_command_station[$node->language][0]['nid'] = $arg[4];  
	$node->field_command_type[$node->language][0]['value'] = $arg['type'];
  $node = node_submit($node);
  node_save($node);
	return $node;
}


function _datalogger_insert_node_rainfall(&$arg){
	$timestam = $arg[0];
	$nid = $arg[1];
	$station = node_load($nid);
	if( $nid != null || !empty($nid ) && (!empty($station) || $station != null)){
		$time_unix = _datalogger_string_to_unix_date($timestam);
		$is_data_valids = $arg[2];
		$measuring_interval = $arg[3];//3
		$accumulate;//4
		$battery = $arg[5];//5
		
		for($i = 5; $i >= 0; $i--){		
			$is_data_valid = $is_data_valids[$i];
			$time = $time_unix - 60*10*$i;
			$send_time = date('dmYHis',$time);
			$year = date('Y',$time);
			$year_month = date('Ym',$time);
			$year_month_date = date('Ymd',$time);
			if($is_data_valid == 0){
				$power = $battery[$i];
				$rainfalls = views_get_view_result('view_find_rainfall_station', NULL, $nid, $send_time);
				
				//xoa tat ca cac node neu trung du lieu
				if(count($rainfalls) > 0){
					foreach($rainfalls as $rainfall_old){
						$rainfall_old = node_load($rainfall_old->nid);
						//lượng mưa đo được trong 10p
						$rainfall_old->field_rainfall_measuring['und'][0]['value'] = $measuring_interval[$i]/10;
						//lượng mưa đo được trong 60p
						$rainfall_old->field_rainfall_total['und'][0]['value'] = $arg[4][$i]/10;
						node_save($rainfall_old);
						// node_delete($rainfall_old->nid);
					}
				}
				else{
					//tao node moi
					$rainfall = new stdClass();
					$rainfall->title = date('d/m/Y H:i:s',$time);
					$rainfall->type = "rainfall";
					$rainfall->created = time();
					$rainfall->changed = $rainfall->created;
					$rainfall->status = 1; // Published?
					$rainfall->promote = 0; // Display on front page?
					$rainfall->sticky = 0; // Display top of page?
					$rainfall->format = 1; // Filtered HTML?
					$rainfall->uid = 1; // Content owner uid (author)?
					$rainfall->language = 'und';

					node_object_prepare($rainfall); 
					$rainfall->field_rainfall_station[$rainfall->language][0]['nid'] = $nid;
					//lượng mưa đo được trong 10p
					$rainfall->field_rainfall_measuring[$rainfall->language][0]['value'] = $measuring_interval[$i]/10;
					//lượng mưa đo được trong 60p
					$rainfall->field_rainfall_total[$rainfall->language][0]['value'] = $arg[4][$i]/10;
					$rainfall->field_rainfall_send_time[$rainfall->language][0]['value'] = $time;
					$rainfall->field_rainfall_time_send_sms[$rainfall->language][0]['value'] = $send_time;
					$rainfall->field_rainfall_year[$rainfall->language][0]['value'] = $year;
					$rainfall->field_rainfall_year_month[$rainfall->language][0]['value'] = $year_month;
					$rainfall->field_rainfall_year_month_date[$rainfall->language][0]['value'] = $year_month_date;
					
					$rainfall = node_submit($rainfall);
					node_save($rainfall);
					
				}
			}
		}
		$station->field_station_power['und'][0]['value'] = $power/10;
		$station->field_station_rain_nearest['und'][0]['value'] = $measuring_interval[0]/10;
		$station->field_station_rain_24['und'][0]['value'] = $arg[4][0]/10;
		
		//tinh trang dang hoat dong_nai
		$station->field_station_status['und'][0]['value'] = 'station_active';		
		
		//trang thai: co mua
		if($measuring_interval[0]/10 > 0){
			//canh bao co mua - luong nho
			$station->field_station_alarm['und'][0]['value'] = 'alarm_rainfall';	
		}
		else{
			//khong co mua - kho han
			$station->field_station_alarm['und'][0]['value'] = 'alarm_false';	
		}		
		node_save($station);
	}
	
}

function _datalogger_generate_rainfalls_form($form, &$form_state) {
  $form['station'] = array(
    '#type' => 'textfield',
    '#title' => 'Trạm Nid',
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Sinh mưa',
  );
  return $form;
}

function _datalogger_generate_rainfalls_form_submit($form, &$form_state) {

  
  for($i = 1; $i <= 24; $i ++) {
    
    $station_nid = $form_state['values']['station'];
    
    $is_valid = 1;
  
    for($i = 0; $i < 6; $i++) {
      $accumulated[$i] = 0;
    }
    
    for($i = 0; $i < 6; $i++) {
      $measuaring[$i] = floatval(rand(6, 9)) / 10.0;
      $accumulated[$i] += $measuaring[$i];
      $battery[$i] = floatval(rand(124, 138)) / 10.0;
    }
    
    $arg = array('Lượng mưa ', $station_nid, $is_valid, $measuaring, $accumulated, $battery);
    
    _datalogger_insert_node_rainfall($arg);
    
  }
  drupal_set_message('Tạo node thành công.');
  
}



/**
*begin: 03-10-12
*
*/

function _datalogger_startsWith($sms, $needle)
{
	return substr($sms, 0, 2) == $needle;
}
function _datalogger_endsWith($sms, $needle)
{
	return substr($sms, -strlen($needle)) == $needle;
}

/*Ham xu ly cac tin nhắn gửi tới*/
function _datalogger_new_sms_form(){
	$output = "";
	$result = db_query("SELECT * FROM `inbox` ORDER BY  `inbox`.`ID` DESC LIMIT 0 , 50");
	$headers = array(
    no => t('No.'),
		station_name => t('Station Name'),
    receiving_date_time => t('Receiving Date Time'),
    sender_number => t('Sender Number'),
    message_content => t('Message content'),
		Modem => t('Modem'),
    processed => t('Processed'),
  );
 
  $rows = array();
  while($row = $result->fetchObject()){
		$number = _datalogger_convert_number($row->SenderNumber);
		$station = views_get_view_result('view_station_find', Null, $number );
		if(!empty($station)){
			$station_name = $station[0]->node_title;
		}
		else{
			$station_name = null;	
		}
    
    $sms = $row -> TextDecoded;
    $len_sms = strlen($row->TextDecoded);

    // highlight
    
    //Xử lý tin nhắn được yêu cầu:88byte
    if($len_sms == 88) {
      $sms = '<span style="background:blue;color:white;font-weight:bold">' . $sms . '</span>';
    }
    //Xử lý bản tin đo mưa tự động:140byte
    elseif($len_sms == 140) {
      $sms = _datalogger_regex_rain($sms);      
    }			
    
    
    
    $rows[] = array (
			$i+=1,
			// $station[0]->node_title,
			$station_name,
			$row -> UpdatedInDB,
			$row -> SenderNumber,
			$sms,
			$row -> RecipientID,
      $row -> Processed ? t('Yes') : t('No'),
			);

  }
  $output = theme_table(
    array(
      "header" => $headers,
      "rows" => $rows,
      "attributes" => array(),
      "sticky" => true, // Table header will be sticky
      "caption" => t('Date').': '.date('d/m/Y',time()),
      "colgroups" => array(),
      "empty" => t("Table has no row!") // The message to be displayed if table is empty
    )
  ).theme("pager");
 
  return $output;
}

function _datalogger_regex_rain($sms) {

  //$sms = 'HS092257,121207230000,121207230000,0 0 0 130,0 0 0 130,0 0 0 130,0 0 0 130,0 0 0 130,0 0 0 130,74;';

  $pattern = '/HS(\d\d\d\d\d\d),(\d\d)(\d\d)(\d\d)(\d\d)(\d\d)(\d\d),(\d\d)(\d\d)(\d\d)(\d\d)(\d\d)(\d\d),'
    . '(\d* *\d* *\d*) *(\d\d)(\d),'
    . '(\d* *\d* *\d*) *(\d\d)(\d),'
    . '(\d* *\d* *\d*) *(\d\d)(\d),'
    . '(\d* *\d* *\d*) *(\d\d)(\d),'
    . '(\d* *\d* *\d*) *(\d\d)(\d),'
    . '(\d* *\d* *\d*) *(\d\d)(\d),'
    . '(..);/';
  
  
  $replacement = '<span style="color:#fff">HS</span><em>${1}</em>,'
    . '<span style="color:red">${2}</span><span style="color:green">${3}</span><span style="color:blue">${4}</span>'
    . '<span style="background:#eee;text-decoration:underline;">'
      . '<span style="color:red">${5}</span><span style="color:green">${6}</span><span style="color:blue">${7}</span>'
    . '</span>'
    . ','
    . '<span style="color:red">${8}</span><span style="color:green">${9}</span><span style="color:blue">${10}</span>'
    . '<span style="background:#eee;text-decoration:underline;">'
      . '<span style="color:red">${11}</span><span style="color:green">${12}</span><span style="color:blue">${13}</span>'
    . '</span>'
  ;
  $n = 13;
  for ($i=1; $i<=6;$i++) {
    $replacement .= 
      ','
    . '<span style="background:#fff"><em>'
    . '<span style="color:blue">$' . ($n+1) . '</span> <span style="color:red">$' . ($n+2) . '</span><span style="color:#ffbbbb">$' . ($n+3) . '</span>'
    . '</em></span>'
    ;
    $n+=3;
  }
  $replacement .= ',<span style="color:#fff">$32</span>;';
  
  return preg_replace($pattern, $replacement, $sms);
}

/*Check sum sms*/
function _datalogger_CheckSum($str){
  $chk = 0;
  for($k = 0; $k < strlen($str); $k++){
    $o = ord(substr($str,$k,1));
    $chk ^= $o;
  }
  $res = substr("0" . dechex($chk),-2);
  return strtoupper($res);
}

/**
*begin: 28-09-12
*
*/

// function _datalogger_insert_outbox($phone, $sms){
  // /*cach 1:*/
  // $sql = "INSERT INTO outbox(DestinationNumber, TextDecoded, CreatorID) VALUES('$phone', '$sms', '')";
  // $nid = db_query($sql);
// }
function _datalogger_insert_outbox($phone, $sms, $modem){
  /*cach 1:*/
  // dsm('thong tin modem gui tin '.$modem);
  $sql = "INSERT INTO outbox(DestinationNumber, TextDecoded, CreatorID, SenderID) VALUES('$phone', '$sms', '', '$modem')";
  $nid = db_query($sql);
	// dsm($nid);
}

/**s
*begin: 25-09-12
*/

function _datalogger_convert_date($strFormat = 'ymdhis', $strDate){
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
	GLOBAL $station_name;
  $form['logStation'] = array(
     '#type' => 'select',
     '#title' => t('Chọn trạm: '),
     '#options' => $station_name,
		 '#attributes' => array('disabled' => 'disabled'),
  );
  
   $form['logDate'] = array(
     '#type' => 'date_popup',
		 '#attributes' => array('disabled' => 'disabled'),
  );
  
  $form['logSubmit'] = array(
     '#type' => 'submit',
     '#value' => t('Xem nhật ký'),
		 '#attributes' => array('disabled' => 'disabled'),
  );
  
  $headers = array(
    1 => t('STT'),
    2 => t('Thời gian'),
    3 => t('Tên file xử lý'),
    4 => t('Trạng thái'),
    5 => t('Mô tả'),
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

function _datalogger_report_rainfall_month_form($form, &$form_state){
	drupal_set_title(t('Report monthly rainfall data'));
	
	_datalogger_select_area_province_station($form, $form_state);
	$form['day']['#access']=FALSE;
	
  $form["submit"] = array(
      "#type" => "submit",
      "#value" => t("Report"),
      "#submit" => array(
          "_datalogger_report_rainfall_month_submit"
      ),
  ); 
  return $form;
}
function _datalogger_report_rainfall_month_submit(&$form, &$form_state) {
	// module_load_include('inc', 'datalogger', 'datalogger.admin.excel');
	module_load_include('inc', 'datalogger', 'excel_export.admin.excel');
	
	$nid = $form_state['values']['station'];
	$year = $form_state['values']['year'];
	$month = $form_state['values']['month'];
	$year_month = $year.$month;
	$name_qtv = $form_state['values']['txtNameQTV'];
	$name_nlb = $form_state['values']['txtNameNLB'];
	$name_ks = $form_state['values']['txtNameKS'];
	$name_pt = $form_state['values']['txtNamePT'];
	
	$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year_month, 'all');
	if(count($rainfalls) <= 0){
		drupal_set_message(t('Rainfall stations in the no data to report'),'error');
	}
	else{
		$args = array($nid, $rainfalls, $name_qtv, $name_nlb, $name_ks, $name_pt);
		_export_excel($args);
	}
	
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

function _datalogger_rainfalls() {
  // for ($i = 1; $i < 227; $i ++) {
  // _datalogger_init_node("Station - " . $i, "Code - " . $i, "Address - " . $i,
  // 1, $i, $i,
  // "Password" . $i, $i, "0168123456" . (78 + $i), $i);
  // }
  return "Finished Create Stations.";

}

function _log_rainfalls() {
  // for ($i = 1; $i < 10; $i ++) {
  // // _log_init_node("Log - ".$i,"Description - ".$i,"Event type - ".$i);
  // _log_init_node("Log - ".$i,"Set Auto Power Management Nable");
  // }
  return "Finished Create Logs.";

}

function _command_form($form, &$form_state) {
  global $user;

  $module_path = drupal_get_path('module', 'datalogger');
  
  drupal_add_js($module_path . '/datalogger_form_command.js');

  // GLOBAL $options_commands;
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
   // 14 => t('Self Power Reset'),
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
		//Alarm Options
		36 => t('Set the Alarm Interval and Level for rainfall alarming'),
		37 => t('Get the Alarm Interval and Level for rainfall alarming'),
		38 => t('Reset All'),);	
    
    
  if ($user->uid != 1)  {
    unset($options_commands[19]);   // Set Auto Power Management Enable disabled for not root
    unset($options_commands[22]);   // Go to Sleep mode
  }
    
	if(count(arg()) == 2){
		$nid = intval(arg(1));
		$node = node_load($nid);
		drupal_set_title(t('Rainfall stations: ').t($node->title));
	}
  $default = !empty($form_state['values']['command_selects']) ? $form_state['values']['command_selects'] : 1;
  $title = $options_commands[$default];
  $form['command_selects'] = array(
    "#type" => "select",
    "#title" => t("Command"),
    '#options' => $options_commands,
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => '_command_callback',
      'wrapper' => 'command-div',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
	$station_nid = !empty($form_state['values']['station_nid']) ? $form_state['values']['station_nid'] : arg();
	$form['station_nid'] = array(
    '#type' => 'hidden',    
    '#value' => $station_nid,
  );
	// */
	// */
	
  /*
	// Old
	$form['station_nid'] = array(
    '#type' => 'hidden',    
    '#value' => intval(arg(1)),
  );
	*/
  
  $form['command_fieldset'] = array(
    '#title' => t("Parameter of %title", array('%title' => $title)),
    '#prefix' => '<div id="command-div">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
  );
	
	
  switch ($default) {
    //Data call command
    case 1 :     
      break;
    case 2 :
      // $form['command_fieldset']['description'] = array(
        // '#type' => 'item',
        // // '#title' => 'a',
        // // '#description' => t('<b>Khoảng thời gian không được cách nhau quá 24h</b>'),
      // );
      $form['command_fieldset']['date_time_from']= array(
        '#type' => 'date_popup',
        '#title' => 'Từ Ngày', 
        '#date_format' => 'd/m/Y H:i:s', 
        '#default_value' => date('d/m/Y H:i:s', $_SERVER['REQUEST_TIME']),
        ////'#required' => TRUE,				
      );
      
      $form['command_fieldset']['date_time_to']= array(
        '#type' => 'date_popup',
        '#title' => 'Tới Ngày', 
        '#date_format' => 'd/m/Y H:i:s', 
        '#default_value' => date('d/m/Y H:i:s', $_SERVER['REQUEST_TIME']),    
        //'#required' => TRUE,
      );
      break;
    case 3 : 
      $form['command_fieldset']['date_time_set']= array(
      '#type' => 'date_popup',
      '#title' => 'Date $ Time', 
      '#date_format' => 'd/m/Y H:i:s',  
			'#required' => TRUE,
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
      );
      break;
    case 6 :
      break;
    case 7 :
      $form['command_fieldset']['set_pass'] = array(
        '#type' => 'textfield',
      '#title' => t('Password'),
      '#maxlength' => '4',
      '#default_value' => '8888',
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
			//'#required' => TRUE,
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
      //'#required' => TRUE,
      );
      break;
    case 12 :
      // $title =  t('Set Rain Fall Clear Time');
			global $clearTime ;
      $form['command_fieldset']['set_rain_fall_clear_time']= array(
      // '#type' => 'date_popup',
      // '#date_format' => 'd:m:Y H:i',
      // '#date_format' => 'Y H:i',
			// '#default_value' => date('H:i', time()),
			//'#required' => TRUE,
			"#type" => "select",
			// "#title" => t("Command"),
			'#options' => $clearTime,
			'#default_value' => 0,
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
      '#title' => t('Active Battery Power Voltage (V)'),
      // '#title' => 'Điện áp nguồn ắc quy hoạt động (V)',
      '#default_value' => 0011.0,
      '#maxlength' => 5,
      // '#description' => t('Dạng phải nhập: xxx.x'),
      //'#required' => TRUE,
      );
      $form['command_fieldset']['bat_off']= array(
      '#type' => 'textfield',
      '#title' => t('De-Active Battery Power Voltage (V)'),
      // '#title' => 'Điện áp nguồn ắc quy ngừng hoạt động (V)',
      '#default_value' => 0013.0,
      '#maxlength' => 5,
      // '#description' => t('Dạng phải nhập: xxx.x'),
      //'#required' => TRUE,
      );
      break;
    case 16 :
      // $title =  t('Get Active / De-Active Battery Power Voltage');
      break;
    case 17 :
      // $title =  t('Set Battery Voltage Offset');
      $form['command_fieldset']['set_bat_vol']= array(
      '#type' => 'textfield',
      // '#title' => 'Phần bù điện áp pin (V)',
      '#title' => t('Battery Voltage Offset (V)'),
      '#default_value' => 1.5,
      '#maxlength' => 4,
      '#description' => t('Dạng phải nhập: xx.x'),
      //'#required' => TRUE,
      );
      break;
    case 18 :
      // $title =  t('Get Battery Voltage Offset');
      // $form['command_fieldset']['get_bat_vol']= array(
      // '#type' => 'textfield',
      // '#title' => t('Battery Voltage Offset (V)'),
      // // '#title' => 'Phần bù điện áp pin (V)',
      // '#default_value' => 1.5,
      // '#maxlength' => 5,
      // '#description' => t('Dạng phải nhập: xx.x'),
      // //'#required' => TRUE,
      // );
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
			
			global $timeInterval;
      $form['command_fieldset']['set_interval']= array(
      // '#type' => 'textfield',
      // // '#title' => 'Thời gian truyên số liệu',
      '#title' => t('Data Send Interval Minutes'),
      // '#default_value' => 10,
      // '#maxlength' => 4,
      //'#required' => TRUE,
			"#type" => "select",
			// "#title" => t("Command"),
			'#options' => $timeInterval,
			'#default_value' => 0,
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
        '#title' => t('Host'),
        '#default_value' => '192.168.151.255',
        '#maxlength' => 15,
        '#description' => 'xxx.xxx.xxx.xxx',
        '#required' => true,
      );
      
      $form['command_fieldset']['id_gprs']= array(
        '#type' => 'textfield',
        '#title' => t('ID'),
        '#default_value' => 123456,
        '#maxlength' => 6,
        '#required' => true,
        '#description' => t('ID phải chứa 6 kí tự.'),
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
      '#title' => t('Host'),
      '#default_value' => '192.168.151.255',
      '#maxlength' => 15,
      '#required' => true,
      );
      
      $form['command_fieldset']['set_port']= array(
      '#type' => 'textfield',
      '#title' => t('Port'),
      '#default_value' => 8000,
      '#maxlength' => 6,
      // '#required' => true,
      );    
      break;
    case 32 :
      // $title =  t('Get Host Network Infomation');
      break;
    case 33 :
      // $title =  t('Set Host Phone Number');
      $form['command_fieldset']['host_phone']= array(
      '#type' => 'textfield',
      '#title' => t('Host Phone Number'),
      // '#title' => 'Số điện thoại máy chủ',
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
		case 36 :
      $form['command_fieldset']['set_alarm']= array(
      '#type' => 'textfield',
      '#title' => t('Interval'),
      '#default_value' => '60',
      '#maxlength' => 3,
      '#required' => true,
      );
      
      $form['command_fieldset']['set_level']= array(
      '#type' => 'textfield',
      '#title' => t('Level'),
      '#default_value' => '100.0',
      '#maxlength' => 4,
      '#required' => true,
      );    
      break;
		case 37 :
      // $title =  t('Get Datalogger Firmware Version');
      break;
		case 38 :
      // $title =  t('Get Datalogger Firmware Version');
      break;
  }
  
  
	$form["submit"] = array(
      "#type" => "submit",
      "#value" => t("Send Now!"),
      "#submit" => array(
          //"_send_command_submit"
      ),
			'#ajax' => array(
      'callback' => '_datalogger_submit_command_callback',
      'wrapper' => 'ajax-command-submit-div',
      'name' => 'submit1',
      'method' => 'replace',
      'effect' => 'fade',
			),
  );
  	
	$form['submit_command_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Command Result'),
    '#prefix' => '<div id="ajax-command-submit-div">',		
    '#suffix' => '</div>',
    //'#attributes' => array('style' => 'display: none;'),    
		// '#value' =>_datalogger_new_result_sms() ,
  );
  	
	
  $form['#validate'][] = '_command_validate';
	// }
	
  return $form;
}
function _command_callback($form, &$form_state) {
  return $form['command_fieldset'];
}

function _datalogger_check_empty($arg1, $arg2){
  return form_set_error($arg1,t('Trường <b>').t($arg2).t('</b> không được để trống'));
}

function _command_validate($form, &$form_state) {
  switch ($form_state["values"]["command_selects"]) {
    case 2 :
      $dt_from = $form_state['values']['date_time_from'];
			$number = $form_state['values']['accumulated_rain_fall'];
      if(empty($dt_from)){
				_datalogger_check_empty('date_time_from', 'Từ ngày');
      }
      $dt_to = $form_state['values']['date_time_to'];
			if(empty($dt_from)){
				_datalogger_check_empty('date_time_to', 'Tới ngày');
      }
      $interval = (strtotime($dt_to) - strtotime($dt_from))/(24*60*60);
      if($interval < 0) {
        form_set_error('date_time_to',t("Thời gian <b>Tới ngày</b> không được nhỏ hơn <b>Từ ngày</b>"));
      }
      else{
        if($interval > 1) {
          form_set_error('date_time_to',t("Thời gian <b>Tới ngày</b> không được lớn hơn <b>Từ ngày</b> quá 24h"));
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
			if(empty($id)){
				_datalogger_check_empty('set_input_id', 'ID');
      }
      elseif (preg_match('/[^a-zA-Z0-9]/i',$id)){
         form_set_error('set_input_id',t('Trường <b>ID</b> không được chứa kí tự đặc biệt.<br>Chỉ được chứa chữ cái, và số'));
      }
      else
        if(strlen($id) != 6) {
          form_set_error('set_input_id',t('Trường <b>ID</b> không đúng định dạng.Bắt buộc phải chứa 6 kí tự'));
        }      
      break;
    case 6 :
      break;
    case 7 :
			$pass = $form_state['values']['set_pass'] ;
			if(empty($pass)){
				_datalogger_check_empty('set_pass', 'Password');
      }
      elseif (preg_match('/[^0-9]/i',$pass)){
         form_set_error('set_pass',t('Trường <b>'.t('Password').'</b> không được chứa kí tự đặc biệt.<br>Chỉ được chứa chữ số'));
      }
      break;
    case 8 :
      break;
    //database Buffer Clear
    case 9 :
      break;
    case 10 :
			$day = $form_state['values']['date_buffer_clear'];
			if(empty($day)){
				_datalogger_check_empty('date_buffer_clear','Ngày tháng');
      }
      break;
    //Rain fall config
    case 11 :
    // ['command_fieldset']['accumulated_rain_fall']
      $number = $form_state['values']['accumulated_rain_fall'];
			if(empty($number)){
				_datalogger_check_empty('accumulated_rain_fall', 'Accumulated Rain Fall Value');
      }
      else{
        // if(($number%10) != 0 || $number < 0){
          // form_set_error('accumulated_rain_fall',t('Giá trị trường <b>').t('Accumulated Rain Fall Value').t('</b> phải dương  và là bội của 10'));
        // }
				// else
				if (preg_match('/[^0-9.]/i',$number)){
         form_set_error('accumulated_rain_fall',t('Trường <b>').t('Accumulated Rain Fall Value').t('</b> chỉ được chứa số.'));
				}
      }
      break;
    case 12 :
			// $time = $form_state['values']['set_rain_fall_clear_time'];
			// dsm($time);
			// if(empty($time)){
				// _datalogger_check_empty('set_rain_fall_clear_time','Thời gian');
      // }
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
				_datalogger_check_empty('bat_on', 'Active Battery Power Voltage (V)');
      }
      else if (preg_match('/[^0-9.]/i',$batOn)){
         form_set_error('bat_on',t('Trường <b>').t('Active Battery Power Voltage (V)').t('</b> chỉ được chứa số.'));
      }
      
			if(empty($batOff)){
				_datalogger_check_empty('bat_on', 'De-Active Battery Power Voltage (V)');
      }
      else if (preg_match('/[^0-9.]/i',$batOff)){
         form_set_error('bat_off',t('Trường <b>').t('De-Active Battery Power Voltage (V)').t('</b> chỉ được chứa số.'));
      }
      break;
    case 16 :
      // $title =  t('Get Active / De-Active Battery Power Voltage');
      break;
    case 17 :
      // $title =  t('Set Battery Voltage Offset');   
      $vol = $form_state['values']['set_bat_vol'];
			if(empty($vol)){
				_datalogger_check_empty('set_bat_vol', 'Battery Voltage Offset (V)');
      }
      else if (preg_match('/[^0-9.]/i',$vol)){
         form_set_error('set_bat_vol',t('Trường <b>').t('Battery Voltage Offset (V)').t('</b> chỉ được chứa số.'));
      }
      break;
    case 18 :
      // $vol = $form_state['values']['get_bat_vol'];
			// if(empty($vol)){
				// _datalogger_check_empty('get_bat_vol', 'Battery Voltage Offset (V)');
      // }
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
      // $interval = $form_state['values']['set_interval'];
			
			// if(empty($interval)){
				// _datalogger_check_empty('set_interval', 'Data Send Interval Minutes');
      // }
      // else{
        // if(($interval % 10) != 0  || $interval > 180 || $interval < 0){
          // form_set_error('set_interval',t('Trường <b>').t('Data Send Interval Minutes').t('</b> Phải là bội của 10, không âm và nhỏ hơn 180 .')); 
        // }       
        // else if (preg_match('/[^0-9]/i',$interval)){
          // form_set_error('set_interval',t('Trường <b>').t('Data Send Interval Minutes').t('</b> chỉ được chứa số.'));
        // }
      // }
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
      $id = $form_state['values']['id_gprs'];
      $pass = $form_state['values']['pass_gprs']; 
			if(empty($host)){
				_datalogger_check_empty('id_gprs', 'Host');
      }
      else{
        if(!filter_var($host, FILTER_VALIDATE_IP)){
          form_set_error('host_gprs',t('Trường <b>').t('Host').t('</b> không đúng định dạng. xxx.xxx.xxx.xxx<br>Hay nhập lại.'));
        }      
      }
      break;
    case 30 :
      // $title =  t('Get GPRS Network Setting');
      break;
    case 31 :
      $host = $form_state['values']['set_host'];
			if(empty($host)){
				_datalogger_check_empty('set_host', 'Host');
      }
      $port = $form_state['values']['set_port'];
			if(empty($port)){
				_datalogger_check_empty('set_port', 'Port');
      }
      if(!filter_var($host, FILTER_VALIDATE_IP)){
          form_set_error('set_host',t('Trường <b>').t('Host').t('</b> không đúng định dạng. xxx.xxx.xxx.xxx<br>Hay nhập lại.'));
      }
      else{
        if (preg_match('/[^0-9]/i',$port)){
          form_set_error('set_port',t('Trường <b>').t('Port').t('</b> chỉ được chứa ký tự số.'));
        }       
      }
      break;
    case 32 :
      // $title =  t('Get Host Network Infomation');
      break;
    case 33 :
      // $title =  t('Set Host Phone Number');
      $host = $form_state['values']['host_phone'];
      if(empty($host)){
        _datalogger_check_empty('host_phone','Host Phone Number');
      }
      break;
    case 34 :
      // $title =  t('Get Host Phone Number');
      break;
    //Get datalogger firmware version
    case 35 :
      // $title =  t('Get Datalogger Firmware Version');
      break;
		case 36 :
			$interval = $form_state['values']['set_alarm'];
			if(empty($interval)){
				_datalogger_check_empty('set_alarm', 'Interval');
      }
			elseif (preg_match('/[^0-9]/i',$interval)){
          form_set_error('set_alarm',t('Trường <b>').t('Interval').t('</b> chỉ được chứa ký tự số.'));
      }
			
      $level = $form_state['values']['set_level'];
			if(empty($level)){
				_datalogger_check_empty('set_level', 'Level');
      }
			//elseif (preg_match('/([0-9]|\.)/i', $level)){
      if (!preg_match('/^[0-9\.]+$/', $level)){         // include .
          form_set_error('set_level',t('Trường <b>').t('Level').t('</b> chỉ được chứa ký tự số và dấu chấm thập phân.'));
      }
			break;
		case 37 :
			break;
		case 38 :
			break;
  }
}

function _datalogger_add_space($sms, $length){
	$len = strlen($sms);
	if($len < $length){
		for($i = 0; $i < ($length - $len); $i++){
			$sms .= ' ';  
		}
	}
	return $sms;
}

function _send_command_submit($form, &$form_state) {

  $nid = intval(arg(1)) ? intval(arg(1)) : $form_state['values']['nid'];
  $form['nid'] = array(
    '#type' => 'hidden', 
    '#value' => $nid,
  );
  
	if(!empty($form_state['values']['select'])){
		// $select = $form_state['values']['select'];
		$select = 1;
	}
	else{
		$select = $form_state["values"]["command_selects"];
	}
	
  return _datalogger_send_command($nid, $select,$form, $form_state);
}

function _view_translate_station() {
  return digipro_views_get_view_result("arg_all_datalogger", "page", null,
      true, false);
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
    global $language_content;
    switch ($language_content->language) {
      case "en":
        switch ($view->name) {
          case "logs_management":
            $view->field['title']->options['label'] = 'Name Log';
            $view->field['field_event_type']->options['label'] = 'Event Type';
            $view->field['created']->options['label'] = 'Post Date';
            $view->field['counter']->options['label'] = 'No.';
            break;
          case "arg_all_datalogger":
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