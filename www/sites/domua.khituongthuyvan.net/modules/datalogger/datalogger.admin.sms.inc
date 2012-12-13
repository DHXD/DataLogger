<?php

/*
 * Helper function to post sms to server.
 */
function _datalogger_sms_post_server(&$row) {
  $row-> RecipientID = '(modem13)';
  $row_s = serialize ($row);
  $row_s = urlencode($row_s);
  
  module_load_include('php', 'datalogger', 'HttpClient.class');
  
  echo 'Sending to remote server...\n';
  flush();
  
  $client = new HttpClient('namtrungbo.domua.khituongthuyvan.net:8181');
  //$client->setDebug(true);
  if (!$client->get('/gammu/inbox/remote/' . $row_s)) {
      echo 'Cross server posting error: '.$client->getError() . '\n';
      return false;
  }
  $pageContents = $client->getContent();
  
  echo 'Posted to server: ' . $pageContents . "\n";
  return true;
}

/*
 * Menu callback when getting sms.
 */
function _datalogger_gammu_inbox_remote() {

  $sms = arg(3);
  
  module_load_include('inc', 'datalogger', 'datalogger.admin');
  
  //dpm($sms);
  
  $row = unserialize ($sms);
  
  if (isset($row->UpdatedInDB )) {
    $row = (array) $row;
    
    unset($row['ID']);
    
    $keys = array_keys($row);
    $fields = array(); $vals = array();
    
    foreach ($keys as $key) {
      $fields[] = '`' . $key . '`';
      $vals[] = "'" . str_replace("'", "''", $row[$key]) . "'";
    }
    
    $sql = "INSERT INTO `inbox` (" . implode(', ', $fields) .  ") VALUES (" . implode(', ', $vals) . ")";
    $nid = db_query($sql);
    
    _datalogger_check_inbox();    // check newly added inbox record
  }
  
  echo $sms;
  echo $sql;
  drupal_exit();
}

