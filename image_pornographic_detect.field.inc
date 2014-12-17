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
  // Add a setting to all field types.
  foreach ($info as $field_type => $field_type_info) {
    if ($field_type == 'image') {
      $info['image']['instance_settings'] += array(
        'image_pornographic_detect' => 0,
      );
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for field_ui_field_edit_form().
 */
function image_pornographic_detect_form_field_ui_field_edit_form_alter(&$form, &$form_state, $form_id) {
  global $base_url;
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
      '#description' => t('This settig will enable the pornographic detection when user upload an image. If this option is checked and user upload a pornographic image this will restrict the uploading of image and will show a message. You can configure more options <a href="@pornographic_detect_setting")>here</a>.', array('@pornographic_detect_setting' => $base_url . base_path() . 'admin/config/media/image-pornographic-detect')),
      '#default_value' => isset($settings['image_pornographic_detect']) ? $settings['image_pornographic_detect'] : FALSE,
    );

    $form['instance']['settings'] += $additions;
  }
}

/**
 * Check whether our module has support for a widget type.
 */
function image_pornographic_detect_field_widget_support($widget_type) {
  return $widget_type == 'image_image';
}

/**
 * Implement hook_field_widget_form_alter.
 * 
 * Add custom upload validator.  
 */
function image_pornographic_detect_field_widget_form_alter(&$element, &$form_state, $context) {
  // Add display_field setting to field because file_field_widget_form() assumes it is set.
  $instance = $context['instance'];
  $settings = $instance['settings'];
  $field = $context['field'];
  if (isset($settings['image_pornographic_detect']) && $field['type'] == 'image' && $settings['image_pornographic_detect']) {
    foreach (element_children($element) as $delta) {
      // Add upload validator to each image.
      $element[$delta]['#upload_validators'] = array('image_pornographic_detect_image_validate' => array($element));
    }
  }
}

/**
 * Custom image upload validator to detect porn image.
 * 
 * Custom file validator recive $file object as first argument.
 * @see file_validate
 */
function image_pornographic_detect_image_validate($file, $element) {
  $errors = array();
  $image_pornographic_detect_active_library = variable_get('image_pornographic_detect_active_library', 'php-nudity-detector');
  $temp_file_url = $file->uri;
  if (($library_found = libraries_detect($image_pornographic_detect_active_library)) && !empty($library_found['installed']) && $temp_file_url) {
    $is_porn = image_pornographic_detect_checkporn($image_pornographic_detect_active_library, $temp_file_url);
    if ($is_porn) {
      $errors[] = variable_get('image_pornographic_detect_warning_message', '');
    }
  }
  return $errors;
}

/**
 * Check the porn image.
 */
function image_pornographic_detect_checkporn($image_pornographic_detect_active_library, $file_url) {
  switch ($image_pornographic_detect_active_library) {
    case 'php-nudity-detector':
      if (!class_exists('Image_FleshSkinQuantifier')) {
        include_once libraries_get_path($image_pornographic_detect_active_library) . '/lib/Autoloader.php';
      }
      $quant = new Image_FleshSkinQuantifier($file_url);
      if ($quant->isPorn()) {
        return TRUE;
      }
      break;

    case 'image-nudity-filter':
      if (!class_exists('ImageFilter')) {
        include_once libraries_get_path($image_pornographic_detect_active_library) . '/class.ImageFilter.php';
      }
      $filter = new ImageFilter();
      $score = $filter->GetScore($file_url);
      if ($score >= 30) {
        return TRUE;
      }
      break;
  }
  return FALSE;
}
