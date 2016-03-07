<?php

/**
 * @file
 * theming functions for Tournament 64 module
 *
 */
function theme_tour64_bracket($variables) {
  
  // add column div
  $output = '<div class="tour64-round-' . $variables['tour64_round'] . '-' . $variables['tour64_side'] . '">';

  foreach ($variables['tour64_teams'] as $key => $team) {
    // add div for each match
    if ($key % 2 == 0) {
      $output .= '<div class="tour64-round-' . $variables['tour64_round'] . '-spacer"></div>';
      if (!empty($variables['tour64_extras'][$key])) {
        $output .= $variables['tour64_extras'][$key];
      }
      $output .= '<div class="tour64-match-' . $variables['tour64_side'] . '">';
    }

    // add div for each team
    if (!isset($team['won'])) {
      $output .= '<div class="tour64-team">' . $team['name'] . '</div>';
    } elseif ($team['won'] == TRUE) {
      $output .= '<div class="tour64-team tour64-match-won">' . $team['name'] . '</div>';
    } elseif ($team['won'] == FALSE) {
      $output .= '<div class="tour64-team tour64-match-lost">' . $team['name'] . '</div>';
    } else {
      $output .= '<div class="tour64-team">' . $team['name'] . '</div>';
    }
  
    // finish match div
    if (!($key % 2) == 0) {
      $output .= '</div>';
      $output .= '<div class="tour64-round-' . $variables['tour64_round'] . '-spacer"></div>';
    // finish champion div since only one team
    } elseif ($variables['tour64_round'] == 6 and $key == 2) {
      $output .= '</div>';
    }
  }
  
  // finish column div
  $output .= '</div>';
  
  return $output;
}

function theme_tour64_textfield($variables) {
  
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('tour64-team-pick'));

  $output = '<div id="tour64-id-' . $element['#parents'][1] . '" title="' . $variables['element']['#value'] . '"><input' . drupal_attributes($element['#attributes']) . ' /></div>';
 
  return $output;
}
