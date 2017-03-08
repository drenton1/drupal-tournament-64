<?php

/**
 * @file
 * Provides metadata for the Tournament 64 entities.
 */

/**
 * Implements hook_entity_property_info().
 */
function tournament_64_entity_property_info() {

  $info = array();
  
  $properties = &$info['tour64_leagues']['properties'];

  $properties['description'] = array(
    'label' => t('Description'),
    'description' => t('Description'),
    'type' => 'text',
    'schema field' => 'description',
    'setter callback' => 'entity_property_verbatim_set',
  );
  
  $properties['close_time'] = array(
    'label' => t('Close Time'),
    'description' => t('Close Time'),
    'type' => 'date',
    'schema field' => 'close_time',
    'setter callback' => 'entity_property_verbatim_set',
  );
  
  for ($i = 1; $i <= 6; $i++) {
    $field = 'round_' . $i . '_points';
    $properties[$field] = array(
      'label' => t('Round ' . $i . ' Points'),
      'description' => t('Round ' . $i . ' Points'),
      'type' => 'integer',
      'schema field' => $field,
      'setter callback' => 'entity_property_verbatim_set',
    );
  }

  for ($i = 1; $i <= 4; $i++) {
    $field = 'section_' . $i . '_name';
    $properties[$field] = array(
      'label' => t('Section ' . $i),
      'description' => t('Section ' . $i),
      'type' => 'text',
      'schema field' => $field,
      'setter callback' => 'entity_property_verbatim_set',
    );
  }
  
  // Add a computed property for the entity URL and expose it to views.
  $properties['url'] = array(
    'label' => t('URL'),
    'description' => t('The URL of the entity.'),
    'getter callback' => 'entity_metadata_entity_get_properties',
    'type' => 'uri',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );
  
  $properties = &$info['tour64_entries']['properties'];

  $properties['nickname'] = array(
    'label' => t('Nickname'),
    'description' => t('Nickname'),
    'type' => 'text',
    'schema field' => 'nickname',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['league_id'] = array(
    'label' => t('League ID'),
    'description' => t('League ID'),
    'type' => 'integer',
    'schema field' => 'league_id',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['uid'] = array(
    'label' => t('User ID'),
    'description' => t('User ID'),
    'type' => 'integer',
    'schema field' => 'uid',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['paid'] = array(
    'label' => t('Paid'),
    'description' => t('Paid'),
    'type' => 'text',
    'schema field' => 'paid',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['tiebreaker'] = array(
    'label' => t('Tiebreaker'),
    'description' => t('Tiebreaker'),
    'type' => 'integer',
    'schema field' => 'tiebreaker',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['points'] = array(
    'label' => t('Points'),
    'description' => t('Points'),
    'type' => 'integer',
    'schema field' => 'points',
    'setter callback' => 'entity_property_verbatim_set',
  );
  
  $properties['position'] = array(
    'label' => t('Position'),
    'description' => t('Position'),
    'type' => 'integer',
    'schema field' => 'position',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['total_points_possible'] = array(
    'label' => t('Total Points Possible'),
    'description' => t('Total Points Possible'),
    'type' => 'integer',
    'schema field' => 'total_points_possible',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['prediction_first'] = array(
    'label' => t('First Place'),
    'description' => t('First Place'),
    'type' => 'integer',
    'schema field' => 'prediction_first',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['prediction_second'] = array(
    'label' => t('Second Place'),
    'description' => t('Second Place'),
    'type' => 'integer',
    'schema field' => 'prediction_second',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['prediction_third'] = array(
    'label' => t('Tie Third Place'),
    'description' => t('Tie Third Place'),
    'type' => 'integer',
    'schema field' => 'prediction_third',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['prediction_fourth'] = array(
    'label' => t('Tie Third Place'),
    'description' => t('Tie Third Place'),
    'type' => 'integer',
    'schema field' => 'prediction_fourth',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['league_id'] = array(
    'label' => t('League ID'),
    'description' => t('League ID'),
    'type' => 'integer',
    'schema field' => 'league_id',
    'setter callback' => 'entity_property_verbatim_set',
  );

  // Add a computed property for the entity URL and expose it to views.
  $properties['url'] = array(
    'label' => t('URL'),
    'description' => t('The URL of the entity.'),
    'getter callback' => 'entity_metadata_entity_get_properties',
    'type' => 'uri',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  // add actual prediction names
  $properties['prediction_first_name'] = array(
    'label' => t('First Place Name'),
    'description' => t('First Place Name'),
    'getter callback' => 'tour64_get_prediction_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  $properties['prediction_second_name'] = array(
    'label' => t('Second Place Name'),
    'description' => t('Second Place Name'),
    'getter callback' => 'tour64_get_prediction_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  $properties['prediction_third_name'] = array(
    'label' => t('Tie Third Place Name'),
    'description' => t('Tie Third Place Name'),
    'getter callback' => 'tour64_get_prediction_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  $properties['prediction_fourth_name'] = array(
    'label' => t('Tie Third Place Name'),
    'description' => t('Tie Third Place Name'),
    'getter callback' => 'tour64_get_prediction_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  // add css for predictions
  $properties['prediction_first_css'] = array(
    'label' => t('First Place CSS'),
    'description' => t('First Place CSS'),
    'getter callback' => 'tour64_get_prediction_css_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  $properties['prediction_second_css'] = array(
    'label' => t('Second Place CSS'),
    'description' => t('Second Place CSS'),
    'getter callback' => 'tour64_get_prediction_css_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  $properties['prediction_third_css'] = array(
    'label' => t('Third Place CSS'),
    'description' => t('Third Place CSS'),
    'getter callback' => 'tour64_get_prediction_css_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  $properties['prediction_fourth_css'] = array(
    'label' => t('Fourth Place CSS'),
    'description' => t('Fourth Place CSS'),
    'getter callback' => 'tour64_get_prediction_css_callback',
    'type' => 'text',
    'computed' => TRUE,
    'entity views field' => TRUE,
  );

  return $info;
  
}
