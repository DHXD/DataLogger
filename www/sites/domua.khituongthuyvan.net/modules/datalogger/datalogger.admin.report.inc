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
	
	
	// kiem tra trong ham _datalogger_export_rainfall_month_excel().
	///$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $year_month, 'all');
	
	/*if(count($rainfalls) <= 0){
		drupal_set_message(t('Rainfall stations in the no data to report'),'error');
	}
	else{*/
		_datalogger_export_rainfall_month_excel($nid, $year, $year_month, $form_state);
	//}
	// */
}
