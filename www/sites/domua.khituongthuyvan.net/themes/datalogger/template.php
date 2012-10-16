<?php
  
global $user;
global $site_name;

if (in_array('administrator', array_values($user->roles)) || in_array('control datalogger', array_values($user->roles))) {
  // variable_set('site_name', t('Phần mềm điều khiển trạm đo mưa tự động'));
  variable_set('site_name', t('Software control automatic rain gauge stations'));
}
else{
  // variable_set('site_name', t('Hệ thống khai thác dữ liệu đo mưa tự động 2012'));
  variable_set('site_name', t('Data mining system automatic rain gauge 2012'));
}




function datalogger_preprocess_html(&$variables) {

  // switch ($_REQUEST['q']) {
  // case '/stations':
    // drupal_set_title(t('List All Datalogger'));
    // break;
  // }

  if (!empty($variables['page']['featured'])) {
    $variables['classes_array'][] = 'featured';
  }

  if (!empty($variables['page']['triptych_first'])
    || !empty($variables['page']['triptych_middle'])
    || !empty($variables['page']['triptych_last'])) {
    $variables['classes_array'][] = 'triptych';
  }

  if (!empty($variables['page']['footer_firstcolumn'])
    || !empty($variables['page']['footer_secondcolumn'])
    || !empty($variables['page']['footer_thirdcolumn'])
    || !empty($variables['page']['footer_fourthcolumn'])) {
    $variables['classes_array'][] = 'footer-columns';
  }

  // Add conditional stylesheets for IE
  drupal_add_css(path_to_theme() . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 6', '!IE' => FALSE), 'preprocess' => FALSE));
}

/**
 * Override or insert variables into the page template for HTML output.
 */
function datalogger_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/**
 * Override or insert variables into the page template.
 */
function datalogger_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
  // Since the title and the shortcut link are both block level elements,
  // positioning them next to each other is much simpler with a wrapper div.
  if (!empty($variables['title_suffix']['add_or_remove_shortcut']) && $variables['title']) {
    // Add a wrapper div using the title_prefix and title_suffix render elements.
    $variables['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $variables['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
      );
    // Make sure the shortcut link is the first item in title_suffix.
    $variables['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }
}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function datalogger_preprocess_maintenance_page(&$variables) {
  // By default, site_name is set to Drupal if no db connection is available
  // or during site installation. Setting site_name to an empty string makes
  // the site and update pages look cleaner.
  // @see template_preprocess_maintenance_page
  if (!$variables['db_is_active']) {
    $variables['site_name'] = '';
  }
  drupal_add_css(drupal_get_path('theme', 'datalogger') . '/css/maintenance-page.css');
}

/**
 * Override or insert variables into the maintenance page template.
 */
function datalogger_process_maintenance_page(&$variables) {
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
	
	//Thiết lập title cho các view với các tham số khách nhau
	// if($variables['nghe_an'])
	
	
}

/**
 * Override or insert variables into the node template.
 */
function datalogger_preprocess_node(&$variables) {
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
    
  }
	
	$node = $variables['node'];
	
	if ($node->type == 'command') {
		$module_path = drupal_get_path('module', 'datalogger');
		drupal_add_js($module_path . '/node_refresh.js');
		drupal_set_message(t('Trang web sẽ tự động nạp lại sau 5 giây.'));
	}
}

/**
 * Override or insert variables into the block template.
 */
function datalogger_preprocess_block(&$variables) {
  // In the header region visually hide block titles.
  if ($variables['block']->region == 'header') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }
}

/**
 * Implements theme_menu_tree().
 */
function datalogger_menu_tree($variables) {
  return '<ul class="menu clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_field__field_type().
 */
function datalogger_field__taxonomy_term_reference($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h3 class="field-label">' . $variables['label'] . ': </h3>';
  }

  // Render the items.
  $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }
  $output .= '</ul>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '">' . $output . '</div>';

  return $output;
}

function datalogger_preprocess_page(&$variables) {
	$str = arg(3);
	$provinces = _datalogger_provinces();
	$areas = _datalogger_areas();
	if($provinces[$str] != '' || $provinces[$str] != null )
		// drupal_set_title(t('Danh sách trạm đo mưa tự động  ').t($provinces[$str]));
		$province = t("Danh sách trạm đo mưa tự động $provinces[$str]");
		drupal_set_title($province);
	if($areas[$str] != '' || $areas[$str] != null )
		// drupal_set_title(t('Danh sách trạm KTTV ').t($areas[$str]));
		$area = t("Danh sách trạm KTTV $areas[$str]");
		drupal_set_title($area);
}

function _datalogger_provinces(){
	$list = array('ho_chi_minh' => 'TP. Hồ Chí Minh',
	'hai_phong' => 'TP. Hải Phòng',
	'da_nang' => 'TP. Đà Nẵng',
	'ha_giang' => 'Tỉnh Hà Giang',
	'cao_bang' => 'Tỉnh Cao Bằng',
	'lai_chau' => 'Tỉnh Lai Châu',
	'lao_cai' => 'Tỉnh Lào Cai',
	'tuyen_quang' => 'Tỉnh Tuyên Quang',
	'lang_son' => 'Tỉnh Lạng Sơn',
	'bac_kan' => 'Tỉnh Bắc Kạn',
	'thai_nguyen' => 'Tỉnh Thái Nguyên',
	'yen_bai' => 'Tỉnh Yên Bái',
	'son_la' => 'Tỉnh Sơn La',
	'phu_tho' => 'Tỉnh Phú Thọ',
	'vinh_phuc' => 'Tỉnh Vĩnh Phúc',
	'quang_ninh' => 'Tỉnh Quảng Ninh',
	'bac_giang' => 'Tỉnh Bắc Giang',
	'bac_ninh' => 'Tỉnh Bắc Ninh',
	'ha_noi' => 'TP. Hà Nội',
	'hai_duong' => 'Tỉnh Hải Dương',
	'hung_yen' => 'Tỉnh Hưng Yên',
	'hoa_binh' => 'Tỉnh Hòa Bình',
	'ha_nam' => 'Tỉnh Hà Nam',
	'nam_dinh' => 'Tỉnh Nam Định',
	'thai_binh' => 'Tỉnh Thái Bình',
	'ninh_binh' => 'Tỉnh Ninh Bình',
	'thanh_hoa' => 'Tỉnh Thanh Hóa',
	'nghe_an' => 'Tỉnh Nghệ An',
	'ha_tinh' => 'Tỉnh Hà Tĩnh',
	'quang_binh' => 'Tỉnh Quảng Bình',
	'quang_tri' => 'Tỉnh Quảng Trị',
	'thua_thien_hue' => 'Tỉnh Thừa Thiên - Huế',
	'quang_nam' => 'Tỉnh Quảng Nam',
	'quang_ngai' => 'Tỉnh Quảng Ngãi',
	'kom_tum' => 'Tỉnh Kon Tum',
	'binh_dinh' => 'Tỉnh Bình Định',
	'giai_lai' => 'Tỉnh Gia Lai',
	'phu_yen' => 'Tỉnh Phú Yên',
	'dak_lak' => 'Tỉnh Đăk Lăk',
	'khanh_hoa' => 'Tỉnh Khánh Hòa',
	'lam_dong' => 'Tỉnh Lâm Đồng',
	'binh_phuoc' => 'Tỉnh Bình Phước',
	'binh_duong' => 'Tỉnh Bình Dương',
	'ninh_thuan' => 'Tỉnh Ninh Thuận',
	'tay_ninh' => 'Tỉnh Tây Ninh',
	'binh_thuan' => 'Tỉnh Bình Thuận',
	'dong_nai' => 'Tỉnh Đồng Nai',
	'long_an' => 'Tỉnh Long An',
	'dong_thap' => 'Tỉnh Đồng Tháp',
	'an_giang' => 'Tỉnh An Giang',
	'ba_ria_vung_tau' => 'Tỉnh Bà Rịa - Vũng Tàu',
	'tien_gian' => 'Tỉnh Tiền Giang',
	'kien_giang' => 'Tỉnh Kiên Giang',
	'can_tho' => 'TP. Cần Thơ',
	'ben_tre' => 'Tỉnh Bến Tre',
	'vinh_long' => 'Tỉnh Vĩnh Long',
	'tra_vinh' => 'Tỉnh Trà Vinh',
	'soc_trang' => 'Tỉnh Sóc Trăng',
	'bac_lieu' => 'Tỉnh Bạc Liêu',
	'ca_mau' => 'Tỉnh Cà Mau',
	'dien_bien' => 'Tỉnh Điện Biên',
	'dak_nong' => 'Tỉnh Đăk Nông',
	'hau_giang' => 'Tỉnh Hậu Giang',);
	return $list;
}

function _datalogger_areas(){
	$list = array('north_central_region' => 'Khu Vực Bắc Trung Bộ',
		'mid_central_region ' => 'Khu Vực Trung Trung Bộ',
		'central_highlands' => 'Khu Vực Tây Nguyên',
		'south_central_region ' => 'Khu Vực Nam Trung Bộ',
		'south_region' => 'Khu Vực Nam Bộ',);
	return $list;
}
