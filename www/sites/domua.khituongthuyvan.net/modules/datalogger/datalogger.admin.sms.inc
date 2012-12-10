<?php

/*
 * Helper function to post sms to server.
 */
function _datalogger_sms_post_server(&$row) {
  $row_s = serialize ($row);
  $row_s = urlencode($row_s);
  
  module_load_include('php', 'datalogger', 'HttpClient.class');
  
  $client = new HttpClient('namtrungbo.domua.khituongthuyvan.net:8181');
  $client->setDebug(true);
  if (!$client->get('/gammu/inbox/remote/' . $row_s)) {
      die('An error occurred: '.$client->getError());
  }
  $pageContents = $client->getContent();
  
  echo 'Posted to server: ' . $pageContents . "\n";
}

/*
 * Menu callback when getting sms.
 */
function _datalogger_gammu_inbox_remote() {

  $sms = arg(3);
  
  module_load_include('inc', 'datalogger', 'datalogger.admin');
  
  //dpm($sms);
  
  echo $sms;
  drupal_exit();
}

