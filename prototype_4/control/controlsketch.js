// setup MQTT client
client = new Paho.MQTT.Client("broker.shiftr.io", Number(443), "controlpanel");
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// some placeholders to keep track of time
var messagereceivedTime = 0;
var timeLeftPercentage = 0;

var userFollowSize_Slider;
var userSize_Slider = 100;
var prevUserSize_Slider = userSize_Slider;

// communication valutes
var subscribedTopic = "/jan";


function setup() {
  client.connect({
    onSuccess: onConnect,
    userName: "connected-thing",
    password: "c784e41dd3da48d4",
    useSSL: true,
  });

  createCanvas(windowWidth, windowHeight);
  setupSliders();
}

function draw() {
  userSize_Slider = userFollowSize_Slider.value();
  background(0, 0, 0);

  if (prevUserSize_Slider != userSize_Slider) {
    generateMessage(undefined, 0, userSize_Slider);
    prevUserSize_Slider = userSize_Slider;
  }

  //updateTime();
  //drawTimeRemaining()
}

function setupSliders() {
  userFollowSize_Slider = createSlider(0, 255, userSize_Slider);
  userFollowSize_Slider.position(10, 0);


  button = createButton('wave');
  button.position(10, 30);
  button.mousePressed(standardMessageWave);

  button = createButton('highlight sofa');
  button.position(10, 60);
  button.mousePressed(standardMessageSofaHighlightStart);

  button = createButton('stop sofa highlighting');
  button.position(10, 90);
  button.mousePressed(standardMessageSofaHighlightStop);
}

function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("connected to mosquitto");
  client.subscribe(subscribedTopic);
}

function onMessageArrived(message) {
  console.log(message.destinationName + " -> " + message.payloadString);
}

function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
}

function standardMessageWave() {
  generateMessage(true);
}

function standardMessageSofaHighlightStart() {
  generateMessage(undefined, undefined, undefined, 0, 1, true);
}

function standardMessageSofaHighlightStop() {
  generateMessage(undefined, undefined, undefined, 0, 1, false);
}

function generateMessage(wave, userId, userSize, sofaId, sofaPosition, highlightStatus) {
  var obj = {
    "wave": wave,
    "user": {
      "id": userId,
      "size": userSize,
    },
    "sofa": {
      "id": sofaId,
      "sofaPosition": sofaPosition,
      "highlightStatus": highlightStatus,
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