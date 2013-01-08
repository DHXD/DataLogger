<?php
error_reporting(E_ALL);
require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel.php';

// function _datalogger_export_rainfall_month_excel($args){
function _datalogger_export_rainfall_month_excel(){
	/*
	//node id
	$nid = $args[0];
	//year month
	// $year_month = $args[1];
	 $rainfalls = $args[1];
  // $rainfalls = views_get_view_result('view_export_excel',NULL, $nid, $year_month,all);
	//ten nguoi quan trac vien
	$name_qtv = $args[2];
	//ten nguoi lap bao cao
	$name_nlb =$args[3];
	//ten nguoi kiem soat
	$name_ks = $args[4];
	//ten nguoi phuc tham
	$name_pt = $args[5];
	*/
  $objPHPExcel = new PHPExcel();

  $objPHPExcel->getProperties()->setCreator("Datalogger")
                 ->setLastModifiedBy("Datalogger")
                 ->setTitle("Office 2007 XLSX Document")
                 ->setSubject("Office 2007 XLSX Document")
                 ->setDescription("Document for Office 2007 XLSX")
                 ->setKeywords("office 2007 openxml php")
                 ->setCategory("Test result file");
  
  // $rainfalls = views_get_view_result('view_export_excel',NULL, $nid, $year_month,all);
  //tong so rows
	/*
  $rowcount = count($rainfalls);
	$limit_row = 152;
  //tong so sheet
  $total_page = (int)$rowcount/$limit_row + 1; //mot ngay co 152 rows
  $j = 0;
	$row = 0;
  for($page = 0; $page < $total_page; $page++)
  {
		if($page != 0)
    {
      $objPHPExcel->createSheet();
    }
		*/
    // for( ; $row < $page*$limit_row; $row++){
		// $objPHPExcel->createSheet();
		//sheet luôn bắt đầy từ 0
    // $objPHPExcel->setActiveSheetIndex($page);
    $objPHPExcel->setActiveSheetIndex();
    //$objPHPExcel->setActiveSheetIndex(0);
    $objPHPExcel->getActiveSheet()->setCellValue('C1', 'Trạm');
    $objPHPExcel->getActiveSheet()->setCellValue('F1', 'Tháng');
    $objPHPExcel->getActiveSheet()->setCellValue('H1', 'Năm');
		
		$objPHPExcel->getActiveSheet()->setCellValue('A2', 'Giờ');
    $objPHPExcel->getActiveSheet()->setCellValue('A4', 'Ngày');
		
    $objPHPExcel->getActiveSheet()->setCellValue('C2', '1');
    $objPHPExcel->getActiveSheet()->setCellValue('C3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('C4', '0');
    $objPHPExcel->getActiveSheet()->setCellValue('C5', '1');
		
		$objPHPExcel->getActiveSheet()->setCellValue('D2', '2');
    $objPHPExcel->getActiveSheet()->setCellValue('D3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('D4', '1');
    $objPHPExcel->getActiveSheet()->setCellValue('D5', '2');
		
		$objPHPExcel->getActiveSheet()->setCellValue('E2', '3');
    $objPHPExcel->getActiveSheet()->setCellValue('E3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('E4', '2');
    $objPHPExcel->getActiveSheet()->setCellValue('E5', '3');
		
		$objPHPExcel->getActiveSheet()->setCellValue('F2', '4');
    $objPHPExcel->getActiveSheet()->setCellValue('F3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('F4', '3');
    $objPHPExcel->getActiveSheet()->setCellValue('F5', '4');
		
		$objPHPExcel->getActiveSheet()->setCellValue('G2', '5');
    $objPHPExcel->getActiveSheet()->setCellValue('G3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('G4', '4');
    $objPHPExcel->getActiveSheet()->setCellValue('G5', '5');
		
		$objPHPExcel->getActiveSheet()->setCellValue('H2', '6');
    $objPHPExcel->getActiveSheet()->setCellValue('H3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('H4', '5');
    $objPHPExcel->getActiveSheet()->setCellValue('H5', '6');
		
		$objPHPExcel->getActiveSheet()->setCellValue('I2', '7');
    $objPHPExcel->getActiveSheet()->setCellValue('I3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('I4', '6');
    $objPHPExcel->getActiveSheet()->setCellValue('I5', '7');
		
		$objPHPExcel->getActiveSheet()->setCellValue('J2', '8');
    $objPHPExcel->getActiveSheet()->setCellValue('J3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('J4', '7');
    $objPHPExcel->getActiveSheet()->setCellValue('J5', '8');
		
		$objPHPExcel->getActiveSheet()->setCellValue('K2', '9');
    $objPHPExcel->getActiveSheet()->setCellValue('K3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('K4', '8');
    $objPHPExcel->getActiveSheet()->setCellValue('K5', '9');
		
		$objPHPExcel->getActiveSheet()->setCellValue('L2', '10');
    $objPHPExcel->getActiveSheet()->setCellValue('L3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('L4', '9');
    $objPHPExcel->getActiveSheet()->setCellValue('L5', '10');
		
		$objPHPExcel->getActiveSheet()->setCellValue('M2', '11');
    $objPHPExcel->getActiveSheet()->setCellValue('M3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('M4', '10');
    $objPHPExcel->getActiveSheet()->setCellValue('M5', '11');
		
		$objPHPExcel->getActiveSheet()->setCellValue('N2', '12');
    $objPHPExcel->getActiveSheet()->setCellValue('N3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('N4', '11');
    $objPHPExcel->getActiveSheet()->setCellValue('N5', '12');
		
		$objPHPExcel->getActiveSheet()->setCellValue('O2', '13');
    $objPHPExcel->getActiveSheet()->setCellValue('O3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('O4', '12');
    $objPHPExcel->getActiveSheet()->setCellValue('O5', '13');
		
		$objPHPExcel->getActiveSheet()->setCellValue('P2', '14');
    $objPHPExcel->getActiveSheet()->setCellValue('P3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('P4', '13');
    $objPHPExcel->getActiveSheet()->setCellValue('P5', '14');
		
		$objPHPExcel->getActiveSheet()->setCellValue('Q2', '15');
    $objPHPExcel->getActiveSheet()->setCellValue('Q3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('Q4', '14');
    $objPHPExcel->getActiveSheet()->setCellValue('Q5', '14');
		
		$objPHPExcel->getActiveSheet()->setCellValue('R2', '16');
    $objPHPExcel->getActiveSheet()->setCellValue('R3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('R4', '15');
    $objPHPExcel->getActiveSheet()->setCellValue('R5', '16');
		
		$objPHPExcel->getActiveSheet()->setCellValue('S2', '17');
    $objPHPExcel->getActiveSheet()->setCellValue('S3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('S4', '16');
    $objPHPExcel->getActiveSheet()->setCellValue('S5', '17');
		
		$objPHPExcel->getActiveSheet()->setCellValue('T2', '18');
    $objPHPExcel->getActiveSheet()->setCellValue('T3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('T4', '17');
    $objPHPExcel->getActiveSheet()->setCellValue('T5', '18');
		
		$objPHPExcel->getActiveSheet()->setCellValue('U2', '19');
    $objPHPExcel->getActiveSheet()->setCellValue('U3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('U4', '18');
    $objPHPExcel->getActiveSheet()->setCellValue('U5', '19');
		
		$objPHPExcel->getActiveSheet()->setCellValue('V2', '20');
    $objPHPExcel->getActiveSheet()->setCellValue('V3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('V4', '19');
    $objPHPExcel->getActiveSheet()->setCellValue('V5', '20');
		
		$objPHPExcel->getActiveSheet()->setCellValue('W2', '21');
    $objPHPExcel->getActiveSheet()->setCellValue('W3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('W4', '20');
    $objPHPExcel->getActiveSheet()->setCellValue('W5', '21');
		
		$objPHPExcel->getActiveSheet()->setCellValue('X2', '22');
    $objPHPExcel->getActiveSheet()->setCellValue('X3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('X4', '21');
    $objPHPExcel->getActiveSheet()->setCellValue('X5', '22');
		
		$objPHPExcel->getActiveSheet()->setCellValue('Y2', '23');
    $objPHPExcel->getActiveSheet()->setCellValue('Y3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('Y4', '22');
    $objPHPExcel->getActiveSheet()->setCellValue('Y5', '23');
		
		$objPHPExcel->getActiveSheet()->setCellValue('Z2', '24');
    $objPHPExcel->getActiveSheet()->setCellValue('Z3', '|');
    $objPHPExcel->getActiveSheet()->setCellValue('Z4', '23');
    $objPHPExcel->getActiveSheet()->setCellValue('Z5', '24');
		
		$objPHPExcel->getActiveSheet()->setCellValue('AA2', 'Tổng số');
    $objPHPExcel->getActiveSheet()->setCellValue('AA3', 'mm');
    $objPHPExcel->getActiveSheet()->setCellValue('AA4', 'phút');
    $objPHPExcel->getActiveSheet()->setCellValue('AA5', '25');
		
    $objPHPExcel->getActiveSheet()->setCellValue('A6', '1');
    $objPHPExcel->getActiveSheet()->setCellValue('A8', '2');
    $objPHPExcel->getActiveSheet()->setCellValue('A10', '3');
    $objPHPExcel->getActiveSheet()->setCellValue('A12', '4');
    $objPHPExcel->getActiveSheet()->setCellValue('A14', '5');
    $objPHPExcel->getActiveSheet()->setCellValue('A16', '6');
    $objPHPExcel->getActiveSheet()->setCellValue('A18', '7');
    $objPHPExcel->getActiveSheet()->setCellValue('A20', '8');
    $objPHPExcel->getActiveSheet()->setCellValue('A22', '9');
    $objPHPExcel->getActiveSheet()->setCellValue('A24', '10');
    $objPHPExcel->getActiveSheet()->setCellValue('A26', '11');
    $objPHPExcel->getActiveSheet()->setCellValue('A28', '12');
    $objPHPExcel->getActiveSheet()->setCellValue('A30', '13');
    $objPHPExcel->getActiveSheet()->setCellValue('A32', '14');
    $objPHPExcel->getActiveSheet()->setCellValue('A34', '15');
    $objPHPExcel->getActiveSheet()->setCellValue('A36', '16');
    $objPHPExcel->getActiveSheet()->setCellValue('A38', '17');
    $objPHPExcel->getActiveSheet()->setCellValue('A40', '18');
    $objPHPExcel->getActiveSheet()->setCellValue('A42', '19');
    $objPHPExcel->getActiveSheet()->setCellValue('A44', '20');
    $objPHPExcel->getActiveSheet()->setCellValue('A46', '21');
    $objPHPExcel->getActiveSheet()->setCellValue('A48', '22');
    $objPHPExcel->getActiveSheet()->setCellValue('A50', '23');
    $objPHPExcel->getActiveSheet()->setCellValue('A52', '24');
    $objPHPExcel->getActiveSheet()->setCellValue('A54', '25');
    $objPHPExcel->getActiveSheet()->setCellValue('A56', '26');
    $objPHPExcel->getActiveSheet()->setCellValue('A58', '27');
    $objPHPExcel->getActiveSheet()->setCellValue('A60', '28');
    $objPHPExcel->getActiveSheet()->setCellValue('A62', '29');
    $objPHPExcel->getActiveSheet()->setCellValue('A64', '30');
    $objPHPExcel->getActiveSheet()->setCellValue('A66', '31');
    $objPHPExcel->getActiveSheet()->setCellValue('A68', 'Tổng số');
    $objPHPExcel->getActiveSheet()->setCellValue('B68', 'mm');
    $objPHPExcel->getActiveSheet()->setCellValue('B69', 'Phút');
		
		//merge cell
    $objPHPExcel->getActiveSheet()->mergeCells('A2:B3');
    $objPHPExcel->getActiveSheet()->mergeCells('A4:B5');
		$objPHPExcel->getActiveSheet()->mergeCells('A6:B7');
    $objPHPExcel->getActiveSheet()->mergeCells('A8:B9');
		$objPHPExcel->getActiveSheet()->mergeCells('A10:B11');
    $objPHPExcel->getActiveSheet()->mergeCells('A12:B13');
		$objPHPExcel->getActiveSheet()->mergeCells('A14:B15');
    $objPHPExcel->getActiveSheet()->mergeCells('A16:B17');
		$objPHPExcel->getActiveSheet()->mergeCells('A18:B19');
    $objPHPExcel->getActiveSheet()->mergeCells('A20:B21');
		$objPHPExcel->getActiveSheet()->mergeCells('A22:B23');
    $objPHPExcel->getActiveSheet()->mergeCells('A24:B25');
		$objPHPExcel->getActiveSheet()->mergeCells('A26:B27');
    $objPHPExcel->getActiveSheet()->mergeCells('A28:B29');
		$objPHPExcel->getActiveSheet()->mergeCells('A30:B31');
    $objPHPExcel->getActiveSheet()->mergeCells('A32:B33');
		$objPHPExcel->getActiveSheet()->mergeCells('A34:B35');
    $objPHPExcel->getActiveSheet()->mergeCells('A36:B37');
		$objPHPExcel->getActiveSheet()->mergeCells('A38:B39');
    $objPHPExcel->getActiveSheet()->mergeCells('A40:B41');
		$objPHPExcel->getActiveSheet()->mergeCells('A42:B43');
		$objPHPExcel->getActiveSheet()->mergeCells('A44:B45');
    $objPHPExcel->getActiveSheet()->mergeCells('A46:B47');
		$objPHPExcel->getActiveSheet()->mergeCells('A48:B49');
    $objPHPExcel->getActiveSheet()->mergeCells('A50:B51');
		$objPHPExcel->getActiveSheet()->mergeCells('A52:B53');
    $objPHPExcel->getActiveSheet()->mergeCells('A54:B55');
		$objPHPExcel->getActiveSheet()->mergeCells('A56:B57');
    $objPHPExcel->getActiveSheet()->mergeCells('A58:B59');
		$objPHPExcel->getActiveSheet()->mergeCells('A60:B61');
    $objPHPExcel->getActiveSheet()->mergeCells('A62:B63');
		$objPHPExcel->getActiveSheet()->mergeCells('A64:B65');
    $objPHPExcel->getActiveSheet()->mergeCells('A66:B67');
    $objPHPExcel->getActiveSheet()->mergeCells('A68:A69');

    $styleThinBlackBorderOutline = array(
      'borders' => array(
        'outline' => array(
          'style' => PHPExcel_Style_Border::BORDER_THIN,
          'color' => array('argb' => 'FF000000'),
        ),
      ),
    );
		
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA4')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA5')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA7')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA9')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA11')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA13')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA15')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA17')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA19')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA21')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA23')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA25')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA27')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA29')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA31')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA33')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA35')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA37')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA39')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA41')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA43')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA45')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA47')->applyFromArray($styleThinBlackBorderOutline);
		$objPHPExcel->getActiveSheet()->getStyle('A2:AA49')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA51')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA53')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA55')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA57')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA59')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA61')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA63')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA65')->applyFromArray($styleThinBlackBorderOutline);
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA67')->applyFromArray($styleThinBlackBorderOutline);

    $sharedStyle1 = new PHPExcel_Style();
    $sharedStyle1->applyFromArray(
      array(//'fill' 	=> array(
          'borders' => array(
                    'bottom'	=> array('style' => PHPExcel_Style_Border::BORDER_THIN),
                    'right'		=> array('style' => PHPExcel_Style_Border::BORDER_THIN)
                  )
         ));

    $objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle1, "A7:AA69");


    $objPHPExcel->getActiveSheet()->getStyle('A3:AA69')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('A68')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F2')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F2')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F4')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F4')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('H4')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('H4')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('I4')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('I4')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('H8')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('H8')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('I8')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('I8')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('H10')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('H10')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('I10')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('I10')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F8')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F8')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F10')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);
    // $objPHPExcel->getActiveSheet()->getStyle('F10')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);

    $styleAlignments = array(
            'alignment' => array(
            'horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER,
            )
    );
    $objPHPExcel->getActiveSheet()->getStyle('A2:AA69')->applyFromArray($styleAlignments);
    $objPHPExcel->getActiveSheet()->getStyle('A68')->applyFromArray(
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
    
    
		/*
    $cell = $objPHPExcel->getActiveSheet();
    $i = 8;
    for(; $row < $limit_row * ($page + 1); $row++)
    {
			if($row > $rowcount){
				break;
			}
      $date = $rainfalls[$row]->node_title;
      $interval = $rainfalls[$row]->field_field_rainfall_measuring[0]['raw']['value'];
      $total = $rainfalls[$row]->field_field_rainfall_total[0]['raw']['value'];
      $cell->setCellValue('A' . $i, $date);
      $cell->setCellValue('B'.$i,$interval);//luong mưa 10'
      $cell->setCellValue('C'.$i,"10");//thoi gian keo dai 10'
      $cell->setCellValue('D'.$i,$total);//luong mua mot dot quan trac
      $cell->setCellValue('E'.$i,"60");//thoi gian keo dai mot dot quan trac
      $i++;  
    }
    $name_station = node_load($nid);
    //trạm đo mưa
    $objPHPExcel->getActiveSheet()->setCellValue('C1', $name_station->title);
    */
    // //tháng
    // $objPHPExcel->getActiveSheet()->setCellValue('G1', substr($year_month,4,2));
    // //năm
    // $objPHPExcel->getActiveSheet()->setCellValue('I1', substr($year_month,0,4));//tháng
    $objPHPExcel->getActiveSheet()->setCellValue('G1',date('m',time()));
    //năm
     
    //set font
    $objPHPExcel->getActiveSheet()->getStyle('A1:Z90')->getFont()->setName('Times New Roman');
    $objPHPExcel->getActiveSheet()->getStyle('A1:Z90')->getFont()->setSize(12);

    $objPHPExcel->getActiveSheet()->setTitle('Trang '.($page+1));
    
  // }
  
  $objPHPExcel->setActiveSheetIndex(0);
  
  /** Include PHPExcel_IOFactory */
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel/IOFactory.php';
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
  //$objWriter->save(str_replace('.php', '.xlsx', __FILE__));
  
  
  header('Content-type: application/vnd.ms-excel');
  header('Content-Disposition: attachment; filename="Báo cáo dữ liệu mưa - Trạm ' . $name_station->title . ' - ' . date('m',time()) . '-' . date('Y',time()) . '.xlsx"');
  $objWriter->save('php://output');
  drupal_exit();
}