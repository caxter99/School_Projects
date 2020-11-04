<?php

	define('FULL_SIZE_CAR_COST_PER_DAY', 54.99);
	define('MEDIUM_SIZE_CAR_COST_PER_DAY', 45.99);
	define('SMALL_SIZE_CAR_COST_PER_DAY', 36.99);

	function getName() {
		if (isset($_POST['name'])) {
			return $_POST['name'];
		}

		return '';
	}

	function getEmail() {
		if (isset($_POST['email'])) {
			return $_POST['email'];
		}

		return '';
	}

	function getPhoneNumber() {
		if (isset($_POST['phoneNumber'])) {
			return $_POST['phoneNumber'];
		}

		return '';
	}

	function getNumberOfRentalDays() {
		if (isset($_POST['numberOfRentalDays'])) {
			return $_POST['numberOfRentalDays'];
		}

		return 0;
	}

	function getCarSize() {
		if (isset($_POST['carSize'])) {
			return $_POST['carSize'];
		}

		return '';
	}

	function getCarCostPerDay() {
		$carSize = getCarSize();
		if ($carSize == '') {
			return 0;
		}

		if ($carSize == 'full') {
			return FULL_SIZE_CAR_COST_PER_DAY;
		}
		else if ($carSize == 'medium') {
			return MEDIUM_SIZE_CAR_COST_PER_DAY;
		}
		return SMALL_SIZE_CAR_COST_PER_DAY;
	}

	function getTotalCostOfCarRental() {
		return getCarCostPerDay() * getNumberOfRentalDays();
	}
?>

<link rel="stylesheet" type="text/css" href="style.css" />
<table class="blue-alternating center">
  <thead>
    <tr>
      <th class="blue-top-row white" colspan="2">Invoice</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th class="blue-alternating">Customer Name</th>
      <td class="blue-alternating"><?php echo getName(); ?></td>
    </tr>
    <tr>
      <th class="blue-alternating">Customer Email</th>
      <td class="blue-alternating"><?php echo getEmail(); ?></td>
    </tr>
    <tr>
      <th class="blue-alternating">Customer Phone</th>
      <td class="blue-alternating"><?php echo getPhoneNumber(); ?></td>
    </tr>
    <tr>
      <th class="blue-alternating">Rental Number of Days</th>
      <td class="blue-alternating"><?php echo getNumberOfRentalDays(); ?></td>
    </tr>
    <tr>
      <th class="blue-alternating">Cost of Car Rental Per Day</th>
      <td class="blue-alternating"><?php echo '$' . getCarCostPerDay(); ?></td>
    </tr>
    <tr>
      <th class="blue-alternating">Total Cost of Car Rental</th>
      <td class="blue-alternating"><?php echo '$' . getTotalCostOfCarRental(); ?></td>
    </tr>
  </tbody>
</table>