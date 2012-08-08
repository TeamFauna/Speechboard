function Poller(interval, callback) {
  function poll() {
    var req = new XMLHttpRequest();
    req.open("GET", "/speech", false);
    req.send();
    console.log(req);
    callback(req.responseText);
  }

  this.start = function() {
    setInterval(poll, interval);
  };

  this.poll = poll;
}

function startPolling(div) {
  function display(text) {
    div.innerHTML += text + '<br>';
  }

  var poller = new Poller(1000, display);
  poller.start();
}

