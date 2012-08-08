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
      id = json[i].id;
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

var emailToImg = {
  'deadhead.russell@gmail.com': 'russell',
  'zetalmac@gmail.com': 'noah',
  'willhughes01@gmail.com': 'will',
  'munnand@gmail.com': 'munn'
};

function GetPicture(speaker) {

}

function CreateTextBox(speaker, text) {
  var boxDiv = document.createElement('Div');

  var speakerSpan = document.createElement('Span');
  speakerSpan.style.fontWeight = 'bold';
  speakerSpan.appendChild(document.createTextNode(speaker + ':'));
  boxDiv.appendChild(speakerSpan);

  var textSpan = document.createElement('Span');
  textSpan.appendChild(document.createTextNode(text));
  boxDiv.appendChild(textSpan);

  return boxDiv;
}

function startPolling(div) {
  function display(json) {
    var speaker = json.speaker;
    var text = json.text;
    div.appendChild(CreateTextBox(speaker, text));
  }

  var poller = new Poller(1000, display);
  poller.start();
}

