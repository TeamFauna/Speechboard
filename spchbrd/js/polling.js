function Poller(interval, callback) {
  function poll() {
    $.get('/speech', function(data) {
      if (data.length > 0) {
        callback(data);
      }
    });
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

