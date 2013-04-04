<?php
/**
 * @return mixed
 */
function txn_admin_settings() {
  $form = array();

  $form[TXN_TAX_AMOUNT] = array(
    '#type' => 'select',
    '#title' => t('Tax percentage'),
    '#options' => range(0,100),
    '#default_value' => variable_get(TXN_TAX_AMOUNT, 10),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}




/**
*Page with requests
*
*/
function show_requests() {
$form = drupal_get_form('requests_form');
	$form = drupal_render($form);
	return $form;
    
}
/**
*Form with requests
*range - amount of page links at bottom
*size - amount/2 of requests per page
*/
function requests_form($form, &$form_state)
{
$size=5;
$range=5;
$arg1 = $form_state['build_info']['args'][0];
$query = db_select('userpoints_trnscts', 't');
	$query->fields('t', array('trid','name','amount','method','additional','approved','action','timestamp')); 
    $query->orderBy('t.approved');
	$query->orderBy('t.timestamp', 'DESC');
    $result = $query->range(($arg1-1)*$size,$size)->execute();
	$i=0;
	$form = array();
    while($nodes = $result->fetch()){
	if ($nodes->approved==1) $appr='Pending';
	if ($nodes->approved==2) $appr='Accepted';
	if ($nodes->approved==3) $appr='Denied';
	if ($nodes->action=='TXN_WITHDRAW') $act='Withdraw'; else $act='Income';
	$form['request'.$i] = array(
		'#type' => 'fieldset',
		'#title' => t('Request'),
		'#description' => $nodes->trid.'&nbsp&nbsp&nbsp'.$nodes->name.'&nbsp&nbsp&nbsp'.$act.'&nbsp&nbsp&nbsp'.$nodes->amount.'&nbsp&nbsp&nbsp'.$nodes->method.'&nbsp&nbsp&nbsp'.$nodes->additional.'&nbsp&nbsp&nbsp'.$appr,
		'#prefix' => '<div id="replace_row_div' . $i . '">', 
		'#suffix' => '</div>',
	);
	$form['request'.$i]['trid'.$i]=array(
		'#type' => 'hidden',
		'#value' => $nodes->trid,
	);
	$form['request'.$i]['name'.$i]=array(
		'#type' => 'hidden',
		'#value' => $nodes->name,
	);
	$form['request'.$i]['amount'.$i]=array(
		'#type' => 'hidden',
		'#value' => $nodes->amount,
	);
	$form['request'.$i]['method'.$i]=array(
		'#type' => 'hidden',
		'#value' => $nodes->method,
	);
	$form['request'.$i]['action'.$i]=array(
		'#type' => 'hidden',
		'#value' => $nodes->action,
	);
	if ($nodes->approved==1){
  $form['request'.$i]['submit'.$i] = array(
    '#name' => $i,
	'#type' => 'button',
    '#default_value' => t('Accept'),
	'#ajax' => array(
      'callback' => 'ajax_approve_function',
       'wrapper' => 'replace_row_div' . $i,
    ),
  );
  $form['request'.$i]['decline'.$i] = array(
    '#name' => $i,
    '#type' => 'button',
    '#default_value' => t('Decline'),
	'#ajax' => array(
      'callback' => 'ajax_disapprove_function',
       'wrapper' => 'replace_row_div' . $i,  
    ),
  );}
		$i++;
    }
	$form['pages'] = array(
		'#type' => 'fieldset',
		'#description' => '',
		);
		$num = db_query("SELECT count(trid) FROM {userpoints_trnscts}")->fetchField();
		$pages=floor(($num-1)/$size+1);
		if (($arg1-1)<abs($arg1-$pages))
			if (abs($arg1-$pages)<$range) $range+=$range-($arg1-$pages);
		else
			if (abs($arg1-1)<$range) $range+=$range-($arg1-1);
		for ($i=1; $i<=$pages;$i++)
		{
			if ($i==1 and (abs($i-$arg1))>$range) 
				{
				$form['pages']['#description'].='...';
				}
			if ($i==$pages and (abs($i-$arg1))>$range) 
				{
				$form['pages']['#description'].='...';
				}
			if (abs($i-$arg1)<$range)
				{
					if ($i==$pages)
					{
						if ($i==$arg1)
							{
							$form['pages']['#description'].=$i;
							}
						else
							{
							$form['pages']['#description'].='<a href="/admin/settings/txn/request/'.$i.'">'.$i.'</a>';
							}
					}
					else
					{
					if ($i==$arg1)
						{
						$form['pages']['#description'].=$i.', ';
						}
					else
						{
						$form['pages']['#description'].='<a href="/admin/settings/txn/request/'.$i.'">'.$i.'</a>, ';
						}
					}
				}
		}
	//	dpm($content);
  return $form;
}
/**
*Implements function for transactions approving (or not)
*
**/
function ajax_approve_function($form, &$form_state) {
$i=$form_state['triggering_element']['#name'];
$values=$form_state['values'];

			$stat_upd = db_update('userpoints_trnscts')
			->fields(array(
			'approved' => '2',
			))
			->condition('trid', $values['trid'.$i], '=')
			->execute();
 switch ($values['action'.$i]) 
	{
		case 'TXN_INCOME' :
		  txn_income($values['name'.$i], $values['amount'.$i]);
		break;
		case 'TXN_WITHDRAW' :
		  txn_withdraw($values['name'.$i], $values['amount'.$i]);

		break;
	}
	  $form['result'] = array(
    '#markup' => 'Accepted Act:'.$values['action'.$i].'name:'.$values['name'.$i].'amount'.$values['amount'.$i],
  );
  return $form;
	}
	/**
*Implements function for transactions disapproving (or not)
*
**/
function ajax_disapprove_function($form, &$form_state) {
$values=$form_state['values'];
$i=$form_state['triggering_element']['#name'];
			$stat_upd = db_update('userpoints_trnscts')
			->fields(array(
			'approved' => '3',
			))
			->condition('trid', $values['trid'.$i], '=')
			->execute();
  $form['result'] = array(
    '#markup' => 'Declined',
  );
  return $form;
}

/**
 * @return array
 */
function txn_admin_add() {
  $form = array();

  for ($i=1; $i<=2; $i++)
    $form['user'.$i] = array(
      '#type' => 'textfield',
      '#title' => t('User ').'#'.$i,
      '#size' => 30,
      '#maxlength' => 60,
      '#default_value' => '',
      '#autocomplete_path' => 'user/autocomplete',
      '#required' => $i==1,
    );

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#maxlength' => 60,
    '#default_value' => TXN_INCOME,
    '#required' => TRUE,
    '#options' => array(
      TXN_INCOME => t('Income'),
      TXN_WITHDRAW => t('Withdraw'),
      TXN_TRANSFER => t('Transfer'),
    ),
  );

  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount'),
    '#size' => 30,
    '#maxlength' => 5,
    '#default_value' => '',
    '#required' => $i==1,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Execute'),
  );

  return $form;
}


/**
* Form for balance income
* @return array
*/
function txn_in_form($form, &$form_state){
	$form=array();
	global $user;
	$form['amount']=array( 
		'#type' => 'textfield',
		'#title' => t('Ввод средств'),
		'#required' => true,
	);
	$form['name']=array( 
		'#type' => 'hidden',
		'#value' => $user->name,
	);
	$form['method'] = array(
		'#type' => 'radios',
		'#title' => t('Средство ввода'),
		'#options' => array('Средство 1' => t('Средство 1'), 'Средство 2' => t('Средство 2')),
		'#description' => t('Выбор метода ввода средств.'),
		'#required' => true,
	);
	$form['file']=array( 
		'#type' => 'file',
		'#title' => t('Фото чека'),
	);
 	$form['additional']=array( 
		'#type' => 'textfield',
		'#title' => t('Дополнительная информация'),
	);
	$form['submit'] = array( //кнопка сабмит
		'#type' => 'submit',
		'#value' => t('Submit'),
	);



	return $form;
}

/**
* Form for balance withdraw
* @return array
*/
function txn_out_form($form, &$form_state){
	$form=array();
	global $user;
	$form['amount']=array( //Сумма
		'#type' => 'textfield',
		'#title' => t('Ввод средств'),
		'#required' => true,
	);
	$form['name']=array( 
		'#type' => 'hidden',
		'#value' => $user->name,
	);
	$form['method'] = array(
		'#type' => 'radios',
		'#title' => t('Средство вывода'),
		'#options' => array('Средство 1' => t('Средство 1'), 'Средство 2' => t('Средство 2')),
		'#description' => t('Выбор метода вывода средств.'),
		'#required' => true,
	);
 
 	$form['additional']=array(
		'#type' => 'textfield',
		'#title' => t('Дополнительная информация'),
	);
	
	$form['submit'] = array( //кнопка сабмит
		'#type' => 'submit',
		'#value' => t('Submit'),
	);
	
	return $form;
}

/**
 * @return array
 */
function txn_admin_add_validate($form, &$form_state) {
  $values = &$form_state['values'];
  if ($values['type'] == TXN_TRANSFER) {
    if (empty($values['user2'])) {
      form_set_error('no second user', t('Select the user to transfer to'));
    }
    $values['user2'] = user_load_by_name($values['user2']);
    if (!is_object($values['user2'])) {
      form_set_error('user2', t('Specified user does not exist.') . ' #2');
    }
  }
  $values['user1'] = user_load_by_name($values['user1']);
  if (!is_object($values['user1'])) {
    form_set_error('user1', t('Specified user does not exist.') . ' #1');
  }
  if (!is_numeric($values['amount']) || ($values['amount'] <= 0)) {
    form_set_error('amount', t('Amount should ve greater than 0.'));
  }
  if ($values['type'] != TXN_INCOME) {
    if (!txn_suff($values['user1'], intval($values['amount']))) {
      form_set_error('amount2', t('Usef doesn\'t have sufficient amount of funds to complete transaction.'));
    }
  }
}

/**
 * @return array
 */
function txn_admin_add_submit($form, &$form_state) {
  $values = &$form_state['values'];
  switch ($values['type']) {
    case TXN_INCOME :
      txn_income($values['user1'], $values['amount']);
    break;
    case TXN_WITHDRAW :
      txn_withdraw($values['user1'], $values['amount']);
    break;
    case TXN_TRANSFER :
      txn_transfer($values['user1'], $values['user2'], $values['amount']);
    break;
  }
}

/**
* Writes values from form for income to table
*
*/
function txn_in_form_submit($form, &$form_state) {
  $values = &$form_state['values'];
  $values['action']='TXN_INCOME';
  $date = date_create();
  $values['timestamp']=date_timestamp_get($date);
  drupal_write_record('userpoints_trnscts',$values);
}

/**
 * validating entered data
 */
function txn_in_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  if (!is_numeric($values['amount']) || ($values['amount'] <= 0)) {
    form_set_error('amount', t('Amount should ve greater than 0.'));
  }
  /*if (isset($values['file'])){
  if (!file_validate_is_image($values['file'])) {
  form_set_error('amount', t('Amount should ve greater than 0.'));
  }}*/
}

/**
* Writes values from form for income to table
*
*/
function txn_out_form_submit($form, &$form_state) {
  $values = &$form_state['values'];
  $values['action']='TXN_WITHDRAW';
  $date = date_create();
  $values['timestamp']=date_timestamp_get($date);
  drupal_write_record('userpoints_trnscts',$values);
}
/**
 * @return array
 */
function txn_out_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  if (!is_numeric($values['amount']) || ($values['amount'] <= 0)) {
    form_set_error('amount', t('Amount should ve greater than 0.'));
  }
 }
