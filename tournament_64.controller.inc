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
