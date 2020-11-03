getCustomerEmail = function() {
  return document.getElementById('customerEmail').value;
};

getCustomerPhone = function() {
  return document.getElementById('customerPhone').value;
};

getCustomerName = function() {
  return document.getElementById('customerName').value;
};

getNumberOfRentalDays = function() {
  return document.getElementById('numberOfRentalDays').value;
};

getNumberOfDigits = function(number) {
  return number.toString().length;
}

hasValidEmail = function() {
  var emailRegex = /^(([^<>()\[\]\\.,;:\s@']+(\.[^<>()\[\]\\.,;:\s@']+)*)|('.+'))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
  var email = getCustomerEmail();

  return emailRegex.test(email);
};

hasValidPhone = function() {
  var phoneRegex = /^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$/im;
  var phone = getCustomerPhone();

  return phoneRegex.test(phone);
};

hasValidName = function() {
  var name = getCustomerName();
  name = name.replace(/ +?/g, '');

  return name.length !== 0;
};

hasValidRentalDays = function() {
  var rentalDays = getNumberOfRentalDays();

  return getNumberOfDigits(rentalDays) !== 0;
};

setFormAction = function() {
  document.getElementById('carRentalForm').action = 'mailto:' + getCustomerEmail();
};

beforeSubmit = function() {
  var invalidEmailMessage = 'Your email is not valid. Please match the following format: example@gmail.com';
  var invalidPhoneMessage = 'Your phone number is not valid. Please be sure to only have 10 digits. If you choose to use dashes, make sure it is in this format: 123-456-7890';
  var invalidNameMessage = 'Your name cannot be blank.';
  var invalidRentalDaysMessage = 'You must specify the number of days you plan on renting the car.';

  if (!hasValidName()) {
    alert(invalidNameMessage);
    return;
  } else if (!hasValidEmail()) {
    alert(invalidEmailMessage);
    return;
  } else if (!hasValidPhone()) {
    alert(invalidPhoneMessage);
    return;
  } else if (!hasValidRentalDays()) {
    alert(invalidRentalDaysMessage);
    return;
  }

  setFormAction();

  document.getElementById('carRentalForm').submit();
};