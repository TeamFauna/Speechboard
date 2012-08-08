function startInput(inputDiv) {
  var nameDiv = document.createElement('Div');

  var nameLabel = document.createElement('H3');
  nameLabel.appendChild(document.createTextNode('Your Name:'));
  nameDiv.appendChild(nameLabel);

  var nameInput = document.createElement('Input');
  nameInput.setAttribute('type', 'text');
  nameDiv.appendChild(nameInput);

  inputDiv.appendChild(nameDiv);

  var textInput = document.createElement('input');
  textInput.setAttribute('x-webkit-speech', '');
  textInput.addEventListener('webkitSpeechChange', function() {}, false);
  inputDiv.appendChild(textInput);
}

