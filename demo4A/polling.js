function Poller() {

}

function startPolling(div) {
  var poller = new Poller();

  function update() {
    text = poller.poll();
    if (text.length > 0) {
      div.innerHTML += text + '<br>';
    }
  }

  setInterval(update, 1000);
}
