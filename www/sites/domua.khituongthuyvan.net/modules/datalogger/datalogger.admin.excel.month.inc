<?php
error_reporting(E_ALL);
require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel.php';
function _datalogger_export_rainfall_month_excel($nid, $year, $year_month){
	module_load_include('inc', 'datalogger', 'datalogger.admin');
  $objPHPExcel = new PHPExcel();

  $objPHPExcel->getProperties()->setCreator("Datalogger")
                 ->setLastModifiedBy("Datalogger")
                 ->setTitle("Office 2007 XLSX Document")
                 ->setSubject("Office 2007 XLSX Document")
                 ->setDescription("Document for Office 2007 XLSX")
                 ->setKeywords("office 2007 openxml php")
                 ->setCategory("Test result file");
  
	$objPHPExcel->setActiveSheetIndex();
	$objPHPExcel->getActiveSheet()->setCellValue('C1', 'Trạm');
	$objPHPExcel->getActiveSheet()->setCellValue('F1', 'Tháng');
	$objPHPExcel->getActiveSheet()->setCellValue('H1', 'Năm');
	
	$objPHPExcel->getActiveSheet()->setCellValue('A2', 'Ngày \Giờ');
	
	$month_days_nuber = cal_days_in_month(CAL_GREGORIAN, substr($year_month, -2), $year);
	//thiet lap header
	for($i =0; $i < 24; $i++){
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'2', $i+1);
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'3', '|');
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'4', $i);
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$i).'5', $i+1);
	}
	$k = 1;
	//gan gia tri mac dinh cho cac o
	for($i =0; $i < $month_days_nuber*2; $i++){
		if($i%2 == 0){
			$objPHPExcel->getActiveSheet()->setCellValue(chr(65).($i+6), $k++);
			for($j =0; $j < 24; $j++){
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($i+6), 0);
			}
			$objPHPExcel->getActiveSheet()->mergeCells('A'.($i+6).':B'.($i+7));
		}
		else{
			for($j =0; $j < 24; $j++){
				$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($i+6), 60);
			}
		}
	}
	
	// /*
	//chen du lieu vao bao cao
	for($day = 1; $day < $month_days_nuber*2; $day++){
		if($day%2 == 0){
			if(($day/2) < 10){
				$day_time = '0'.($day/2);
			}
			$rainfalls = views_get_view_result('view_rainfall_hour_time','default', $nid, $year, $year_month, $year_month.$day_time);
			for($j =0; $j < 24; $j++){
				if(count($rainfalls) == 24){
					$rainfall_total = (int)substr($rainfalls_month[$i]->field_field_rainfall_total[0]['rendered']['#markup']);
					$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($day+6),$rainfall_total);
				}
				else{
					// $rainfall_total2 = (int)substr($rainfalls_month[$i]->field_field_rainfall_total[0]['rendered']['#markup']);
					for($k = 0; $k < count($rainfalls); $k++){
						$hour_time = (int)substr($rainfalls_month[$k]->field_field_rainfall_hour_time[0]['rendered']['#markup']);
						if($j == $hour_time){
							$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).($day+6),(int)substr($rainfalls_month[$k]->field_field_rainfall_total[0]['rendered']['#markup']));
						}
					}
				}
			}
		}
	}
	// */
	
	$objPHPExcel->getActiveSheet()->setCellValue('AA2', 'Tổng số');
	$objPHPExcel->getActiveSheet()->setCellValue('AA3', 'mm');
	$objPHPExcel->getActiveSheet()->setCellValue('AA3', 'mddddd');
	$objPHPExcel->getActiveSheet()->setCellValue('AA4', 'phút');
	$objPHPExcel->getActiveSheet()->setCellValue('AA5', '25');
	
	
	for($i =0; $i < $month_days_nuber*2; $i++){
		
		if($i%2 == 0){
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+6), '=SUM(C'.($i+6).':Z'.($i+6).')');
		}
		else{
			$objPHPExcel->getActiveSheet()->setCellValue('AA'.($i+6), '=SUM(C'.($i+6).':Z'.($i+6).')');
		}
	}
	
	$objPHPExcel->getActiveSheet()->setCellValue('A'.(($month_days_nuber+3)*2), 'Tổng số');
	$objPHPExcel->getActiveSheet()->setCellValue('B'.(($month_days_nuber+3)*2), 'mm');
	$objPHPExcel->getActiveSheet()->setCellValue('B'.(($month_days_nuber+3)*2+1), 'Phút');
	
	$mm =0;
	$minute = 0;
	for($j =0; $j < 24; $j++){
		for($i =0; $i < $month_days_nuber*2; $i++){
			if($i%2 == 0){
				$mm += (int)$objPHPExcel->getActiveSheet()->getCell(chr(67+$j).($i+6))->getFormattedValue();
			}
			else{
				$minute += (int)$objPHPExcel->getActiveSheet()->getCell(chr(67+$j).($i+6))->getFormattedValue();
			}
		}
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).(($month_days_nuber+3)*2), $mm);
		$objPHPExcel->getActiveSheet()->setCellValue(chr(67+$j).(($month_days_nuber+3)*2+1), $minute);
		$mm =0;
		$minute = 0;
	}
	
	$objPHPExcel->getActiveSheet()->mergeCells('A'.(($month_days_nuber+3)*2).':A'.(($month_days_nuber+3)*2+1));
	$objPHPExcel->getActiveSheet()->mergeCells('A2:B5');
	
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

	$objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle1, 'A2:AA'.(($month_days_nuber+3)*2+1));
	$objPHPExcel->getActiveSheet()->getStyle('A3:AA'.(($month_days_nuber+3)*2+1))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
	$styleAlignments = array(
					'alignment' => array(
					'horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER,
					)
	);
	$objPHPExcel->getActiveSheet()->getStyle('A2:AA'.(($month_days_nuber+3)*2+1))->applyFromArray($styleAlignments);
	$objPHPExcel->getActiveSheet()->getStyle((($month_days_nuber+3)*2+1))->applyFromArray(
			array(
					'alignment' => array(
					'horizontal' => PHPExcel_Style_Alignment::VERTICAL_CENTER,
					)
				)
	);
	$objPHPExcel->getActiveSheet()->getColumnDimension('A')->setWidth(10);
	$objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(5);
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
  /** Include PHPExcel_IOFactory */
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel/IOFactory.php';
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
	
  header('Content-type: application/vnd.ms-excel');
  header('Content-Disposition: attachment; filename="Báo cáo dữ liệu mưa - Trạm ' . $name_station->title . ' - ' . date('m',time()) . '-' . date('Y',time()) . '.xlsx"');
  $objWriter->save('php://output');
  drupal_exit();
}