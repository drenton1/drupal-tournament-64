<?php

/**
 * @file
 * Tournament 64 classes
 *
 */
class Tour64LeaguesEntityController extends EntityAPIController {

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $entity->changed = REQUEST_TIME;

    if (empty($entity->{$this->idKey}) || !empty($entity->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($entity->created)) {
        $entity->created = REQUEST_TIME;
      }
      if (empty($entity->uid)) {
        global $user;
        $entity->uid = $user->uid;
      }
    }

    // convert date to UTC
    $timezone = date_default_timezone();
    $datetime = new dateObject($entity->close_time, $timezone);
    $timezone = 'UTC';
    $datetime->setTimezone(new DateTimeZone($timezone));
    $entity->close_time = $datetime->format('Y-m-d H:i:s');
    
    return parent::save($entity, $transaction);
  }
  
}

class Tour64EntriesEntityController extends EntityAPIController {

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $entity->changed = REQUEST_TIME;

    if (empty($entity->{$this->idKey}) || !empty($entity->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($entity->created)) {
        $entity->created = REQUEST_TIME;
      }
      if (empty($entity->uid)) {
        global $user;
        $entity->uid = $user->uid;
      }
      if (empty($entity->paid)) {
        $entity->paid = 'N';
      }
    }
    
    // fill in predictions if we have all our picks
    if (!empty($entity->winners[57]) and 
        !empty($entity->winners[58]) and 
        !empty($entity->winners[59]) and 
        !empty($entity->winners[60]) and 
        !empty($entity->winners[61]) and 
        !empty($entity->winners[62]) and 
        !empty($entity->winners[63])) {
    
      $final_two = array($entity->winners[61], $entity->winners[62]);
      $final_four = array($entity->winners[57], $entity->winners[58], $entity->winners[59], $entity->winners[60]);
    
      $second_place = array_values(array_diff($final_two, array($entity->winners[63])));
      $tie_third = array_values(array_diff($final_four, $final_two));
      
      $entity->prediction_first = $entity->winners[63];
      $entity->prediction_second = $second_place[0];
      $entity->prediction_third = $tie_third[0];
      $entity->prediction_fourth = $tie_third[1];
      
    } else {
      $entity->prediction_first = NULL;
      $entity->prediction_second = NULL;
      $entity->prediction_third = NULL;
      $entity->prediction_fourth = NULL;
    }

    return parent::save($entity, $transaction);
  }
  
}

class Tour64Leagues extends Entity {
  protected function defaultLabel() {
    return $this->description;
  }

  protected function defaultUri() {
    return array('path' => 'tournament-64/' . $this->identifier());
  }
}

class Tour64Entries extends Entity {
  protected function defaultLabel() {
    return $this->nickname;
  }

  protected function defaultUri() {
    return array('path' => 'tournament-64/' . $this->league_id . '/entries/' . $this->identifier());
  }
}
