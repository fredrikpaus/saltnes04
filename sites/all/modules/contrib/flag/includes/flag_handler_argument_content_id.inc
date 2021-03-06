<?php
// $Id: flag_handler_argument_content_id.inc,v 1.4 2010/12/22 23:32:26 mooffie Exp $

/**
 * @file
 * Contains the content ID argument handler.
 */

/**
 * Handler to accept an argument of the content ID of any object.
 *
 * @ingroup views
 */
class flag_handler_argument_content_id extends views_handler_argument_numeric {

  /**
   * Returns the flag object associated with our argument.
   *
   * An argument is in some relationship. This function reaches out for this
   * relationship and reads its 'flag' option, which holds the flag name.
   */
  function get_flag() {
    return $this->view->relationship[$this->options['relationship']]->get_flag();
  }

  /**
   * Override the behavior of title(). Get the title of the appropriate objects.
   */
  function title_query() {
    if (!($flag = $this->get_flag())) {
      return array(); // Error message is printed by get_flag().
    }
    $views_info = $flag->get_views_info();

    $titles = array();
    $placeholders = implode(', ', array_fill(0, sizeof($this->value), '%d'));

    $result = db_select($views_info['views table'], 'o')
      ->fields('o', array($views_info['title field']))
      ->condition('o.' . $views_info['join field'], $this->value, 'IN')
      ->execute();
    foreach ($result as $title) {
      $titles[] = check_plain($title->$views_info['title field']);
    }
    return $titles;
  }
}
