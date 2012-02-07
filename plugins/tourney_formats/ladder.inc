<?php

/**
 * @file
 * Default plugin for a default style.
 */

/**
* Ladder Tournament
*/
$plugin = array(
  'name' => t('Ladder Tournament'),
  'machine name' => 'ladder',
  'description' => t('This is the description of the tournament'),
  'weight' => 4,
  'total games' => 5,
  'builder controller' => 'Ladder', 
  'completed controller' => 'LadderMatchComplete',
);

// Define any classes below to extend default functionality in the controllers.
// The default implementation works for this plugin.