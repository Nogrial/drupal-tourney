<?php

/**
 * Gets a padded/trimmed list to throw into a table
 * 
 * @param $ids
 *   List of game entity ids.
 * @param $total
 *   Total number of games in the match.
 * @return
 *   List of game entities, filled with null elements if less than total, or trimmed if more.
 */
function tourney_load_games($ids, $total) {
  $games = array();
  $game_list = entity_load('tourney_game', $ids);
  foreach ( $game_list as $game ) $games[] = $game;
  while ( count($games) < $total ) $games[] = null;
  while ( count($games) > $total ) array_pop($games);
  return $games;
}

/**
 * Renders a match to an HTML table
 * 
 * @param $games
 *   List of game entities.
 * @return
 *   Rendered HTML table.
 */
function tourney_games_to_table($games) {
  $header = array('Team Name');
  $rows   = array();
  foreach ( $games as $gn => $game ) {
    $header[] = "Game " . ( $gn + 1 ); //. ( $game ? " | " . $game->id : "" );
    if ( $game == null ) foreach ( $rows as $k => $v ) $rows[$k][] = '-';
    else foreach ( $game->contestants as $id => $contestant ) {
      if ( !isset($rows[$id]) ) $rows[$id] = array($contestant);
      if ( $game->winner ) $rows[$id][] = $game->winner == $id ? 'W' : 'L';
      else $rows[$id][] = drupal_render(drupal_get_form('tourney_game_win_form', 
        array('match' => $game->match->id, 'game' => $game->id, 'contestant' => $id, 'name' => $contestant)));
    }
  }
  $header[] = "Results";
  foreach ( $rows as $k => $v ) {
    $points = array_key_exists('W', $tally = array_count_values($v)) ? $tally['W'] : 0;
    $rows[$k][] = ( $points > count($games) / 2 ) ? 'Winner' : '-';
  }
  return theme('table', array(
    'attributes' => array('id' => 'game-list'),
    'header' => $header,
    'rows' => $rows,
  ));
}

/**
 * Renders an HTML table of a match
 * 
 * @param $vars
 *   Theme variables, needs only a match.
 * @return
 *   Rendered HTML table.
 */
function theme_tourney_render_match($vars) {
  $match = $vars['match'];
  $games = tourney_load_games($match->games_played, $match->games);
  $table = tourney_games_to_table($games);
  return $table;
}