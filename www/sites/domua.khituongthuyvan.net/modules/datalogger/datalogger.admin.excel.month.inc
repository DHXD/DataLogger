<?php

function _datalogger_export_rainfall_month_excel($nid, $year, $month){
  error_reporting(0);
  //error_reporting(E_ALL);
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel.php';

	module_load_include('inc', 'datalogger', 'datalogger.admin');
  
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel/IOFactory.php';
  
/*
  //$target ='Results/';
  //$fileType = 'Excel2007';   
  $InputFileName = 'd:/Coder/DataLogger/BKT14/BKT14-2-unicode.XLSx';
  //$OutputFileName =  $target . '_Result.xlsx';

   //Read the file (including chart template) 
  $objReader = PHPExcel_IOFactory::createReader('Excel2007'); 
  $objReader->setIncludeCharts(TRUE);
  $objPHPExcel = $objReader->load($InputFileName); 
  
  
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
  header('Content-type: application/vnd.ms-excel');
  header('Content-Disposition: attachment; filename="Báo cáo dữ liệu mưa - Trạm ' . $name_station->title . ' - ' . date('m',time()) . '-' . date('Y',time()) . '.xlsx"');
  $objWriter->save('php://output');
  drupal_exit();
  */
  
  
	if($nid != ''){
		$name_station = node_load($nid);
	}
	else{
		$name_station = '';
	}
	
	//lay du lieu cua tram
	$month_days_number = cal_days_in_month(CAL_GREGORIAN, substr($month, -2), $year);
	for($day = 1; $day <= $month_days_number; $day++){
		if(($day) < 10){
			$day_time = '0'.($day);
		}
		else{
			$day_time = $day;
		}
		$max_rainfall_in_day = 0;
		$max_total_rainfall_in_day = 0;
		$max_total_time_rainfall_in_day = 0;
		$hours_in_day = array();
		$rainfalls = views_get_view_result('view_export_excel','default', $nid, $year, $month, $month.$day_time);
		if(count(rainfalls) > 0){
			foreach($rainfalls as $rainfall){
				$hour = (int)substr($rainfall->node_title, -8, 2);
				$rainfall_measuring = (float)$rainfall->field_field_rainfall_measuring[0]['rendered']['#markup'];
				if($rainfall_measuring > 0){
					$hours_in_day[$hour][] = $rainfall;
					$total_rainfall_in_day += $rainfall_measuring;
					$time_rainfall_in_day +=10;
					$max_total_time_rainfall_in_day = ($max_total_time_rainfall_in_day < $time_rainfall_in_day)?$time_rainfall_in_day:$max_total_time_rainfall_in_day;
					$max_total_rainfall_in_day = ($max_total_rainfall_in_day < $total_rainfall_in_day)?$total_rainfall_in_day:$max_total_rainfall_in_day; 
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
		$day_of_month[$day]= array('max_total_rainfall_in_day' => $max_total_rainfall_in_day,
			'max_total_time_rainfall_in_day' => $max_total_time_rainfall_in_day, 
			'max_rainfall_in_day' => $max_rainfall_in_day,
			'hours_in_day' => $hours_in_day);
	}
	/*-----------------------------------------------------------------------------------------------------------*/
	
  $objPHPExcel = new PHPExcel();
  $objPHPExcel->getProperties()->setCreator("Datalogger")
                 ->setLastModifiedBy("Datalogger")
                 ->setTitle("Datalogger BKT14")
                 ->setSubject("BKT14")
                 ->setDescription("Document for Office 2007 XLSX")
                 ->setKeywords("Datalogger")
                 ->setCategory("Datalogger");
	$objPHPExcel->setActiveSheetIndex();
	$objPHPExcel->getActiveSheet()->setCellValue('C1', 'Trạm');
	$objPHPExcel->getActiveSheet()->setCellValue('G1', 'Tháng');
	$objPHPExcel->getActiveSheet()->setCellValue('I1', 'Năm');
	$objPHPExcel->getActiveSheet()->setCellValue('A2', 'Ngày \Giờ');
  
  
	// $month_days_number = cal_days_in_month(CAL_GREGORIAN, substr($month, -2), $year);
	/*++++++++++++++tao sheet 1++++++++++++++++++++++++*/
	// $objPHPExcel->createSheet();
	//sheet từ 0
	$objPHPExcel->setActiveSheetIndex(0);
  
	//thiet lap header
	for($i =0; $i < 24; $i++){
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'2', $i+1);
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'3', '|');
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'4', $i);
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'5', $i+1);
	}
	$objPHPExcel->getActiveSheet()->setCellValue('AA2', 'Tổng số');
	$objPHPExcel->getActiveSheet()->setCellValue('AA3', 'mm');
	$objPHPExcel->getActiveSheet()->setCellValue('AA4', 'phút');
	$objPHPExcel->getActiveSheet()->setCellValue('AA5', '25');
	$k = 1;
	//gan gia tri mac dinh cho cac o
	// /*
	for($i = 0; $i < $month_days_number*2; $i++){
		if($i%2 == 0){
			$objPHPExcel->getActiveSheet()->setCellValue(chr(65).($i+6), $k++);
			for($j = 0; $j < 24; $j++){
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($i+6), '0');
			}
			$objPHPExcel->getActiveSheet()->mergeCells('A'.($i+6).':B'.($i+7));
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+6), '=SUM(C'.($i+6).':Z'.($i+6).')');
		}
		else{
			for($j =0; $j < 24; $j++){
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($i+6), '0');
			}
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+6), '=SUM(C'.($i+6).':Z'.($i+6).')');
		}
	}
	// */
	/*
	for($i =0; $i < $month_days_number*2; $i++){
		if($i%2 == 0){
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+6), '=SUM(C'.($i+6).':Z'.($i+6).')');
		}
		else{
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+6), '=SUM(C'.($i+6).':Z'.($i+6).')');
		}
	}
	*/
	$objPHPExcel->getActiveSheet()->setCellValue('A'.(($month_days_number+3)*2), 'Tổng số');
	$objPHPExcel->getActiveSheet()->setCellValue('B'.(($month_days_number+3)*2), 'mm');
	$objPHPExcel->getActiveSheet()->setCellValue('B'.(($month_days_number+3)*2+1), 'Phút');
	
	// $mm =0;
	// $minute = 0;
	for($j = 0; $j < 24; $j++){
		$str_rainfall = '';
		$str_time = '';
		for($i = 0; $i < $month_days_number*2; $i++){
			if($i%2 == 0){
				$str_rainfall = $str_rainfall.','.(chr(67+$j).($i+6));
			}
			else{
				$str_time = $str_time.','.(chr(67+$j).($i+6));
			}
		}
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).(($month_days_number+3)*2), '=SUM('.$str_rainfall.')');
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).(($month_days_number+3)*2+1), '=SUM('.$str_time.')');
	}
	
	$objPHPExcel->getActiveSheet()->mergeCells('A'.(($month_days_number+3)*2).':A'.(($month_days_number+3)*2+1));
	$objPHPExcel->getActiveSheet()->mergeCells('A2:B5');
	$objPHPExcel->getActiveSheet()->mergeCells('C1:D1');
	$objPHPExcel->getActiveSheet()->mergeCells('E1:F1');
	
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
	$objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle1, 'A1:AA'.(($month_days_number+3)*2+1));

	//chinh vi tri cac cell 
	$objPHPExcel->getActiveSheet()->getStyle('A1:AA'.(($month_days_number+3)*2+1))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('A1:C'.(($month_days_number+3)*2+1))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	//thiet lap chieu rong cac cell
	$objPHPExcel->getActiveSheet()->getColumnDimension('A')->setWidth(1.5);
  for($c = 'B'; $c <= 'Z'; $c++)
    $objPHPExcel->getActiveSheet()->getColumnDimension($c)->setWidth(2.9);
	
	$objPHPExcel->getActiveSheet()->getColumnDimension('AA')->setWidth(4.72);
  $objPHPExcel->getActiveSheet()->setTitle('Trang 2');
	
	// /*
	//chen du lieu vao bao cao
	$objPHPExcel->getActiveSheet()->setCellValue('E1', $name_station->title);
	$objPHPExcel->getActiveSheet()->setCellValue('H1', substr($month,-1,2));
	$objPHPExcel->getActiveSheet()->setCellValue('J1',$year);
	/*
	for($day = 1; $day < $month_days_number*2; $day++){
		if(($day%2) == 0){
			if(($day/2) < 10){
				$day_time = '0'.($day/2);
			}
			else{
				$day_time = $day/2;
			}
			$rainfalls = views_get_view_result('view_rainfall_hour_time','default', $nid, $year, $month, $month.$day_time);
			for($j =0; $j < 24; $j++){
				if(count($rainfalls) == 24){
					$rainfall_total = $rainfalls[23 - $i]->field_field_rainfall_total[0]['rendered']['#markup'];
					$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($day+6),$rainfall_total);
				}
				else{
					for($k = 0; $k < count($rainfalls); $k++){
						$hour_time = (int)substr($rainfalls[$k]->field_field_rainfall_hour_time[0]['rendered']['#markup'],0,2);
						if($j == $hour_time){
							$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($day+4),$rainfalls[$k]->field_field_rainfall_total[0]['rendered']['#markup']);
						}
					}
				}
			}
		}
	}
	*/
	// 
	$font_bold = array(
		'font' => array(
		'bold' => true
		)
	);
	$day_in_month = 1;
	for($day = 0; $day < $month_days_number*2; $day++){
		if($day%2 == 0){
			for($j = 0; $j < 24 ; $j++){
				$total = $day_of_month[$day_in_month]['hours_in_day'][$j]['total_rainfall_in_hour'];
				$time = $day_of_month[$day_in_month]['hours_in_day'][$j]['time_rainfall_in_hour'];
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($day+6),$total);
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($day+7),$time);
				if($total > 0 && $time > 0){
					$objPHPExcel->getActiveSheet()->getStyle(chr(67+$j).($day+6))->applyFromArray($font_bold);
					$objPHPExcel->getActiveSheet()->getStyle(chr(67+$j).($day+7))->applyFromArray($font_bold);
				}
			}
			$day_in_month++;
		}
	}
	//
	
	/*++++++++++++++++++tao sheet 2++++++++++++++++++++++++++*/
	$objPHPExcel->createSheet();
	$objPHPExcel->setActiveSheetIndex(1);
	$objPHPExcel->getActiveSheet()->setCellValue('B1', 'Trạm');
	$objPHPExcel->getActiveSheet()->setCellValue('F1', 'Tháng');
	$objPHPExcel->getActiveSheet()->setCellValue('H1', 'Năm');
	$objPHPExcel->getActiveSheet()->setCellValue('A2', 'LƯỢNG GIÁNG THỦY LỚN NHẤT');
	$objPHPExcel->getActiveSheet()->setCellValue('B3', 'Trong 60 phút');
	$objPHPExcel->getActiveSheet()->setCellValue('D3', 'Trong một đợt liên tục');
	$objPHPExcel->getActiveSheet()->setCellValue('F2', 'CỰC TRỊ TRONG THÁNG');
	$objPHPExcel->getActiveSheet()->setCellValue('A3', 'Ngày');
	$objPHPExcel->getActiveSheet()->setCellValue('B4', 'Lượng');
	$objPHPExcel->getActiveSheet()->setCellValue('C4', 'Thời gian');
	$objPHPExcel->getActiveSheet()->setCellValue('D4', 'Lượng');
	$objPHPExcel->getActiveSheet()->setCellValue('E4', 'Thời gian');
	$objPHPExcel->getActiveSheet()->setCellValue('B5', '(mm)');
	$objPHPExcel->getActiveSheet()->setCellValue('C5', 'kéo dài');
	$objPHPExcel->getActiveSheet()->setCellValue('D5', '(mm)');
	$objPHPExcel->getActiveSheet()->setCellValue('E5', 'kéo dài');
	$objPHPExcel->getActiveSheet()->setCellValue('C6', '(phút)');
	$objPHPExcel->getActiveSheet()->setCellValue('E6', '(giờ, phút)');
	$objPHPExcel->getActiveSheet()->setCellValue('H4', 'Lượng');
	$objPHPExcel->getActiveSheet()->setCellValue('I4', 'Thời gian kéo dài');
	$objPHPExcel->getActiveSheet()->setCellValue('H6', '(mm)');
	$objPHPExcel->getActiveSheet()->setCellValue('I6', '(giờ, phút)');
	$objPHPExcel->getActiveSheet()->setCellValue('F8', 'Trong một giờ');
	
	$objPHPExcel->getActiveSheet()->setCellValue('F10', 'Trong một đợt liên tục');
	$objPHPExcel->getActiveSheet()->setCellValue('G13', 'GHI CHÚ');

	$objPHPExcel->getActiveSheet()->setCellValue('B7', '1');
	$objPHPExcel->getActiveSheet()->setCellValue('C7', '2');
	$objPHPExcel->getActiveSheet()->setCellValue('D7', '3');
	$objPHPExcel->getActiveSheet()->setCellValue('E7', '4');
	
	//phan ghi chú:
	$objPHPExcel->getActiveSheet()->setCellValue('F15', 'Quan trắc viên');
	$objPHPExcel->getActiveSheet()->setCellValue('F16', 'Người lập bảng');
	$objPHPExcel->getActiveSheet()->setCellValue('F17', 'Người kiểm soát');
	$objPHPExcel->getActiveSheet()->setCellValue('F18', 'Người phúc thẩm');
	
	
	$objPHPExcel->getActiveSheet()->mergeCells('A2:E2');
	$objPHPExcel->getActiveSheet()->mergeCells('A3:A6');
	$objPHPExcel->getActiveSheet()->mergeCells('B3:C3');
	$objPHPExcel->getActiveSheet()->mergeCells('D3:E3');
	$objPHPExcel->getActiveSheet()->mergeCells('F2:J3');
	$objPHPExcel->getActiveSheet()->mergeCells('F4:G7');
	$objPHPExcel->getActiveSheet()->mergeCells('H4:H5');
	$objPHPExcel->getActiveSheet()->mergeCells('I4:J5');
	$objPHPExcel->getActiveSheet()->mergeCells('I6:J6');
	$objPHPExcel->getActiveSheet()->mergeCells('F8:G9');
	$objPHPExcel->getActiveSheet()->mergeCells('H8:H9');
	$objPHPExcel->getActiveSheet()->mergeCells('I8:J9');
	$objPHPExcel->getActiveSheet()->mergeCells('F10:G11');
	$objPHPExcel->getActiveSheet()->mergeCells('H10:H11');
	$objPHPExcel->getActiveSheet()->mergeCells('I10:J11');

	$styleThinBlackBorderOutline = array(
		'borders' => array(
			'outline' => array(
				'style' => PHPExcel_Style_Border::BORDER_THIN,
				'color' => array('argb' => 'FF000000'),
			),
		),
	);
	$objPHPExcel->getActiveSheet()->getStyle('A2:J'.($month_days_number+7))->applyFromArray($styleThinBlackBorderOutline);

	$objPHPExcel->getActiveSheet()->getStyle('A2:E2')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('A3:A6')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('B3:C3')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('D3:E3')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('B4:B6')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('C4:C6')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('D4:D6')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('E4:E6')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('F4:G7')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('F2:J3')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('H4:H7')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('I4:J7')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('F8:G9')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('H8:H9')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('I8:J9')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('F10:G11')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('H10:H11')->applyFromArray($styleThinBlackBorderOutline);
	$objPHPExcel->getActiveSheet()->getStyle('I10:J11')->applyFromArray($styleThinBlackBorderOutline);


	$sharedStyle1 = new PHPExcel_Style();
	$sharedStyle1->applyFromArray(
		array(//'fill' 	=> array(
				'borders' => array(
									'bottom'	=> array('style' => PHPExcel_Style_Border::BORDER_THIN),
									'right'		=> array('style' => PHPExcel_Style_Border::BORDER_THIN)
								)
			 ));

	$objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle1, 'A7:E'.($month_days_number+7));
	$objPHPExcel->getActiveSheet()->getStyle('B1')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT);
	$objPHPExcel->getActiveSheet()->getStyle('F1')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_RIGHT);
	$objPHPExcel->getActiveSheet()->getStyle('J1')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT);
	$objPHPExcel->getActiveSheet()->getStyle('G13')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT);
	$objPHPExcel->getActiveSheet()->getStyle('A2')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);


	$objPHPExcel->getActiveSheet()->getStyle('A3')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('A3')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F2')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F2')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F4')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F4')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('H4')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('H4')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('I4')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('I4')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('H8')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('H8')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('I8')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('I8')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('H10')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('H10')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('I10')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('I10')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F8')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F8')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F10')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$objPHPExcel->getActiveSheet()->getStyle('F10')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);

	$styleAlignments = array(
					'alignment' => array(
					'horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER,
					)
	);
	$objPHPExcel->getActiveSheet()->getStyle('A2:E165')->applyFromArray($styleAlignments);
	$objPHPExcel->getActiveSheet()->getStyle('F2:I10')->applyFromArray($styleAlignments);
	$objPHPExcel->getActiveSheet()->getStyle('F2:I10')->applyFromArray(
			array(
					'alignment' => array(
					'horizontal' => PHPExcel_Style_Alignment::VERTICAL_CENTER,
					)
				)
	);
	$objPHPExcel->getActiveSheet()->getColumnDimension('A')->setWidth(25);
	$objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(15);
	$objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(15);
	$objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(15);
	$objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(15);
	$objPHPExcel->getActiveSheet()->getColumnDimension('F')->setWidth(15);
	$objPHPExcel->getActiveSheet()->getColumnDimension('H')->setWidth(10);
	$objPHPExcel->getActiveSheet()->getColumnDimension('I')->setWidth(15);
	//tram do mưa
	$objPHPExcel->getActiveSheet()->setCellValue('C1', $name_station->title);
	
	$objPHPExcel->getActiveSheet()->setCellValue('G1',substr($month,-1,2));
	$objPHPExcel->getActiveSheet()->setCellValue('I1', $year);
	$objPHPExcel->getActiveSheet()->setCellValue('H8' , '=MAX(B8:B'.($month_days_number+7).')');
	$objPHPExcel->getActiveSheet()->setCellValue('I8', '=MAX(C8:C'.($month_days_number+7).')');
	$objPHPExcel->getActiveSheet()->setCellValue('H10' , '=MAX(D8:D'.($month_days_number+7).')');
	$objPHPExcel->getActiveSheet()->setCellValue('I10', '=MAX(E8:E'.($month_days_number+7).')');

	// $objPHPExcel->getActiveSheet()->setCellValue('G15', "$name_qtv");
	// $objPHPExcel->getActiveSheet()->setCellValue('G16', "$name_nlb");
	// $objPHPExcel->getActiveSheet()->setCellValue('G17', "$name_ks");
	// $objPHPExcel->getActiveSheet()->setCellValue('G18', "$name_pt");
	 
	//set font
	$objPHPExcel->getActiveSheet()->getStyle('A1:J'.($month_days_number+7))->getFont()->setName('Times New Roman');
	$objPHPExcel->getActiveSheet()->getStyle('A2:J7')->getFont()->setSize(12);
	$objPHPExcel->getActiveSheet()->getStyle('B8:E'.($month_days_number+7))->getFont()->setSize(12);
	$objPHPExcel->getActiveSheet()->getStyle('B1')->getFont()->setSize(14);
	$objPHPExcel->getActiveSheet()->getStyle('F1:H1')->getFont()->setSize(12);
	$objPHPExcel->getActiveSheet()->getStyle('J1')->getFont()->setSize(10);
	$objPHPExcel->getActiveSheet()->getStyle('F4:G7')->getFont()->setSize(10);
	$objPHPExcel->getActiveSheet()->getStyle('H8:J11')->getFont()->setSize(10);
	$objPHPExcel->getActiveSheet()->getStyle('A8:A'.($month_days_number+7))->getFont()->setSize(12);
	
	$objPHPExcel->getActiveSheet()->setTitle('Trang 4');
	//chen du lieu vao sheet 2007
	for($day = 1; $day <= $month_days_number; $day++){
		$objPHPExcel->getActiveSheet()->setCellValue('A'.(7+$day),$day);
		$objPHPExcel->getActiveSheet()->setCellValue('B'.(7+$day),0);
		$objPHPExcel->getActiveSheet()->setCellValue('C'.(7+$day),0);
		$objPHPExcel->getActiveSheet()->setCellValue('D'.(7+$day),0);
		$objPHPExcel->getActiveSheet()->setCellValue('E'.(7+$day),0);
	}
	
	for($day = 1; $day <= $month_days_number; $day++){
		$objPHPExcel->getActiveSheet()->setCellValue('B'.($day+7), $day_of_month[$day]['max_rainfall_in_day']);
		$objPHPExcel->getActiveSheet()->setCellValue('C'.($day+7), 10);
		$objPHPExcel->getActiveSheet()->setCellValue('D'.($day+7), $day_of_month[$day]['max_total_rainfall_in_day']);
		$objPHPExcel->getActiveSheet()->setCellValue('E'.($day+7), $day_of_month[$day]['max_total_time_rainfall_in_day']);
	}

    //return 'aaaa';
	
	/** Include PHPExcel_IOFactory */  
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
  header('Content-type: application/vnd.ms-excel');
  header('Content-Disposition: attachment; filename="Báo cáo dữ liệu mưa - Trạm ' . $name_station->title . ' - ' . substr($month,-2,2) . '-' . $year . '.xls"');
  $objWriter->save('php://output');
  drupal_exit();
}
