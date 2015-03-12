<?php

/**
 * @file
 * Tournament 64 forms
 *
 */
/**
 * Delete confirmation form.
 */
function tour64_delete_form($form, &$form_state, $entity) {
  $form_state['entity'] = $entity;
  $entity_uri = entity_uri($entity->entityType(), $entity);

  $current_path = explode('/', request_path());
  $redirect_array = array_slice($current_path, 0, -1);
  $redirect_path = implode('/', $redirect_array);
  
  if (empty($redirect_path)) {
    $redirect_path = $entity_uri['path'];
  }
  
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => entity_label($entity->entityType(), $entity))),
    $redirect_path,
    t('This action cannot be undone.'),
    t('Confirm Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function tour64_delete_form_submit($form, &$form_state) {
  $entity = $form_state['entity'];
  
  $entity_type = $entity->entityType();
  $league_id = $entity->league_id;
  
  entity_delete($entity->entityType(), entity_id($entity->entityType(), $entity));
  
  drupal_set_message(t('%title deleted.', array('%title' => entity_label($entity->entityType(), $entity))));
  // remove the last 2 path components to get redirect
  $current_path = explode('/', request_path());
  $redirect_array = array_slice($current_path, 0, -2);
  $redirect_path = implode('/', $redirect_array);
  if (empty($redirect_path)) {
    $form_state['redirect'] = '<front>';
  } else {
    $form_state['redirect'] = $redirect_path;
  }
  
  if ($entity_type == 'tour64_entries') {
    _tour64_update_entry_points($league_id);
  }
}

function tour64_entry_add($league_entity = NULL) {
  // add winners
  for ($i = 1; $i <= 63; $i++) {
    $winners[$i] = NULL;
  }
  
  global $user;
  
  $entity = entity_create('tour64_entries',
    array(
      'type' => 'tour64_entries',
      'league_id' => $league_entity->league_id,
      'winners' => $winners,
      'uid' => $user->uid,
    )
  );
  
  drupal_set_title($league_entity->description . ' - Create New Entry ');
  $output = drupal_get_form('tour64_entry_form', $entity);
  return $output;
}

function tour64_entry_addfavourite($league_entity = NULL) {
  // add winners
  for ($i = 1; $i <= 32; $i++) {
    $winners[$i] = $i * 2 -1;
  }
  for ($i = 33; $i <= 60; $i++) {
    $winners[33] = 1;
    $winners[34] = 7;
    $winners[35] = 11;
    $winners[36] = 15;
    $winners[37] = 17;
    $winners[38] = 23;
    $winners[39] = 27;
    $winners[40] = 31;
    $winners[41] = 33;
    $winners[42] = 39;
    $winners[43] = 43;
    $winners[44] = 47;
    $winners[45] = 49;
    $winners[46] = 55;
    $winners[47] = 59;
    $winners[48] = 63;
    $winners[49] = 1;
    $winners[50] = 15;
    $winners[51] = 17;
    $winners[52] = 31;
    $winners[53] = 33;
    $winners[54] = 47;
    $winners[55] = 49;
    $winners[56] = 63;
    $winners[57] = 1;
    $winners[58] = 17;
    $winners[59] = 33;
    $winners[60] = 49;
  }
  for ($i = 61; $i <= 63; $i++) {
    $winners[$i] = NULL;
  }
  
  global $user;
  
  $entity = entity_create('tour64_entries',
    array(
      'type' => 'tour64_entries',
      'league_id' => $league_entity->league_id,
      'winners' => $winners,
      'uid' => $user->uid,
    )
  );
  
  drupal_set_title($league_entity->description . ' - Create New Entry ');
  $output = drupal_get_form('tour64_entry_form', $entity);
  return $output;
}

function tour64_entry_form($form, &$form_state, $entity) {

  $form = array();
  
  $form['nickname'] = array(
    '#type' => 'textfield',
    '#title' => t('Nickname'),
    '#required' => TRUE,
    '#default_value' => !empty($entity->nickname) ? $entity->nickname : NULL,
  );

  $form['tiebreaker'] = array(
    '#type' => 'textfield',
    '#title' => t('Tiebreaker'),
    '#description' => t('Total combined points of final game.'),
    '#required' => user_is_anonymous() ? TRUE : FALSE,
    '#default_value' => !empty($entity->tiebreaker) ? $entity->tiebreaker : NULL,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['#attached']['css'][] = array(
    'data' => drupal_get_path('module', 'tournament_64') . '/tournament_64.css',
  );
  
  $form_state['entity'] = $entity;
  $league_entity = entity_load('tour64_leagues', array($entity->league_id));
  $league_entity = reset($league_entity);
  $form_state['tour64_teams'] = $league_entity->teams;

  $form['bracket'] = _tour64_fill_bracket_form($league_entity->teams, $entity->winners, $league_entity->sections);
  $form['winners'] = _tour64_fill_winners_form($entity->winners);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('tour64_entry_form_submit'),
  );

  $form['#validate'][] = 'tour64_entry_form_validate';

  return $form;
}

/**
 * entry form validation.
 */
function tour64_entry_form_validate($form, &$form_state) {
  if (!empty($form_state['values']['op'])) {
    // check for duplicate nickname
    $result = db_query('SELECT entry_id FROM {tour64_entries}
      WHERE league_id = :league_id and nickname = :nickname and entry_id <> :entry_id',
      array(':league_id' => $form_state['entity']->league_id,
            ':nickname' => $form_state['values']['nickname'],
            ':entry_id' => !empty($form_state['entity']->entry_id) ? $form_state['entity']->entry_id : 0))->fetchField();
      
    if (!empty($result)) {
      form_set_error('nickname', t('Nickname already exists.'));
    }

    $picks_remaining = FALSE;
    for ($i = 1; $i <= 63; $i++) {
      if (empty($form_state['values']['winners'][$i])) {
        $picks_remaining = TRUE;
        break;
      }
    }
    if ($picks_remaining and user_is_anonymous()) {
      form_set_error('', t('Please pick a winner for every game.'));
    } elseif ($picks_remaining) {
      drupal_set_message(t('You still have picks remaining.
        Be sure to have them all in before the start of the tournament.'), 'warning');
    }
    if (user_is_logged_in() and empty($form_state['values']['tiebreaker'])) {
      drupal_set_message(t('Don\'t forget to fill in the tiebreaker field before the start of the tournament.'), 'warning');
    }

  }
 
}

/**
 * entry submit handler.
 */
function tour64_entry_form_submit($form, &$form_state) {
  $entity = $form_state['entity'];
  entity_form_submit_build_entity($entity->entityType(), $entity, $form, $form_state);
  entity_save($entity->entityType(), $entity);
  $entity_uri = entity_uri($entity->entityType(), $entity);
  $form_state['redirect'] = 'tournament-64/' . $entity->league_id . '/entries';
  drupal_set_message(t('Saved'));
  _tour64_update_entry_points($entity->league_id);
}

function tour64_entry_paid_form($form, &$form_state, $entity) {
  
  $form_state['entity'] = $entity;
  
  $form = array();
  
  $form['paid'] = array(
    '#type' => 'select',
    '#title' => t('Paid'),
    '#required' => TRUE,
    '#options' => array('Y' => t('Yes'), 'N' => t('No')),
    '#default_value' => !empty($entity->paid) ? $entity->paid : NULL,
  );

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('tour64_entry_paid_form_submit'),
  );

  return $form;
}

/**
 * paid submit handler.
 */
function tour64_entry_paid_form_submit($form, &$form_state) {
  $entity = $form_state['entity'];
  entity_form_submit_build_entity($entity->entityType(), $entity, $form, $form_state);
  entity_save($entity->entityType(), $entity);
  drupal_set_message(t('Saved'));
}

function tour64_league_add() {
  global $user;
  $entity = entity_create('tour64_leagues', array('type' => 'tour64_leagues'));
  drupal_set_title('Create New League');
  $output = drupal_get_form('tour64_league_form', $entity);
  return $output;
}

function tour64_league_form($form, &$form_state, $entity) {
  
  $form_state['entity'] = $entity;
  $timezone = date_default_timezone();
  
  $form = array();
  
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#required' => TRUE,
    '#default_value' => !empty($entity->description) ? $entity->description : NULL,
  );

  $form['close_time'] = array(
    '#type' => 'date_popup',
    '#title' => t('Close Time'),
    '#required' => TRUE,
    '#default_value' => !empty($entity->close_time) ? $entity->close_time : NULL,
    '#date_timezone' => $timezone,
  );
  
  $form['points'] = array(
    '#type' => 'fieldset',
    '#title' => t('Points'),
    '#tree' => TRUE,
  );

  for ($i = 1; $i <= 6; $i++) {
    $form['points'][$i] = array(
      '#type' => 'textfield',
      '#title' => t("Round $i"),
      '#required' => FALSE,
      '#default_value' => !empty($entity->points[$i]) ? $entity->points[$i] : NULL,
    );
  }

  $form['sections'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sections'),
    '#description' => t('1 : Top Left<br>2 : Bottom Left<br>3 : Top Right<br>4 : Bottom Right'),
    '#tree' => TRUE,
  );
  
  for ($i = 1; $i <= 4; $i++) {
    $form['sections'][$i] = array(
      '#type' => 'textfield',
      '#title' => t("Section $i"),
      '#required' => FALSE,
      '#default_value' => !empty($entity->sections[$i]) ? $entity->sections[$i] : NULL,
    );
  }
  
  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('tour64_league_form_submit'),
  );

  return $form;
}

/**
 * Entity submit handler.
 */
function tour64_league_form_submit($form, &$form_state) {
  $entity = $form_state['entity'];
  entity_form_submit_build_entity($entity->entityType(), $entity, $form, $form_state);
  entity_save($entity->entityType(), $entity);
  $entity_uri = entity_uri($entity->entityType(), $entity);
  $form_state['redirect'] = $entity_uri['path'];
  drupal_set_message(t('Saved'));
  _tour64_update_entry_points($entity->league_id);
}

function tour64_league_teams_form($form, &$form_state, $entity) {
  
  $form_state['entity'] = $entity;
  
  $form = array();
  
  $form['teams_section_1'] = _tour64_fill_teams_form(1, 0, $entity);
  $form['teams_section_2'] = _tour64_fill_teams_form(2, 16, $entity);
  $form['teams_section_3'] = _tour64_fill_teams_form(3, 32, $entity);
  $form['teams_section_4'] = _tour64_fill_teams_form(4, 48, $entity);
  
  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('tour64_league_form_submit'),
  );

  return $form;
}


function tour64_league_winners_form($form, &$form_state, $entity) {

  $form['#attached']['css'][] = array(
    'data' => drupal_get_path('module', 'tournament_64') . '/tournament_64.css',
  );
  
  $form_state['entity'] = $entity;
  $form_state['tour64_teams'] = $entity->teams;
  
  $form['bracket'] = _tour64_fill_bracket_form($entity->teams, $entity->winners, $entity->sections);
  $form['winners'] = _tour64_fill_winners_form($entity->winners);
 
  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('tour64_league_winners_form_submit'),
  );

  return $form;
}

/**
 * Entity submit handler.
 */
function tour64_league_winners_form_submit($form, &$form_state) {
  $entity = $form_state['entity'];
  entity_form_submit_build_entity($entity->entityType(), $entity, $form, $form_state);
  entity_save($entity->entityType(), $entity);
  $entity_uri = entity_uri($entity->entityType(), $entity);
  $form_state['redirect'] = $entity_uri['path'];
  drupal_set_message(t('Saved'));
  _tour64_update_entry_points($entity->league_id);
}

function _tour64_calculate_points($pick_number, $league_entity, $entry_winners, $teams_lost, &$points, &$possible_points_remaining) {

  if (empty($entry_winners[$pick_number])) {
    return;
  }
  if ($pick_number < 33) {
    $round = 1;
  } elseif ($pick_number < 49) {
    $round = 2;
  } elseif ($pick_number < 57) {
    $round = 3;
  } elseif ($pick_number < 61) {
    $round = 4;
  } elseif ($pick_number < 63) {
    $round = 5;
  } elseif ($pick_number < 64) {
    $round = 6;
  }
  if ($league_entity->winners[$pick_number] == $entry_winners[$pick_number]) {
    $points = $points + $league_entity->points[$round];
  // if no winner yet and this is first round, include as possible points
  } elseif (empty($league_entity->winners[$pick_number]) && $pick_number < 33) {
    $possible_points_remaining = $possible_points_remaining + $league_entity->points[$round];
  } else {
    // if they have not lost, include as possible points
    if (!in_array($entry_winners[$pick_number], $teams_lost)) {
      $possible_points_remaining = $possible_points_remaining + $league_entity->points[$round];
    }
  }

}

function _tour64_cmp_by_points($a, $b) {
  return $b['points'] - $a['points'];
}

function _tour64_fill_bracket_form($teams, $winners, $sections) {

  $bracket_form = array(
    '#prefix' => '<div id="bracket" class="tour64-bracket-block">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  for ($i = 1; $i <= 127; $i++) {
    
    if ($i <= 32) {
      $weight = $i;
    } elseif ($i <= 64) {
      $weight = 11000 + $i;
    } elseif ($i <= 80) {
      $weight = 2000 + $i;
    } elseif ($i <= 96) {
      $weight = 10000 + $i;
    } elseif ($i <= 104) {
      $weight = 3000 + $i;
    } elseif ($i <= 112) {
      $weight = 9000 + $i;
    } elseif ($i <= 116) {
      $weight = 4000 + $i;
    } elseif ($i <= 120) {
      $weight = 8000 + $i;
    } elseif ($i <= 122) {
      $weight = 5000 + $i;
    } elseif ($i <= 124) {
      $weight = 7000 + $i;
    } else {
      $weight = 6000 + $i;
    }

    // add a div for each column
    $prefix = '';
    $suffix = '';
    if ($i == 1) $prefix .= '<div class="tour64-round-1-left">';
    if ($i == 33) $prefix .= '<div class="tour64-round-1-right">';
    if ($i == 65) $prefix .= '<div class="tour64-round-2-left">';
    if ($i == 81) $prefix .= '<div class="tour64-round-2-right">';
    if ($i == 97) $prefix .= '<div class="tour64-round-3-left">';
    if ($i == 105) $prefix .= '<div class="tour64-round-3-right">';
    if ($i == 113) $prefix .= '<div class="tour64-round-4-left">';
    if ($i == 117) $prefix .= '<div class="tour64-round-4-right">';
    if ($i == 121) $prefix .= '<div class="tour64-round-5-left">';
    if ($i == 123) $prefix .= '<div class="tour64-round-5-right">';
    if ($i == 125) $prefix .= '<div class="tour64-round-6-centre">';
    
    // add a div for each match
    if ($i == 127) {
      $prefix .= '<div class="tour64-round-6-spacer"></div>';
      $prefix .= '<div id="tour64-winner">Champion';
      $suffix .= '</div>';
    } else {
      if ($i % 2 == 0) {
        $suffix .= '</div>';
        if ($i <= 64) {
          $suffix .= '<div class="tour64-round-1-spacer"></div>';
        } elseif ($i > 64 and $i <= 96) {
          $suffix .= '<div class="tour64-round-2-spacer"></div>';
        } elseif ($i > 96 and $i <= 112) {
          $suffix .= '<div class="tour64-round-3-spacer"></div>';
        } elseif ($i > 112 and $i <= 120) {
          $suffix .= '<div class="tour64-round-4-spacer"></div>';
        } elseif ($i > 120 and $i <= 124) {
          $suffix .= '<div class="tour64-round-5-spacer"></div>';
        } elseif ($i > 124 and $i <= 126) {
        }
      } else {
        if ($i <= 64) {
          $prefix .= '<div class="tour64-round-1-spacer"></div>';
          if ($i <= 32) {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-left">';
          } else {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-right">';
          }
        } elseif ($i > 64 and $i <= 96) {
          $prefix .= '<div class="tour64-round-2-spacer"></div>';
          if ($i <= 80) {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-left">';
          } else {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-right">';
          }
        } elseif ($i > 96 and $i <= 112) {
          $prefix .= '<div class="tour64-round-3-spacer"></div>';
          if ($i <= 104) {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-left">';
          } else {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-right">';
          }
        } elseif ($i > 112 and $i <= 120) {
          $prefix .= '<div class="tour64-round-4-spacer"></div>';
          if ($i <= 116) {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-left">';
          } else {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-right">';
          }
        } elseif ($i > 120 and $i <= 124) {
          $prefix .= '<div class="tour64-round-5-spacer"></div>';
          if ($i <= 122) {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-left">';
          } else {
            $prefix .= '<div id="tour64-match-' . $i . '" class="tour64-match-right">';
          }
        } elseif ($i > 124 and $i <= 126) {
          $prefix .= '<div id="tour64-match-' . $i . '">Finals';
        }
      }
    }

    if (in_array($i, array(32, 64, 80, 96, 104, 112, 116, 120, 122, 124, 127))) {
      $suffix .= '</div>';
    }
    
    if (!empty($prefix)) {
      $bracket_form['tour64_prefix_' . $i] = array(
        '#markup' => $prefix,
        '#weight' => ($weight - 0.1),
      );
    }
    if (!empty($suffix)) {
      $bracket_form['tour64_suffix_' . $i] = array(
        '#markup' => $suffix,
        '#weight' => ($weight + 0.1),
      );
    }
    
    $bracket_form[$i] = array(
      '#type' => 'textfield',
      '#size' => 12,
      '#theme' => 'tour64_textfield',
      '#theme_wrappers' => array(),
      '#weight' => $weight,
      '#attributes' => array('readonly'=>'readonly'),
      '#ajax' => array(
        'callback' => '_tour64_pick_callback',
        'progress' => array('message' => NULL),
        'event' => 'click',
      ),
    );

    if ($i <= 64) {
      $bracket_form[$i]['#default_value'] = t($teams[$i]['name']);
    } elseif (!empty($winners[$i-64])) {
      $bracket_form[$i]['#default_value'] = t($teams[$winners[$i-64]]['name']);
    } else {
      $bracket_form[$i]['#default_value'] = NULL;
    }
  }
  
  return $bracket_form;
  
}

function _tour64_fill_teams_form($section, $teams_start, $entity) {
  
  $teams_form = array(
    '#type' => 'fieldset',
    '#title' => t($entity->sections[$section]),
    '#prefix' => '<div id="teams_section_' . $section . '">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );
 
  for ($i = 1; $i <= 16; $i++) {
   
    $teams_form[$teams_start+$i] = array(
      '#type' => 'textfield',
      '#title' => t($entity->teams[$teams_start+$i]['seed']),
      '#title_display' => 'before', 
      '#default_value' => t($entity->teams[$teams_start+$i]['description']),
      '#prefix' => '<div class="container-inline">',
      '#suffix' => '</div>',
    );
    
  }
  
  return $teams_form;
  
}

function _tour64_fill_winners_form($winners) {
  $winners_form = array(
    '#tree' => TRUE,
  );
  
  for ($i = 1; $i <= 63; $i++) {
    $winners_form[$i] = array(
      '#prefix' => '<div id="tour64-winner-' . $i . '">',
      '#suffix' => '</div>',
      '#type' => 'hidden',
      '#default_value' => $winners[$i],
    );
  }

  return $winners_form;
}

function _tour64_pick_callback($form, &$form_state) {

  $element_exploded = explode('[', $form_state['input']['_triggering_element_name']);
  $element_pieces = array();
  foreach ($element_exploded as $element_piece) {
    $element_pieces[] = str_replace(']', '', $element_piece);
  }
  $pick_number = $element_pieces[1];
  
  // update all picks this pick affects
  $pick_updates = _tour64_pick_updates($pick_number);

  if ($pick_number < 65) {
    $team_id = $pick_number;
  } else {
    $team_id = $form['winners'][$pick_number-64]['#value'];
  }
  
  $ajax_commands = array();
  $team_replaced = NULL;
  foreach ($pick_updates as $key => $value) {
    $winner_key = $value - 64;
    if ($key == 0 and $form['winners'][$winner_key]['#value'] <> $team_id) {
      $team_replaced = $form['winners'][$winner_key]['#value'];
      
      $form['bracket'][$value]['#value'] = t($form_state['tour64_teams'][$team_id]['name']);
      $form['winners'][$winner_key]['#value'] = $team_id;

      $ajax_commands[] = ajax_command_replace('#tour64-id-' . $value,
        render($form['bracket'][$value]));
      $ajax_commands[] = ajax_command_replace('#tour64-winner-' . $winner_key,
        render($form['winners'][$winner_key]));
    } elseif ($key > 0 and !empty($team_replaced) and !empty($form['winners'][$winner_key]['#value']) and
      $form['winners'][$winner_key]['#value'] == $team_replaced) {
        
      $form['bracket'][$value]['#value'] = NULL;
      $form['winners'][$winner_key]['#value'] = NULL;

      $ajax_commands[] = ajax_command_replace('#tour64-id-' . $value,
        render($form['bracket'][$value]));
      $ajax_commands[] = ajax_command_replace('#tour64-winner-' . $winner_key,
        render($form['winners'][$winner_key]));
    }
  }
  
  return array(
    '#type' => 'ajax',
    '#commands' => $ajax_commands,
  );

}

function _tour64_pick_updates($pick_number) {

  $pick_updates = array();
  while ($pick_number <= 126) {
    if ($pick_number&1) {
      $pick_number = $pick_number + 1;
    }
    $next_pick_number = $pick_number / 2 + 64;
    $pick_updates[] = $next_pick_number;
    $pick_number = $next_pick_number;
  }

  return $pick_updates;
  
}

function _tour64_update_entry_points($league_id) {
  
  $league_entity = entity_load('tour64_leagues', array($league_id));
  $league_entity = reset($league_entity);
  $teams_lost = tour64_teams_lost($league_entity->winners);
  $entries = array();
  // update scores for this league
  $results = db_query('SELECT * FROM {tour64_entries} WHERE league_id = :league_id', array(':league_id' => $league_entity->league_id));
  foreach ($results as $record) {
    $points = 0;
    $possible_points_remaining = 0;
    // load entry winners
    $entry_winner_results = db_query('SELECT * FROM {tour64_entry_winners} WHERE entry_id = :entry_id', array(':entry_id' => $record->entry_id));
    $entry_winners = array();
    foreach ($entry_winner_results as $entry_winner_record) {
      $entry_winners[$entry_winner_record->winner_id] = $entry_winner_record->team_id;
    }
    for ($pick_number = 1; $pick_number <= 63; $pick_number++) {
      _tour64_calculate_points($pick_number, $league_entity, $entry_winners, $teams_lost, $points, $possible_points_remaining);
    }
    $entries[$record->entry_id] = array(
      'points' => $points,
      'total_points_possible' => $points + $possible_points_remaining,
    );
  }
  if (!empty($entries)) {
    uasort($entries, "_tour64_cmp_by_points");
    $total_positions_so_far = 1;
    foreach ($entries as $entry_id => $entry_entity) {
      if ($total_positions_so_far == 1) {
        $current_position = 1;
      } elseif ($last_points <> $entry_entity['points']) {
        $current_position = $total_positions_so_far;
      }
      $entries[$entry_id]['position'] = $current_position;
      $total_positions_so_far = $total_positions_so_far + 1;
      $last_points = $entry_entity['points'];
    }
    foreach ($entries as $entry_id => $entry_details) {
      $num_updated = db_update('tour64_entries')
        ->fields(array(
          'points' =>  $entry_details['points'],
          'total_points_possible' =>  $entry_details['total_points_possible'],
          'position' =>  $entry_details['position'],
        ))
        ->condition('entry_id', $entry_id, '=')
        ->execute();
    }
  }
}
