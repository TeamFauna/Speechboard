function init() {
  var inputDiv = document.createElement('Div');
  document.body.appendChild(inputDiv);

  var pollingDiv = document.createElement('Div');
  document.body.appendChild(pollingDiv);

  startInput(inputDiv);
  startPolling(pollingDiv);
}
