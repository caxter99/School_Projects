getCustomerEmail = function() {
  return document.getElementById('customerEmail').value;
};

getCustomerPhone = function() {
  return document.getElementById('customerPhone').value;
};

hasValidEmail = function() {
  var emailRegex = /^(([^<>()\[\]\\.,;:\s@']+(\.[^<>()\[\]\\.,;:\s@']+)*)|('.+'))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
  var email = getCustomerEmail();

  return emailRegex.test(email);
};

hasValidPhone = function() {
  var phoneRegex = /^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$/;
  var phone = getCustomerPhone();

  return phoneRegex.test(phone);
};

setFormAction = function() {
  document.getElementById('carRentalForm').action = 'mailto:' + getCustomerEmail();
};

beforeSubmit = function() {
  if (!hasValidEmail()) {
    alert('Your email is not valid. Please match the following format: example@gmail.com');
    return;
  } else if (!hasValidPhone()) {
    alert('Your phone number is not valid. Please be sure to only have 10 digits.');
    return;
  }

  setFormAction();

  document.getElementById('carRentalForm').submit();
};