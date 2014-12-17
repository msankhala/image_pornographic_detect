<?php

/**
 * @file
 * Admin setting for image pornographic detect.
 */

/**
 * Image pornographic detect admin form.
 */
function image_pornographic_detect_admin_settings_form($form, &$form_state) {
  $options = array();
  drupal_set_message(t('You only need either "Php nudity library" or "Image nudity filter" library to make this moduel work. You can download both the library and you can choose which library to use for pornographic detection. Sometime one library may not work for some very special kind of image.'), 'status', FALSE);
  if (($php_nudity_detectro_library = libraries_detect('php-nudity-detector')) && !empty($php_nudity_detectro_library['installed'])) {
    // drupal_set_message('Php Nudity library is installed', $type = 'status', $repeat = FALSE);
    $options['php-nudity-detector'] = t('Php nudity detector (recommended)');
  }
  else {
    drupal_set_message(t('Php Nudity library is not installed. Download and place the library at /sites/all/libraries/ and make sure the path become "/sites/all/libraries/php-nudity-detector". You can download <a href="@php-nudity-detector" target="_blank">Php nudity detector library</a> here.', array('@php-nudity-detector' => 'https://github.com/FreebieStock/php-nudity-detector')), $type = 'warning', $repeat = FALSE);
  }
  if (($image_nudity_filter_library = libraries_detect('image-nudity-filter')) && !empty($image_nudity_filter_library['installed'])) {
    // drupal_set_message('image Nudity library is installed', $type = 'status', $repeat = FALSE);
    $options['image-nudity-filter'] = t('Image nudity filter');
  }
  else {
    drupal_set_message(t('Image nudity filter library is not installed. Download and place the library at /sites/all/libraries/ and make sure the path become "/sites/all/libraries/image-nudity-filter". You can download <a href="@image-nudity-filter" target="_blank">Image nudity filter library</a> here.', array('@image-nudity-filter' => 'http://www.phpclasses.org/package/3269-PHP-Determine-whether-an-image-may-contain-nudity.html#download')), $type = 'warning', $repeat = FALSE);
  }

  if (!empty($options)) {
    $form['image_pornographic_detect_active_library'] = array(
      '#type' => 'radios',
      '#title' => t('Pornographic detection library to use'),
      '#default_value' => variable_get('image_pornographic_detect_active_library', 'php-nudity-detector'),
      '#options' => $options,
      '#description' => t('Chose which library to use for image pornographic detection.'),
    );
  }

  $form['image_pornographic_detect_warning_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Warning Message to display'),
    '#description' => t('Enter the warning message to display to user when pornographic image is uploaded.'),
    '#default_value' => variable_get('image_pornographic_detect_warning_message', 'The image you uploaded contain pornographic content. You are not allowed to upload pornographic images. Please choose another image.'),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}
