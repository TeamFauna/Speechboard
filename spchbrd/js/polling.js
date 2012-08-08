function Poller(interval, callback) {
  var id_ = -1;

  function poll() {
    var req = new XMLHttpRequest();
    var id = id_ < 0 ? 0 : id_;
    req.open("GET", "/speech?id=" + id, false);
    req.send();

    var json = JSON.parse(req.responseText);
    if (!json || json.length == 0) {
      return;
    }

    for (var i = 0; i < json.length; i++) {
      id = json[i].id;
      if (id > id_) {
        callback(json[i]);
        id_ = id;
      }
    }
  }

  this.start = function() {
    poll();
    setInterval(poll, interval);
  };
}

var emailToImg = {
  'deadhead.russell@gmail.com': 'russell',
  'zetalmac@gmail.com': 'noah',
  'Noah': 'noah',
  'willhughes01@gmail.com': 'will',
  'munnand@gmail.com': 'munn'
};

function CreateAvatar(speaker) {
  var path = 'js/' + emailToImg[speaker] + '.jpg';
  var img = document.createElement('Img');
  img.src = path;

  img.style.width = '64px';

  return img;
}

function CreateTextBox(speaker, text) {
  var boxDiv = document.createElement('Div');

  var speakerImg = CreateAvatar(speaker);
  boxDiv.appendChild(speakerImg);

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
    console.log(json);
    var speaker = json.speaker;
    var text = json.text;
    div.appendChild(CreateTextBox(speaker, text));
  }

  var poller = new Poller(1000, display);
  poller.start();
}

