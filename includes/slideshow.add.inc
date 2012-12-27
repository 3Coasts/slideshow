<?php

/**
 * Creates a basic entity for us - simply intializing the main variables and
 * sending us to a form to add in the rest.
 */
function slideshow_add() {
  $slideshow = (object) array(
    'sid' => '',
    'title' => '',
  );

  return drupal_get_form('slideshow_add_form', $slideshow);
}



/**
 * Form callback: allows us to create a basic entity.
 *
 * As you can see below the pattern followed is:
 * 1. Set up the form for the data that is specific to your
 * entity - typically the columns of your bas table.
 * 2. Call on the Field API to pull in the form elements
 * for fields attached to the entity.
 */
function slideshow_add_form($form, &$form_state, $slideshow) {

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
  );

  field_attach_form('slideshow', $slideshow, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );

  return $form;
}


/**
 * Form callback: Validates basic_add_form form.
 * We pass things straight through to the Field API to handle validation
 * of the attached fields.
 */
function slideshow_add_form_validate($form, &$form_state) {
  $slideshow_submission = (object) $form_state['values'];
  field_attach_form_validate('slideshow', $slideshow_submission, $form, $form_state);
}


/**
 * Form callback: submits basic_add_form information
 */
function slideshow_add_form_submit($form, &$form_state) {
  $slideshow_submission = (object) $form_state['values'];
  field_attach_submit('slideshow', $slideshow_submission, $form, $form_state);
  $slideshow = slideshow_save($slideshow_submission);
  $form_state['redirect'] = 'admin/structure/slideshow/manage';
}





