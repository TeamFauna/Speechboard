function init() {
    var pollingDiv = document.getElementById("container");
  document.body.appendChild(pollingDiv);

  startPolling(pollingDiv);
}
