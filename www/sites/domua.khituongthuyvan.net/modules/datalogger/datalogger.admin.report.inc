<?php


/* BKT14*/
function _datalogger_report_rainfall_month_form($form, &$form_state) {
	//drupal_set_title(t('Report monthly rainfall data'));
 
	_datalogger_select_area_province_station($form, $form_state);
  
  
	$form['stations_fieldset']['day']['#access']=FALSE;
	
	$form["submit2"] = array(
      "#type" => "submit",
      "#value" => t("Report"),
      "#submit" => array(
          "_datalogger_report_rainfall_month2_submit"
      ),
  ); 
  return $form;
}

function _datalogger_report_rainfall_month2_submit(&$form, &$form_state) {
	module_load_include('inc', 'datalogger', 'datalogger.admin.excel');
	module_load_include('inc', 'datalogger', 'datalogger.admin.excel.month');
	$nid = $form_state['values']['station'];
	$year = $form_state['values']['year'];	
  $month = $form_state['values']['month'];
  
  //dpm($form_state['values']);
  
	if($month < 10){
		$month = '0'.$month;
	}
	$year_month = $year.$month;
	$name_qtv = $form_state['values']['txtNameQTV'];
	$name_nlb = $form_state['values']['txtNameNLB'];
	$name_ks = $form_state['values']['txtNameKS'];
	$name_pt = $form_state['values']['txtNamePT'];
	
	// $rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year_month, 'all');
	/*
	$month_days_number = cal_days_in_month(CAL_GREGORIAN, substr($year_month, -2), $year);
	for($day = 1; $day <= $month_days_number; $day++){
		if(($day) < 10){
			$day_time = '0'.($day);
		}
		else{
			$day_time = $day;
		}
		$max_rainfall_in_day = 0;
		$max_time_rainfall_in_day = 0;
		$hours_in_day = array();
		$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year_month, $year_month.$day_time);
		if(count(rainfalls) > 0){
			foreach($rainfalls as $rainfall){
				$hour = (int)substr($rainfall->node_title, -8, 2);
				$rainfall_measuring = (float)$rainfall->field_field_rainfall_measuring[0]['rendered']['#markup'];
				if($rainfall_measuring > 0){
					$hours_in_day[$hour][] = $rainfall;
					$total_rainfall_in_day += $rainfall_measuring;
					$time_rainfall_in_day +=10;
					$max_time_rainfall_in_day = ($max_time_rainfall_in_day < $time_rainfall_in_day)?$time_rainfall_in_day:$max_time_rainfall_in_day;
					$max_rainfall_in_day = ($max_rainfall_in_day < $total_rainfall_in_day)?$total_rainfall_in_day:$max_rainfall_in_day; 
				}
				else{
					$total_rainfall_in_day = 0;
					$time_rainfall_in_day =0;
				}
			}
			for($i = 23; $i >= 0; $i--){
				$number = count($hours_in_day[$i]);
				$total_rainfall_in_hour = 0;
				$time_rainfall_in_hour = 0;
				$max_rainfall_in_hour = 0; 
				if($number > 0){
					for($j = 0; $j < $number; $j++){
						$rainfall_measuring = (float)$hours_in_day[$i][$j]->field_field_rainfall_measuring[0]['rendered']['#markup'];
						$total_rainfall_in_hour += $rainfall_measuring;
						$time_rainfall_in_hour +=10;
						$max_rainfall_in_hour = ($max_rainfall_in_hour < $rainfall_measuring) ? $rainfall_measuring : $max_rainfall_in_hour; 
					}
					$hours_in_day[$i] = array('max_rainfall_in_hour' => $max_rainfall_in_hour, 
						'total_rainfall_in_hour' => $total_rainfall_in_hour, 
						'time_rainfall_in_hour' => $time_rainfall_in_hour);
				}
				else{
					$hours_in_day[$i] = array('max_rainfall_in_hour' => 0, 
						'total_rainfall_in_hour' => 0, 
						'time_rainfall_in_hour' => 0);
				}
			}
		}
		else{
			for($i = 23; $i >=0; $i--){
				$hours_in_day[$i] = array('max_rainfall_in_hour' => 0, 
						'total_rainfall_in_hour' => 0, 
						'time_rainfall_in_hour' => 0);
			}
		}
		$day_of_month[$day]= array('max_rainfall_in_day' => $max_rainfall_in_day,
			'max_time_rainfall_in_day' => $max_time_rainfall_in_day, 
			'hours_in_day' => $hours_in_day);
	}
	*/
	// dsm($day_of_month);
	// /*
	
	
	$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year_month, 'all');
	// $rainfalls_month = views_get_view_result('view_rainfall_hour_time','default', $nid, $year, $year_month,all);
	if(count($rainfalls) <= 0){
		drupal_set_message(t('Rainfall stations in the no data to report'),'error');
	}
	else{
		_datalogger_export_rainfall_month_excel($nid, $year, $year_month);
	}
	// */
}
