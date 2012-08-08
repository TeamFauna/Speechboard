function init() {
  var pollingDiv = document.createElement('Div');
  document.body.appendChild(pollingDiv);

  var inputDiv = document.createElement('Div');
  document.body.appendChild(inputDiv);

  startInput(inputDiv);
  startPolling(pollingDiv);
}
