<?php
function _datalogger_export_rainfall_station_day_excel($region, $province, $station_nids, $year, $month, $day){
  error_reporting(0);
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel.php';
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel/IOFactory.php';
	module_load_include('inc', 'datalogger', 'datalogger.admin');

	$number = count($station_nids);
	//lay du lieu cua tram
	foreach($station_nids as $nid){
		$station = node_load($nid);
		$max_rainfall_in_day = 0;
		$max_total_rainfall_in_day = 0;
		$max_total_time_rainfall_in_day = 0;
		$hours_in_day = array();
		$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $month, $day);
		if(count(rainfalls) > 0){
			foreach($rainfalls as $rainfall){
				$hour = (int)substr($rainfall->node_title, -8, 2);
				$rainfall_measuring = (float)$rainfall->field_field_rainfall_measuring[0]['rendered']['#markup'];
				if($rainfall_measuring > 0){
					$hours_in_day[$hour][] = $rainfall;
					$total_rainfall_in_day += $rainfall_measuring;
					$time_rainfall_in_day +=10;
					$max_total_time_rainfall_in_day = ($max_total_time_rainfall_in_day < $time_rainfall_in_day) ? $time_rainfall_in_day : $max_total_time_rainfall_in_day;
					$max_total_rainfall_in_day = ($max_total_rainfall_in_day < $total_rainfall_in_day) ? $total_rainfall_in_day : $max_total_rainfall_in_day; 
				}
				else{
					$total_rainfall_in_day = 0;
					$time_rainfall_in_day =0;
				}
			}
			for($i = 23; $i >= 0; $i--){
				$number_for = count($hours_in_day[$i]);
				$total_rainfall_in_hour = 0;
				$time_rainfall_in_hour = 0;
				$max_rainfall_in_hour = 0; 
				if($number_for > 0){
					for($j = 0; $j < $number_for; $j++){
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
				$max_rainfall_in_day = ($max_rainfall_in_day < $hours_in_day[$i]['max_rainfall_in_hour']) ? $hours_in_day[$i]['max_rainfall_in_hour'] : $max_rainfall_in_day; 
			}
		}
		else{
			for($i = 23; $i >=0; $i--){
				$hours_in_day[$i] = array('max_rainfall_in_hour' => 0, 
						'total_rainfall_in_hour' => 0, 
						'time_rainfall_in_hour' => 0);
			}
		}
		$stations[]= array(
			'station_name' => $station->title,
			'max_total_rainfall_in_day' => $max_total_rainfall_in_day,
			'max_total_time_rainfall_in_day' => $max_total_time_rainfall_in_day, 
			'max_rainfall_in_day' => $max_rainfall_in_day,
			'hours_in_day' => $hours_in_day
		);
	}
	/*-----------------------------------------------------------------------------------------------------------*/
	
  $objPHPExcel = new PHPExcel();
  $objPHPExcel->getProperties()->setCreator("Datalogger")
                 ->setLastModifiedBy("Datalogger")
                 ->setTitle("Office 2007 XLSX Document")
                 ->setSubject("Office 2007 XLSX Document")
                 ->setDescription("Document for Office 2007 XLSX")
                 ->setKeywords("office 2007 openxml php")
                 ->setCategory("Test result file");
	$objPHPExcel->setActiveSheetIndex();
	$objPHPExcel->getActiveSheet()->setCellValue('A1', 'Bảng thống kê lượng mưa trong ngày');
	$objPHPExcel->getActiveSheet()->setCellValue('A2', 'Đài khu vực');
	$objPHPExcel->getActiveSheet()->setCellValue('H2', 'Tỉnh');
	$objPHPExcel->getActiveSheet()->setCellValue('S2', 'Ngày');
	$objPHPExcel->getActiveSheet()->setCellValue('U2', 'Tháng');
	$objPHPExcel->getActiveSheet()->setCellValue('W2', 'Năm');
	$objPHPExcel->getActiveSheet()->setCellValue('A3', 'Trạm đo mưa \Giờ');
	//sheet luôn bắt đầy từ 0
	$objPHPExcel->setActiveSheetIndex(0);
	//thiet lap header
	for($i =0; $i < 24; $i++){
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'3', $i+1);
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'4', '|');
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'5', $i);
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'6', $i+1);
	}
	$objPHPExcel->getActiveSheet()->setCellValue('AA3', 'Tổng số');
	$objPHPExcel->getActiveSheet()->setCellValue('AA4', 'mm');
	$objPHPExcel->getActiveSheet()->setCellValue('AA5', 'phút');
	$objPHPExcel->getActiveSheet()->setCellValue('AA6', '25');
	
	for($i = 0; $i < ($number*2); $i++){
		if($i%2 == 0){
			for($j = 0; $j < 24; $j++){
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($i+7), '0');
			}
			$objPHPExcel->getActiveSheet()->mergeCells('A'.($i+7).':B'.($i+8));
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+7), '=SUM(C'.($i+7).':Z'.($i+7).')');
		}
		else{
			for($j =0; $j < 24; $j++){
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($i+7), '0');
			}
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+7), '=SUM(C'.($i+7).':Z'.($i+7).')');
		}
	}
	
	
	$objPHPExcel->getActiveSheet()->mergeCells('A1:AA1');
	$objPHPExcel->getActiveSheet()->mergeCells('C2:G2');
	$objPHPExcel->getActiveSheet()->mergeCells('I2:P2');
	$objPHPExcel->getActiveSheet()->mergeCells('A3:B6');
	
	$styleThinBlackBorderOutline = array(
		'borders' => array(
			'outline' => array(
				'style' => PHPExcel_Style_Border::BORDER_THIN,
				'color' => array('argb' => 'FF000000'),
			),
		),	
	);

	$sharedStyle1 = new PHPExcel_Style();
	$sharedStyle1->applyFromArray(
		array(//'fill' 	=> array(
				'borders' => array(
									'bottom'	=> array('style' => PHPExcel_Style_Border::BORDER_THIN),
									'right'		=> array('style' => PHPExcel_Style_Border::BORDER_THIN)
								)
			 ));
	$objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle1, 'A1:AA'.(($number+3)*2));

	//chinh vi tri cac cell 
	$objPHPExcel->getActiveSheet()->getStyle('A1:AA'.(($number+3)*2))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('A1:C'.(($number+3)*2))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	//thiet lap chieu rong cac cell
	$objPHPExcel->getActiveSheet()->getStyle('A1')->getFont()->setSize(30);
	$objPHPExcel->getActiveSheet()->getColumnDimension('A')->setWidth(10);
	$objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(10);
	$objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('F')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('G')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('H')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('I')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('J')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('K')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('L')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('M')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('N')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('O')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('P')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('Q')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('R')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('S')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('T')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('U')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('V')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('W')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('X')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('Y')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('Z')->setWidth(5);
	$objPHPExcel->getActiveSheet()->getColumnDimension('AA')->setWidth(10);
	
	$font_bold = array(
		'font' => array(
		'bold' => true
		)
	);

	for($index = 0; $index < $number*2; $index++){
		if($index%2 == 0){
			$objPHPExcel->getActiveSheet()->setCellValue('A'.($index+7), $stations[$index/2]['station_name']);
			for($j = 0; $j < 24 ; $j++){
				$total = $stations[$index/2]['hours_in_day'][$j]['total_rainfall_in_hour'];
				$time = $stations[$index/2]['hours_in_day'][$j]['time_rainfall_in_hour'];
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($index+7),$total);
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($index+8),$time);
				if($total > 0 && $time > 0){
					$objPHPExcel->getActiveSheet()->getStyle(chr(67+$j).($index+7))->applyFromArray($font_bold);
					$objPHPExcel->getActiveSheet()->getStyle(chr(67+$j).($index+8))->applyFromArray($font_bold);
				}
			}
		}
	}
	
	$objPHPExcel->getActiveSheet()->setCellValue('C2',$region);//khu vuc
	$objPHPExcel->getActiveSheet()->setCellValue('I2',$province);//tinh
	
	$objPHPExcel->getActiveSheet()->setCellValue('T2',substr($day,-2));//ngay
	$objPHPExcel->getActiveSheet()->setCellValue('V2',substr($month,-2));//thang
	$objPHPExcel->getActiveSheet()->setCellValue('X2',$year);//nam
	
		

	/** Include PHPExcel_IOFactory */
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
  
  header('Content-type: application/vnd.ms-excel');
  header('Content-Disposition: attachment; filename="Báo cáo dữ liệu mưa - Trạm ' . $name_station->title . ' - ' . date('m',time()) . '-' . date('Y',time()) . '.xls"');
  //$objWriter->save('php://output');
  $abc = file_directory_temp() . '/Bao cao du lieu mua trong ngay_' . time() . '.xls';
  $objWriter->save($abc);
  files($abc);
  drupal_unlink($abc);
  drupal_exit();
}