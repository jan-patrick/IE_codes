// setup MQTT client
client = new Paho.MQTT.Client("broker.shiftr.io", Number(443), "controlpanel");
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// some placeholders to keep track of time
var messagereceivedTime = 0;
var timeLeftPercentage = 0;
var clientName = "control";

var userFollowSize_Slider;
var userSize_Slider = 130;
var prevUserSize_Slider = userSize_Slider;
var arduinoPresenceDelay_Slider;
var arduinoDebounceDelay_Slider = 20;
var prevArduinoDebounceDelay_Slider = arduinoDebounceDelay_Slider;
var al = 0;

// communication valutes
var subscribedTopic = "/jan";

// user position value
var usersDetected = [];
var currentUser = 0;
var userMovementValueDifferenz = 40;

// sofaSeats
var sofaSeats_left = false;
var sofaSeats_right = false;
var currentJourney_state = -1;
var lastJourney_state = currentJourney_state - 1;


function setup() {
  client.connect({
    onSuccess: onConnect,
    userName: "connected-thing",
    password: "c784e41dd3da48d4",
    useSSL: true,
  });

  createCanvas(windowWidth, windowHeight);
  setupSliders();
  usersDetected[currentUser] = new UserDetected();
  textAlign( CENTER );
}

function draw() {
  checkForAlerts();
  //console.log(currentUser);
  //userSize_Slider = userFollowSize_Slider.value();
  //arduinoDebounceDelay_Slider = arduinoPresenceDelay_Slider.value();
  background(0, 0, 0);

  let color_active = color(0, 82, 33);
  let color_inActive = color(0, 0, 0);

  if (sofaSeats_left) {
    fill(color_active);
  } else {
    fill(color_inActive);
  }
  noStroke();
  rect(0, windowHeight / 5, windowWidth / 2, windowHeight / 5);

  if (sofaSeats_right) {
    fill(color_active);
  } else {
    fill(color_inActive);
  }
  noStroke();
  rect(windowWidth / 2, windowHeight / 5, windowWidth / 2, windowHeight / 5);

  fill(255);
  text( currentJourney_state, windowWidth / 2, windowHeight / 5 * 1.5);

  //if (prevUserSize_Slider != userSize_Slider) {
  //  generateMessage(clientName, "display", undefined, undefined, currentUser, userSize_Slider);
  //  prevUserSize_Slider = userSize_Slider;
  //}
  //if (prevArduinoDebounceDelay_Slider != arduinoDebounceDelay_Slider) {
  //  generateMessage(clientName, "arduino-entrance", undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, currentUser, arduinoDebounceDelay_Slider);
  //  prevArduinoDebounceDelay_Slider = arduinoDebounceDelay_Slider;
  //}

  //updateTime();
  //drawTimeRemaining()
}

function checkForAlerts() {
  if (lastJourney_state != currentJourney_state) {
    lastJourney_state = currentJourney_state;
    console.log("current journey: " + currentJourney_state)
    if (7 === currentJourney_state) {
      alert("‼️ LUGGAGE LIGHT ON ‼️");
    }
  }
}

function reloadAllJourneyComponents() {
  if (confirm("I'm reloading everything?")) {
    var obj = {
      "from": clientName,
      "to": "display",
      "debug": "reload"
    };
    sendMessage(compileMessage(obj));
    location.reload();
  }
}

function resetAndReloadAllJourneyComponents() {
  if (confirm("Abort and reload everything?")) {
    var obj = {
      "from": clientName,
      "to": "display",
      "debug": "abort&reload"
    };
    sendMessage(compileMessage(obj));
  }
}

function setupSliders() {
  button = createButton("reload");
  button.position(0, 0);
  button.size(windowWidth/2, windowHeight / 5);
  button.mousePressed(reloadAllJourneyComponents);

  button = createButton("abort and reload");
  button.position(windowWidth/2, );
  button.size(windowWidth/2, windowHeight / 5);
  button.mousePressed(resetAndReloadAllJourneyComponents);

  button = createButton("left");
  button.position(0, windowHeight / 5 * 2);
  button.size(windowWidth / 2, windowHeight / 5);
  button.mousePressed(standardMessageSofaSeatsLeft);

  button = createButton("right");
  button.position(windowWidth / 2, windowHeight / 5 * 2);
  button.size(windowWidth / 2, windowHeight / 5);
  button.mousePressed(standardMessageSofaSeatsRight);

  button = createButton('next');
  button.position(0, windowHeight / 5 * 3);
  button.size(windowWidth, windowHeight / 2);
  button.mousePressed(standardMessageJourneyNext);

  //userFollowSize_Slider = createSlider(0, 500, userSize_Slider);
  //userFollowSize_Slider.position(150, 0);
  //arduinoPresenceDelay_Slider = createSlider(5, 70, arduinoDebounceDelay_Slider);
  //arduinoPresenceDelay_Slider.position(170, 40);
  //button = createButton('reset user pos');
  //button.position(170, 10);
  //button.mousePressed(standardMessageUserPosReset);
  //button = createButton('new user');
  //button.position(170, 90);
  //button.mousePressed(standardMessageNewUser);
  //button = createButton('al');
  //button.position(260, 90);
  //button.mousePressed(standardMessageAmbientLight);
  //button = createButton('show online devices');
  //button.position(280, 10);
  //button.mousePressed(standardMessageShowDevOnline);
  //button = createButton('wave');
  //button.position(10, 30);
  //button.mousePressed(standardMessageWave);
  //button = createButton('highlight sofa');
  //button.position(10, 60);
  //button.mousePressed(standardMessageSofaHighlightStart);
  //button = createButton('stop sofa highlighting');
  //button.position(10, 90);
  //button.mousePressed(standardMessageSofaHighlightStop);
  //button = createButton('up');
  //button.position(55, 150);
  //button.mousePressed(standardMessageUserMoveUp);
  //button = createButton('left');
  //button.position(10, 200);
  //button.mousePressed(standardMessageUserMoveLeft);
  //button = createButton('right');
  //button.position(100, 200);
  //button.mousePressed(standardMessageUserMoveRight);
  //button = createButton('down');
  //button.position(50, 250);
  //button.mousePressed(standardMessageUserMoveDown);
}

function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("connected to mosquitto");
  client.subscribe(subscribedTopic);
}

function onMessageArrived(message) {
  //console.log(message.destinationName + " -> " + message.payloadString);
  try {
    inputs = JSON.parse(message.payloadString);

    if (typeof inputs === 'object' && inputs !== null) {
      if (typeof inputs.from === "string" && typeof inputs.to === "string") {
        if ("all" === inputs.to) {
          generateMessage(clientName, inputs.from, "online")
        }
        if (clientName === inputs.to) {
          if ("reload" === inputs.debug) {
            location.reload();
          } else {
            console.log(inputs.debug + " : " + inputs.from);
          }
        }
        if (typeof inputs.sofaSeats === 'object' && inputs.sofaSeats !== null) {
          if (typeof inputs.sofaSeats.left === "boolean" && inputs.sofaSeats.left !== null && typeof inputs.sofaSeats.right === "boolean" && inputs.sofaSeats.right !== null) {
            setSofaSeatsInUse(inputs.sofaSeats.left, inputs.sofaSeats.right);
          } else if (typeof inputs.sofaSeats.left === "boolean" && inputs.sofaSeats.left !== null) {
            setSofaSeatsInUse(inputs.sofaSeats.left, undefined);
          } else if (typeof inputs.sofaSeats.right === "boolean" && inputs.sofaSeats.right !== null) {
            setSofaSeatsInUse(undefined, inputs.sofaSeats.right);
          }
        }
        if (typeof inputs.journey === 'object' && inputs.journey !== null) {
          if (typeof inputs.journey.current === "number") {
            setJourneyState(inputs.journey.current);
          }
        }
      }
    } else {
      console.log("error while understanding data!")
    }

  } catch (e) {
    console.log("error parsing data!")
  }
}

function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
}

function setSofaSeatsInUse(left, right) {
  if (typeof left === "boolean" && null !== left) {
    sofaSeats_left = left;
  }
  if (typeof right === "boolean" && null !== right) {
    sofaSeats_right = right;
  }
}

function setJourneyState(state) {
  currentJourney_state = state;
}

function standardMessageWave() {
  generateMessage(clientName, "display", undefined, true);
}

function standardMessageAmbientLight() {
  if (0 == al) {
    al = 1;
  } else if (1 == al) {
    al = 2;
  } else if (2 == al) {
    al = -1;
  } else {
    al = 0;
  }
  generateMessage(clientName, "display", undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, al);
}

function standardMessageSofaHighlightStart() {
  generateMessage(clientName, "display", undefined, undefined, undefined, undefined, undefined, undefined, 0, -1, true);
}

function standardMessageSofaHighlightStop() {
  generateMessage(clientName, "display", undefined, undefined, undefined, undefined, undefined, undefined, 0, -1, false);
}

function standardMessageUserMoveUp() {
  usersDetected[currentUser].updateY(-userMovementValueDifferenz);
  generateMessage(clientName, "display", undefined, undefined, currentUser, undefined, usersDetected[currentUser].x, usersDetected[currentUser].y, undefined, undefined, undefined);
}

function standardMessageUserMoveDown() {
  usersDetected[currentUser].updateY(userMovementValueDifferenz);
  generateMessage(clientName, "display", undefined, undefined, currentUser, undefined, usersDetected[currentUser].x, usersDetected[currentUser].y, undefined, undefined, undefined);
}

function standardMessageUserMoveLeft() {
  usersDetected[currentUser].updateX(-userMovementValueDifferenz);
  generateMessage(clientName, "display", undefined, undefined, currentUser, undefined, usersDetected[currentUser].x, usersDetected[currentUser].y, undefined, undefined, undefined);
}

function standardMessageUserMoveRight() {
  usersDetected[currentUser].updateX(userMovementValueDifferenz);
  generateMessage(clientName, "display", undefined, undefined, currentUser, undefined, usersDetected[currentUser].x, usersDetected[currentUser].y, undefined, undefined, undefined);
}

function standardMessageUserPosReset() {
  usersDetected[currentUser].reset();
  generateMessage(clientName, "display", undefined, undefined, currentUser, undefined, usersDetected[currentUser].x, usersDetected[currentUser].y, undefined, undefined, undefined);
}

function standardMessageShowDevOnline() {
  generateMessage(clientName, "all");
}

function standardMessageNewUser() {
  currentUser++;
  usersDetected[currentUser] = new UserDetected();
  generateMessage(clientName, "display", undefined, undefined, currentUser, undefined, usersDetected[currentUser].x, usersDetected[currentUser].y, undefined, undefined, undefined);
}

function generateMessage(from, to, debug, wave, userId, userSize, posX, posY, sofaId, sofaPosition, highlightStatus, arduinoId, debounceDelay, als) {
  var obj = {
    "from": from,
    "to": to,
    "debug": debug,
    "wave": wave,
    "user": {
      "id": userId,
      "size": userSize,
      "posX": posX,
      "posY": posY
    },
    "sofa": {
      "id": sofaId,
      "sofaPosition": sofaPosition,
      "highlightStatus": highlightStatus,
    },
    "arduino": {
      "id": arduinoId,
      "debounceDelay": debounceDelay,
    },
    "al": als
  };
  sendMessage(compileMessage(obj));
}

function standardMessageJourneyNext() {
  if (1 === currentJourney_state && sofaSeats_left && sofaSeats_right || 1 === currentJourney_state && !sofaSeats_left && !sofaSeats_right ||
    2 === currentJourney_state && sofaSeats_left && sofaSeats_right || 2 === currentJourney_state && !sofaSeats_left && !sofaSeats_right ||
    3 === currentJourney_state && sofaSeats_left && sofaSeats_right || 3 === currentJourney_state && !sofaSeats_left && !sofaSeats_right) {
    alert("one seat must be in use (only)")
  } else {
    generateJourneyMessage(clientName, "display", undefined, true);
  }
}

function generateJourneyMessage(from, to, current, next) {
  var obj = {
    "from": from,
    "to": to,
    "journey": {
      "current": current,
      "next": next,
    }
  };
  sendMessage(compileMessage(obj));
}

function standardMessageSofaSeatsLeft() {
  sofaSeats_left = !sofaSeats_left;
  generateSofaSeatsMessage(clientName, "display", sofaSeats_left, sofaSeats_right);
}

function standardMessageSofaSeatsRight() {
  sofaSeats_right = !sofaSeats_right;
  generateSofaSeatsMessage(clientName, "display", sofaSeats_left, sofaSeats_right);
}

function generateSofaSeatsMessage(from, to, left, right) {
  var obj = {
    "from": from,
    "to": to,
    "sofaSeats": {
      "left": left,
      "right": right,
    }
  };
  sendMessage(compileMessage(obj));
}

function compileMessage(obj) {
  var json = JSON.stringify(obj);
  return json;
}

function sendMessage(message) {
  message = new Paho.MQTT.Message(message);
  message.destinationName = subscribedTopic;
  client.send(message);
}

function updateTime() {
  if (timeLeftPercentage > 0) {
    var timePassed = millis() - messagereceivedTime;
    var timeRemaining = duration - timePassed;
    timeLeftPercentage = map(timeRemaining, 0, duration, 0, 1);
  } else {
    strokeOff();
  }
}

function strokeOn() {
  strokeColor = 255;
  if (250 <= strokeColor) {
    strokeColor = 255;
  }
  running = true;
}

function setStrokeWidth() {
  strokeWidth = Math.round(map(continuity, 0, 100, 2, 4));
}

function strokeOff() {
  strokeColor = 0;
  if (5 >= strokeColor) {
    strokeColor = 0;
  }
  a = 0.0;
  intensity = 0;
  duration = 0;
  continuity = 0;
  running = false;
}

function drawTimeRemaining() {
  noStroke()
  fill(0);
  rect(0, height - 5, width * timeLeftPercentage, 5);
}

class UserDetected {
  constructor() {
    this.name = "UserDetected";
    this.x = windowWidth / 2;
    this.y = windowHeight / 2;
  }

  updateX(xChange) {
    this.x += xChange;
  }

  updateY(yChange) {
    this.y += yChange;
  }

  reset() {
    this.x = windowWidth / 2;
    this.y = windowHeight;
  }

}