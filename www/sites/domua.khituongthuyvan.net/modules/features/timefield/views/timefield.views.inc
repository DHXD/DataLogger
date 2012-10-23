<?php


/**
 * @file
 *   Default views hooks.
 */

/**
 * Implements hook_views_plugins().
 */
function timefield_views_plugins() {
  $plugins = array(
    'module' => 'timefield',
    'style' => array(
      'timefield_minical' => array(
        'title' => t('Timefield MiniCal'),
        'help' => t('Displays a Mini Summary of Timefield.'),
        'handler' => 'TimefieldPluginStyleMinical',
        'theme' => 'timefield_minical',
        'theme path' => drupal_get_path('module', 'timefield') . '/views',
        'path' => drupal_get_path('module', 'timefield') . '/views',
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
  );

  return $plugins;
}
