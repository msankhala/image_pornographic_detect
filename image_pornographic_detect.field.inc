<?php

/**
 * @file
 * Image pornographic detect option.
 * Provide option for pornographic image detection for image field.
 */

/**
 * Implements hook_field_info_alter().
 */
function image_pornographic_detect_field_info_alter(&$info) {
  foreach (array('file', 'image') as $type) {
    if (isset($info[$type])) {
      $info[$type]['instance_settings'] += array(
        'resup' => 0,
        'resup_max_filesize' => '',
      );
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for field_ui_field_edit_form().
 */
function image_pornographic_detect_form_field_ui_field_edit_form_alter(&$form, &$form_state, $form_id) {
  if (image_pornographic_detect_field_widget_support($form['#instance']['widget']['type'])) {
    $settings = $form['#instance']['settings'];

    $additions['image_pornographic_detect_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Image pornographic Detect settings'),
      '#collapsible' => TRUE,
      '#collapsed' => isset($settings['image_pornographic_detect']) ? !$settings['image_pornographic_detect'] : TRUE,
      '#parents' => array('instance', 'settings'),
      '#weight' => 20,
    );

    $additions['image_pornographic_detect_settings']['image_pornographic_detect'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Image Pornographic Detect'),
      '#description' => t('This settig will enable the pornographic detection when user upload an image. If this option is checked and user upload a pornographic image this will restrict the uploading of image and will show a message. You can configure more options<a href="@pornographic_detect_setting")>here</a>.', array('pornographic_detect_setting' => '/admin/config')),
      '#default_value' => isset($settings['image_pornographic_detect']) ? $settings['image_pornographic_detect'] : FALSE,
    );

    $form['instance']['settings'] += $additions;
  }
}

/**
 * Check whether our module has support for a widget type.
 */
function image_pornographic_detect_field_widget_support($widget_type) {
  return $widget_type == 'file_generic' || $widget_type == 'image_image';
}
