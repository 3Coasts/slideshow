<?php

function slideshow_admin_page() {

  $output = 'Welcome to the administration page for your Basic Entities.<br/>';
  $output .= '<a href="/slideshow/add">Add entity</a>';
  $output .= theme('table',slideshow_load_admin_table());
  return $output;

}

function slideshow_load_admin_table(){
	$result = db_select('slideshow','s')
			->fields('s')
			->execute();
	$rows = array();
	while($row = $result->fetchAssoc()) {
		$rows[] = array($row['sid'], $row['title'], l('edit','slideshow/' . $row['sid'] . '/edit'));
	}

	$variables = array(
		'header' => array('ID','Title','Edit'),
		'rows' => $rows,
	);
	return $variables;

}