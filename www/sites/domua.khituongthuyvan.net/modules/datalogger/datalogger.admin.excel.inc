<?php

function _export_excel()
{
  /**
   * PHPExcel
   *
   * Copyright (C) 2006 - 2012 PHPExcel
   *
   * This library is free software; you can redistribute it and/or
   * modify it under the terms of the GNU Lesser General Public
   * License as published by the Free Software Foundation; either
   * version 2.1 of the License, or (at your option) any later version.
   *
   * This library is distributed in the hope that it will be useful,
   * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   * Lesser General Public License for more details.
   *
   * You should have received a copy of the GNU Lesser General Public
   * License along with this library; if not, write to the Free Software
   * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
   *
   * @category   PHPExcel
   * @package    PHPExcel
   * @copyright  Copyright (c) 2006 - 2012 PHPExcel (http://www.codeplex.com/PHPExcel)
   * @license    http://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt	LGPL
   * @version    1.7.8, 2012-10-12
   */

  /** Error reporting */
  error_reporting(E_ALL);

  /** Include PHPExcel */
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel.php';


  // Create new PHPExcel object
  //echo date('H:i:s') , " Create new PHPExcel object" , PHP_EOL;
  $objPHPExcel = new PHPExcel();

  // Set document properties
  //echo date('H:i:s') , " Set document properties" , PHP_EOL;
  $objPHPExcel->getProperties()->setCreator("Maarten Balliauw")
                 ->setLastModifiedBy("Maarten Balliauw")
                 ->setTitle("Office 2007 XLSX Test Document")
                 ->setSubject("Office 2007 XLSX Test Document")
                 ->setDescription("Test document for Office 2007 XLSX, generated using PHP classes.")
                 ->setKeywords("office 2007 openxml php")
                 ->setCategory("Test result file");
  // Create a first sheet, representing sales data
  //echo date('H:i:s') , " Add some data" , PHP_EOL;
  $objPHPExcel->setActiveSheetIndex(0);
  $objPHPExcel->getActiveSheet()->setCellValue('B1', 'Tr?m');
  $objPHPExcel->getActiveSheet()->setCellValue('F1', 'Tháng...... Nam.....');
  $objPHPExcel->getActiveSheet()->setCellValue('J1', 'Trang 4');
  $objPHPExcel->getActiveSheet()->setCellValue('A2', 'LU?NG GIÁNG TH?Y L?N NH?T');
  $objPHPExcel->getActiveSheet()->setCellValue('B3', 'Trong 60 phút');
  $objPHPExcel->getActiveSheet()->setCellValue('D3', 'Trong m?t d?t liên t?c');
  $objPHPExcel->getActiveSheet()->setCellValue('F2', 'C?C TR? TRONG THÁNG');
  $objPHPExcel->getActiveSheet()->setCellValue('A3', 'Ngày');
  $objPHPExcel->getActiveSheet()->setCellValue('B4', 'Lu?ng');
  $objPHPExcel->getActiveSheet()->setCellValue('C4', 'Th?i gian');
  $objPHPExcel->getActiveSheet()->setCellValue('D4', 'Lu?ng');
  $objPHPExcel->getActiveSheet()->setCellValue('E4', 'Th?i gian');
  $objPHPExcel->getActiveSheet()->setCellValue('B5', '(mm)');
  $objPHPExcel->getActiveSheet()->setCellValue('C5', 'kéo dài');
  $objPHPExcel->getActiveSheet()->setCellValue('D5', '(mm)');
  $objPHPExcel->getActiveSheet()->setCellValue('E5', 'kéo dài');
  $objPHPExcel->getActiveSheet()->setCellValue('C6', '(phút)');
  $objPHPExcel->getActiveSheet()->setCellValue('E6', '(gi?, phút)');
  $objPHPExcel->getActiveSheet()->setCellValue('H4', 'Lu?ng');
  $objPHPExcel->getActiveSheet()->setCellValue('I4', 'Th?i gian kéo dài');
  $objPHPExcel->getActiveSheet()->setCellValue('H6', '(mm)');
  $objPHPExcel->getActiveSheet()->setCellValue('I6', '(gi?, phút)');
  $objPHPExcel->getActiveSheet()->setCellValue('F8', 'Trong m?t gi?');
  $objPHPExcel->getActiveSheet()->setCellValue('F10', 'Trong m?t d?t liên t?c');
  $objPHPExcel->getActiveSheet()->setCellValue('G13', 'GHI CHÚ');

  $objPHPExcel->getActiveSheet()->setCellValue('B7', '1');
  $objPHPExcel->getActiveSheet()->setCellValue('C7', '2');
  $objPHPExcel->getActiveSheet()->setCellValue('D7', '3');
  $objPHPExcel->getActiveSheet()->setCellValue('E7', '4');


  // Merge cells
  //echo date('H:i:s') , " Merge cells" , PHP_EOL;
  $objPHPExcel->getActiveSheet()->mergeCells('F1:H1');
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

  //$objPHPExcel->getActiveSheet()->unmergeCells('A28:B28');

  // Set thin black border outline around column
  //echo date('H:i:s') , " Set thin black border outline around column" , PHP_EOL;

  $styleThinBlackBorderOutline = array(
    'borders' => array(
      'outline' => array(
        'style' => PHPExcel_Style_Border::BORDER_THIN,
        'color' => array('argb' => 'FF000000'),
      ),
    ),
  );
  $objPHPExcel->getActiveSheet()->getStyle('A2:J38')->applyFromArray($styleThinBlackBorderOutline);

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
    //							'type'		=> PHPExcel_Style_Fill::FILL_SOLID,
      //						'color'		=> array('argb' => 'FFCCFFCC')
        //				),
        'borders' => array(
                  'bottom'	=> array('style' => PHPExcel_Style_Border::BORDER_THIN),
                  'right'		=> array('style' => PHPExcel_Style_Border::BORDER_THIN)
                )
       ));

  $objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle1, "A7:E38");
  //$objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle1, "F2:J11");
  //$objPHPExcel->getActiveSheet()->setSharedStyle($sharedStyle2, "C5:R95");

  // Set alignments
  //echo date('H:i:s') , " Set alignments" , PHP_EOL;
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

  /*
  $objPHPExcel->getActiveSheet()->getStyle('A3')->applyFromArray(
      array(
        'alignment' => array(
          'horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT,
        ),
        'borders' => array(
          'left'     => array(
            'style' => PHPExcel_Style_Border::BORDER_THIN
          )
        )
      )
  );
  */

  $styleAlignments = array(
          'alignment' => array(
          'horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER,
          )
  );
  $objPHPExcel->getActiveSheet()->getStyle('A2:E38')->applyFromArray($styleAlignments);
  $objPHPExcel->getActiveSheet()->getStyle('F2:I10')->applyFromArray($styleAlignments);
  $objPHPExcel->getActiveSheet()->getStyle('F2:I10')->applyFromArray(
      array(
          'alignment' => array(
          'horizontal' => PHPExcel_Style_Alignment::VERTICAL_CENTER,
          )
        )
  );

  // Set column widths
  //echo date('H:i:s') , " Set column widths" , PHP_EOL;
  $objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(50);

  //Ðánh s? th? t?
  for ($i = 8; $i <= 38; $i++) {
    $j = $i - 7;
    $objPHPExcel->getActiveSheet()->setCellValue('A' . $i, "$j");
    }
   
  //set font
  //$objPHPExcel->getActiveSheet()->getStyle('A1:J38')->getFont()->setName('.VnTime');
  $objPHPExcel->getActiveSheet()->getStyle('A1:J38')->getFont()->setName('Times New Roman');
  $objPHPExcel->getActiveSheet()->getStyle('A2:J7')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('B8:E38')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('B1')->getFont()->setSize(14);
  $objPHPExcel->getActiveSheet()->getStyle('F1:H1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('J1')->getFont()->setSize(10);
  $objPHPExcel->getActiveSheet()->getStyle('F4:G7')->getFont()->setSize(10);
  $objPHPExcel->getActiveSheet()->getStyle('H8:J11')->getFont()->setSize(10);
  $objPHPExcel->getActiveSheet()->getStyle('A8:A38')->getFont()->setSize(12);

  /** Include PHPExcel_IOFactory */
  require_once 'sites/all/libraries/PHPExcel/Classes/PHPExcel/IOFactory.php';


  // Save Excel 2007 file
  //echo date('H:i:s') , " Write to Excel2007 format";
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
  
  // We'll be outputting an excel file
  header('Content-type: application/vnd.ms-excel');
  // It will be called file.xls
  header('Content-Disposition: attachment; filename="file1.xlsx"');
  // Write file to the browser
  $objWriter->save('php://output');
  drupal_exit();
  
  /*
  $objWriter->save(str_replace('.php', '.xlsx', __FILE__));
  //echo date('H:i:s') , " File written to " , str_replace('.php', '.xlsx', pathinfo(__FILE__, PATHINFO_BASENAME));
  // Save Excel5 file
  //echo date('H:i:s') , " Write to Excel5 format";
  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
  $objWriter->save(str_replace('.php', '.xls', __FILE__));
  //echo date('H:i:s') , " File written to " , str_replace('.php', '.xls', pathinfo(__FILE__, PATHINFO_BASENAME));

  // //echo memory peak usage
  //echo date('H:i:s') , " Peak memory usage: " , (memory_get_peak_usage(true) / 1024 / 1024) , " MB";

  // //echo done
  //echo date('H:i:s') , " Done writing files";
  //echo 'Files have been created in ' , getcwd();

  */
}