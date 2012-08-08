function Poller(interval, callback) {
  function poll() {
    json = $.getJson('/speech');
    if (json.length > 0) {
      callback(json);
    }
  }

  this.start = function() {
    setInterval(poll, interval);
  }

  this.poll = poll;
}

function startPolling(div) {
  function display(text) {
    div.innerHTML += text + '<br>';
  }

  var poller = new Poller(1000, display);
  poller.start();
}

