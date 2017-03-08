<?php

/**
 * @file
 * Tournament 64 Views
 *
 */

/**
 * Implements hook_views_default_views().
 */
function tournament_64_views_default_views() {

$view = new view();
$view->name = 'tournament_64_leagues';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'tour64_leagues';
$view->human_name = 'Tournament 64 Leagues';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Tournament 64 Leagues';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view tour64_leagues entities';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '100';
$handler->display->display_options['style_plugin'] = 'table';
/* Field: Tournament 64 League: URL */
$handler->display->display_options['fields']['url']['id'] = 'url';
$handler->display->display_options['fields']['url']['table'] = 'views_entity_tour64_leagues';
$handler->display->display_options['fields']['url']['field'] = 'url';
$handler->display->display_options['fields']['url']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['url']['alter']['text'] = 'View';
$handler->display->display_options['fields']['url']['link_to_entity'] = 0;
/* Field: Tournament 64 League: Description */
$handler->display->display_options['fields']['description']['id'] = 'description';
$handler->display->display_options['fields']['description']['table'] = 'tour64_leagues';
$handler->display->display_options['fields']['description']['field'] = 'description';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'tournament-64';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Leagues';
$handler->display->display_options['menu']['description'] = 'Leagues';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$handler->display->display_options['tab_options']['type'] = 'tab';
$handler->display->display_options['tab_options']['title'] = 'Leagues';
$handler->display->display_options['tab_options']['description'] = 'Leagues';
$handler->display->display_options['tab_options']['weight'] = '0';


  $views[$view->name] = $view;





  
$view = new view();
$view->name = 'tournament_64_entries';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'tour64_entries';
$view->human_name = 'Tournament 64 Entries';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Entries';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '100';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'position' => 'position',
  'league_id' => 'league_id',
  'url' => 'url',
  'nickname' => 'nickname',
  'points' => 'points',
  'total_points_possible' => 'total_points_possible',
  'paid' => 'paid',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'position' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'league_id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'url' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'nickname' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'points' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'total_points_possible' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'paid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Field: Tournament 64 Entry: Position */
$handler->display->display_options['fields']['position']['id'] = 'position';
$handler->display->display_options['fields']['position']['table'] = 'tour64_entries';
$handler->display->display_options['fields']['position']['field'] = 'position';
$handler->display->display_options['fields']['position']['separator'] = '';
/* Field: Tournament 64 Entry: League ID */
$handler->display->display_options['fields']['league_id']['id'] = 'league_id';
$handler->display->display_options['fields']['league_id']['table'] = 'tour64_entries';
$handler->display->display_options['fields']['league_id']['field'] = 'league_id';
$handler->display->display_options['fields']['league_id']['exclude'] = TRUE;
$handler->display->display_options['fields']['league_id']['separator'] = '';
/* Field: Tournament 64 Entry: URL */
$handler->display->display_options['fields']['url']['id'] = 'url';
$handler->display->display_options['fields']['url']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['url']['field'] = 'url';
$handler->display->display_options['fields']['url']['exclude'] = TRUE;
$handler->display->display_options['fields']['url']['alter']['text'] = '[nickname]';
$handler->display->display_options['fields']['url']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: Nickname */
$handler->display->display_options['fields']['nickname']['id'] = 'nickname';
$handler->display->display_options['fields']['nickname']['table'] = 'tour64_entries';
$handler->display->display_options['fields']['nickname']['field'] = 'nickname';
$handler->display->display_options['fields']['nickname']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nickname']['alter']['path'] = '[url]/bracket';
/* Field: Tournament 64 Entry: Points */
$handler->display->display_options['fields']['points']['id'] = 'points';
$handler->display->display_options['fields']['points']['table'] = 'tour64_entries';
$handler->display->display_options['fields']['points']['field'] = 'points';
$handler->display->display_options['fields']['points']['separator'] = '';
/* Field: Tournament 64 Entry: Total Points Possible */
$handler->display->display_options['fields']['total_points_possible']['id'] = 'total_points_possible';
$handler->display->display_options['fields']['total_points_possible']['table'] = 'tour64_entries';
$handler->display->display_options['fields']['total_points_possible']['field'] = 'total_points_possible';
$handler->display->display_options['fields']['total_points_possible']['separator'] = '';
/* Field: Tournament 64 Entry: Paid */
$handler->display->display_options['fields']['paid']['id'] = 'paid';
$handler->display->display_options['fields']['paid']['table'] = 'tour64_entries';
$handler->display->display_options['fields']['paid']['field'] = 'paid';
$handler->display->display_options['fields']['paid']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['paid']['alter']['path'] = '[url]/paid?destination=tournament-64/[league_id]/entries';
/* Field: Tournament 64 Entry: First Place CSS */
$handler->display->display_options['fields']['prediction_first_css']['id'] = 'prediction_first_css';
$handler->display->display_options['fields']['prediction_first_css']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_first_css']['field'] = 'prediction_first_css';
$handler->display->display_options['fields']['prediction_first_css']['exclude'] = TRUE;
$handler->display->display_options['fields']['prediction_first_css']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: Second Place CSS */
$handler->display->display_options['fields']['prediction_second_css']['id'] = 'prediction_second_css';
$handler->display->display_options['fields']['prediction_second_css']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_second_css']['field'] = 'prediction_second_css';
$handler->display->display_options['fields']['prediction_second_css']['exclude'] = TRUE;
$handler->display->display_options['fields']['prediction_second_css']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: Third Place CSS */
$handler->display->display_options['fields']['prediction_third_css']['id'] = 'prediction_third_css';
$handler->display->display_options['fields']['prediction_third_css']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_third_css']['field'] = 'prediction_third_css';
$handler->display->display_options['fields']['prediction_third_css']['exclude'] = TRUE;
$handler->display->display_options['fields']['prediction_third_css']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: Fourth Place CSS */
$handler->display->display_options['fields']['prediction_fourth_css']['id'] = 'prediction_fourth_css';
$handler->display->display_options['fields']['prediction_fourth_css']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_fourth_css']['field'] = 'prediction_fourth_css';
$handler->display->display_options['fields']['prediction_fourth_css']['exclude'] = TRUE;
$handler->display->display_options['fields']['prediction_fourth_css']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: First Place Name */
$handler->display->display_options['fields']['prediction_first_name']['id'] = 'prediction_first_name';
$handler->display->display_options['fields']['prediction_first_name']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_first_name']['field'] = 'prediction_first_name';
$handler->display->display_options['fields']['prediction_first_name']['element_class'] = '[prediction_first_css]';
$handler->display->display_options['fields']['prediction_first_name']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: Second Place Name */
$handler->display->display_options['fields']['prediction_second_name']['id'] = 'prediction_second_name';
$handler->display->display_options['fields']['prediction_second_name']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_second_name']['field'] = 'prediction_second_name';
$handler->display->display_options['fields']['prediction_second_name']['element_class'] = '[prediction_second_css]';
$handler->display->display_options['fields']['prediction_second_name']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: Tie Third Place Name */
$handler->display->display_options['fields']['prediction_third_name']['id'] = 'prediction_third_name';
$handler->display->display_options['fields']['prediction_third_name']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_third_name']['field'] = 'prediction_third_name';
$handler->display->display_options['fields']['prediction_third_name']['element_class'] = '[prediction_third_css]';
$handler->display->display_options['fields']['prediction_third_name']['link_to_entity'] = 0;
/* Field: Tournament 64 Entry: Tie Third Place Name */
$handler->display->display_options['fields']['prediction_fourth_name']['id'] = 'prediction_fourth_name';
$handler->display->display_options['fields']['prediction_fourth_name']['table'] = 'views_entity_tour64_entries';
$handler->display->display_options['fields']['prediction_fourth_name']['field'] = 'prediction_fourth_name';
$handler->display->display_options['fields']['prediction_fourth_name']['element_class'] = '[prediction_fourth_css]';
$handler->display->display_options['fields']['prediction_fourth_name']['link_to_entity'] = 0;
/* Sort criterion: Tournament 64 Entry: Position */
$handler->display->display_options['sorts']['position']['id'] = 'position';
$handler->display->display_options['sorts']['position']['table'] = 'tour64_entries';
$handler->display->display_options['sorts']['position']['field'] = 'position';
/* Sort criterion: Tournament 64 Entry: Total Points Possible */
$handler->display->display_options['sorts']['total_points_possible']['id'] = 'total_points_possible';
$handler->display->display_options['sorts']['total_points_possible']['table'] = 'tour64_entries';
$handler->display->display_options['sorts']['total_points_possible']['field'] = 'total_points_possible';
$handler->display->display_options['sorts']['total_points_possible']['order'] = 'DESC';
/* Sort criterion: Tournament 64 Entry: Nickname */
$handler->display->display_options['sorts']['nickname']['id'] = 'nickname';
$handler->display->display_options['sorts']['nickname']['table'] = 'tour64_entries';
$handler->display->display_options['sorts']['nickname']['field'] = 'nickname';
/* Contextual filter: Tournament 64 Entry: League ID */
$handler->display->display_options['arguments']['league_id']['id'] = 'league_id';
$handler->display->display_options['arguments']['league_id']['table'] = 'tour64_entries';
$handler->display->display_options['arguments']['league_id']['field'] = 'league_id';
$handler->display->display_options['arguments']['league_id']['default_action'] = 'access denied';
$handler->display->display_options['arguments']['league_id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['league_id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['league_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['league_id']['summary_options']['items_per_page'] = '25';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'tournament-64/%/entries';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Entries';
$handler->display->display_options['menu']['description'] = 'Entries';
$handler->display->display_options['menu']['weight'] = '6';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;


  $views[$view->name] = $view;
  
  return $views;
}
