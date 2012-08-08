function Poller(interval, callback) {
  this.id = -1;

  function poll() {
    var req = new XMLHttpRequest();
    var id = this.id < 0 ? 0 : this.id;
    req.open("GET", "/speech?id=" + id, false);
    req.send();
    console.log(req);

    var json = JSON.parse(req.responseText);
    if (!json || json.length == 0) {
      return;
    }

    for (var i = 0; i < json.length; i++) {
      var id = json[i].id;
      if (id > this.id) {
        callback(json[i]);
        this.id = id;
      }
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

