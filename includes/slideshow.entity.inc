<?php

function slideshow_entity_info() {
  $slideshow_info['slideshow'] = array(
    'label' => t('Slideshow Entity'),
    'controller class' => 'slideshowController',
    'base table' => 'slideshow',
    'fieldable' => TRUE,
    'entity keys' => array(
      'id' => 'sid',
    ),
    'static cache' => TRUE,
    'bundles' => array(
      'slideshow' => array(
        'label' => 'slideshow',
        'admin' => array(
          'path' => 'admin/structure/slideshow/manage',
          'access arguments' => array('administer slideshow entities'),
        ),
      ),
    ),
    'view modes' => array(
      'full' => array(
        'label' => t('Full'),
        'custom settings' =>  FALSE,
      ),
    )

  );
  return $slideshow_info;
}

/**
 * Callback for displaying the entity
 */
function slideshow_view($slideshow, $view_mode = 'full') {

  $slideshow->content = array();

  // Build fields content - this where the FieldAPI really comes in to play. The task
  // is relatively trivial for us - it all gets taken care of by Drupal core.
  field_attach_prepare_view('slideshow', array($slideshow->sid => $slideshow), $view_mode);
  entity_prepare_view('slideshow', array($slideshow->sid => $slideshow));
  $slideshow->content += field_attach_view('slideshow', $slideshow, $view_mode);
  $slideshow->content += array(
    '#theme'     => 'slideshow',
    '#element'   => $slideshow,
    '#view_mode' => 'full',
    '#language'  => NULL,
  );

  return $slideshow->content;
}


function slideshow_theme($existing, $type, $theme, $path) {
  return array(
    'slideshow' => array(
      'variables' => array('element' => null),
    ),
  );
}

function slideshow_field_extra_fields() {
  $return = array();
  $return['slideshow']['title'] = array(
    'form' => array(
      'title' => array(
        'label' => t('Title'),
        'description' => t('Slideshow Entity Title'),
      ),
    ),
  );

  return $return;
}

function slideshow_load($sid = NULL, $reset = FALSE) {
  $sids = (isset($sid) ? array($sid) : array());
  $slideshow = slideshow_load_multiple($sids, $reset);
  return $slideshow ? reset($slideshow) : FALSE;
}

function slideshow_load_multiple($sids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('slideshow', $sids, $conditions, $reset);
}

/**
 * Callback for title
 */
function slideshow_page_title($slideshow) {
  return $slideshow->title;
}

/**
 * We save the basic entity by calling the controller.
 */
function slideshow_save(&$slideshow) {
  return entity_get_controller('slideshow')->save($slideshow);
}

function slideshow_delete($slideshow) {
  return entity_get_controller('slideshow')->delete($slideshow);
}


/**
 * BasicController extends the DrupalDefaultEntityController by adding
 * an extra function to handle saving of entities.
 */
class slideshowController extends DrupalDefaultEntityController{

  public function save($slideshow) {

    if (empty($slideshow->created)) {
      $slideshow->created = REQUEST_TIME;
    }
    $slideshow->changed = REQUEST_TIME;

    if (!isset($slideshow->sid) || $slideshow->sid == '') {
      drupal_write_record('slideshow', $slideshow);
      field_attach_insert('slideshow', $slideshow);
      module_invoke_all('entity_insert', 'slideshow', $slideshow);
    }else{
      $slideshow->original = isset($slideshow->original) ? $slideshow->original : NULL;
      drupal_write_record('slideshow', $slideshow, 'sid');
      field_attach_update('slideshow', $slideshow);
      module_invoke_all('entity_update', 'slideshow', $slideshow);
    }
    return $slideshow;
  }

  public function delete($sid) {
    $this->delete_multiple(array($sid));
  }

  public function delete_multiple($sids) {
    $transaction = db_transaction();
    if (!empty($sids)) {
      $slideshows = slideshow_load_multiple($sids);

      try {
        foreach ($slideshows as $sid => $slideshow) {

          module_invoke_all('slideshow_delete', $slideshow);
          module_invoke_all('entity_delete', $slideshow, 'slideshow');
          field_attach_delete('slideshow', $slideshow);

        }

        db_delete('slideshow')
          ->condition('sid', $sids, 'IN')
          ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('slideshow', $e);
        throw $e;
      }

      entity_get_controller('slideshow')->resetCache();
    }

  }

}



/**
 * Implements hook_help().
 */
function slideshow_help($path, $arg) {
  switch ($path) {
    case 'admin/help#slideshow':
      return "<p>" . t('Once you have activated the module you can configure your slideshow bundle by visiting "admin/structure/slideshow/manage"') . "</p>";
  }
}

