<?php

/**
 * @file
 * Plugin to check if the title has configured string.
 */

$plugin = array(
  'title' => t('Title string'),
  'description' => t('Checks if title has configured string in title.'),
  'callback' => 'title_hide_ctools_access_check',
  'default' => array('negate' => 0),
  'summary' => 'title_hide_ctools_access_summary',
  'settings form' => 'title_hide_ctools_access_settings',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Settings form for the 'title hide' access plugin.
 */
function title_hide_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['keyword'] = array(
    '#title' => t('Keyword'),
    '#type' => 'textfield',
    '#description' => t('Title field will be searched for entered string.'),
    '#default_value' => $conf['keyword'],
    '#required' => TRUE,
  );
  return $form;
}


/**
 * Check for access.
 */
function title_hide_ctools_access_check($conf, $context) {
  // Return false if context is not set.
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }

  $node = $context->data;

  if (strpos($node->title, $conf['keyword']) !== FALSE) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Provide a summary description.
 */
function title_hide_ctools_access_summary($conf, $context) {
  $replacement = array('@keyword' => $conf['keyword']);
  return t('Checks if "@keyword" appears in title.', $replacement);
}
