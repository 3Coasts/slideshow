<?php

function slideshow_edit_form($form, &$form_state, $slideshow) {
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
    '#default_value' => $slideshow->title,
  );

  $form['slideshow'] = array(
    '#type' => 'value',
    '#value' => $slideshow,
  );

  field_attach_form('slideshow', $slideshow, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );

  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#submit' => array('slideshow_edit_delete'),
    '#weight' => 200,
  );

  return $form;
}


/**
 * Validation handler for entity_example_basic_add_form form.
 * We pass things straight through to the Field API to handle validation
 * of the attached fields.
 */
function slideshow_edit_form_validate($form, &$form_state) {
  field_attach_form_validate('slideshow', $form_state['values']['slideshow'], $form, $form_state);
}


/**
 * Form submit handler: submits basic_add_form information
 */
function slideshow_edit_form_submit($form, &$form_state) {
  $slideshow = $form_state['values']['slideshow'];
  $slideshow->title = $form_state['values']['title'];
  field_attach_submit('slideshow', $slideshow, $form, $form_state);
  $slideshow = slideshow_save($slideshow);
  $form_state['redirect'] = 'admin/structure/slideshow/manage';
}


function slideshow_edit_delete($form , &$form_state) {
  $slideshow = $form_state['values']['slideshow'];
  slideshow_delete($slideshow);
  drupal_set_message(t('The slideshow %title (ID %id) has been deleted',
    array('%title' => $slideshow->title, '%id' => $slideshow->sid))
  );
  $form_state['redirect'] = 'admin/structure/slideshow/manage';
}
