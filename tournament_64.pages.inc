<?php

/**
 * @file
 * Tournament 64 page views
 * 
 */
function tour64_bracket($teams, $winners, $sections, $league_winners = NULL) {

  $build = array();
  
  $build[] = array(
    '#markup' => '<div id="bracket" class="tour64-bracket-block">',
  );
  
  if (!empty($league_winners)) {
    $tour64_won = _tour64_fill_won($league_winners, $winners);
  }
  
  for ($i = 1; $i <= 32; $i++) {
    $round_1_left_teams[] = array('name' => $teams[$i]['name']);
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_1_left_teams,
    '#tour64_round' => 1,
    '#tour64_side' => 'left',
  );

  for ($i = 1; $i <= 16; $i++) {
    $round_2_left_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_2_left_teams,
    '#tour64_round' => 2,
    '#tour64_side' => 'left',
  );
  
  for ($i = 33; $i <= 40; $i++) {
    $round_3_left_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_3_left_teams,
    '#tour64_round' => 3,
    '#tour64_side' => 'left'
  );

  for ($i = 49; $i <= 52; $i++) {
    $round_4_left_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_4_left_teams,
    '#tour64_round' => 4,
    '#tour64_side' => 'left',
  );

  for ($i = 57; $i <= 58; $i++) {
    $round_5_left_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_5_left_teams,
    '#tour64_round' => 5,
    '#tour64_side' => 'left'
  );

  for ($i = 61; $i <= 63; $i++) {
    $round_6_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_6_teams,
    '#tour64_round' => 6,
    '#tour64_side' => 'centre',
    '#tour64_extras' => array('Finals', NULL, 'Champion'),
  );

  for ($i = 59; $i <= 60; $i++) {
    $round_5_right_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_5_right_teams,
    '#tour64_round' => 5,
    '#tour64_side' => 'right',
  );

  for ($i = 53; $i <= 56; $i++) {
    $round_4_right_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_4_right_teams,
    '#tour64_round' => 4,
    '#tour64_side' => 'right',
  );

  for ($i = 41; $i <= 48; $i++) {
    $round_3_right_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_3_right_teams,
    '#tour64_round' => 3,
    '#tour64_side' => 'right',
  );

   for ($i = 17; $i <= 32; $i++) {
    $round_2_right_teams[] = array(
      'name' => !empty($winners[$i]) ? $teams[$winners[$i]]['name'] : NULL,
      'won' => isset($tour64_won[$i]) ? $tour64_won[$i] : NULL,
    );
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_2_right_teams,
    '#tour64_round' => 2,
    '#tour64_side' => 'right',
  );

  for ($i = 33; $i <= 64; $i++) {
    $round_1_right_teams[] = array('name' => $teams[$i]['name']);
  }

  $build[] = array(
    '#theme' => 'tour64_bracket',
    '#tour64_teams' => $round_1_right_teams,
    '#tour64_round' => 1,
    '#tour64_side' => 'right',
  );

  $build[] = array(
    '#markup' => '</div>',
  );
  
  return $build;  
}

function tour64_entity_view($entity_type, $entity_id) {
  drupal_set_title(entity_label($entity_type, $entity_id));
  return entity_view($entity_type, array(entity_id($entity_type, $entity_id) => $entity_id), 'full');
}

function tour64_entry_bracket($entity) {
  $league_entity = entity_load('tour64_leagues', array($entity->league_id));
  $league_entity = reset($league_entity);
  return tour64_bracket($league_entity->teams, $entity->winners, $league_entity->sections, $league_entity->winners);
}

function tour64_league_bracket($entity) {
  return tour64_bracket($entity->teams, $entity->winners, $entity->sections);
}

/**
 * style winners and losers
 *
 */
function _tour64_fill_won($league_winners, $entry_winners) {

  $tour64_won = array();
  $teams_lost = tour64_teams_lost($league_winners);
  // check if this pick is a winner or loser and format accordingly
  for ($game_number = 1; $game_number <= 63; $game_number++) {
    // if no winner for this game yet, check to see if team lost in previous rounds
    if (empty($league_winners[$game_number])) {
      if (in_array($entry_winners[$game_number], $teams_lost)) {
        $tour64_won[$game_number] = FALSE;
      } else {
        $tour64_won[$game_number] = NULL;
      }
    } elseif ($league_winners[$game_number] == $entry_winners[$game_number]) {
      $tour64_won[$game_number] = TRUE;
     
    } else {
      $tour64_won[$game_number] = FALSE;
    }
  }

  return $tour64_won;
  
}
