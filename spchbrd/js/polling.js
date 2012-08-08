function Poller(interval, callback) {
  this.id = 0;

  function poll() {
    var req = new XMLHttpRequest();
    req.open("GET", "/speech?id=" + this.id, false);
    req.send();
    console.log(req);
    var json = JSON.parse(req.responseText);
    if (json && json.length) {
      this.id = json[json.length].id;
      callback(json);
    }
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

