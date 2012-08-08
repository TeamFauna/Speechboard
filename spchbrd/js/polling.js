function Poller(interval, callback) {
  function poll() {
    var req = new XMLHttpRequest();
    req.open("GET", "/speech", false);
    req.send();
    console.log(req);
    var json = JSON.parse(req.responseText);
    callback(json);
  }

  this.start = function() {
    setInterval(poll, interval);
  };

  this.poll = poll;
}

function startPolling(div) {
  function display(json) {
    div.innerHTML += json + '<br>';
  }

  var poller = new Poller(1000, display);
  poller.start();
}

