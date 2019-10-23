//setup MQTT client
client = new Paho.MQTT.Client("broker.shiftr.io", Number(443), "controlpanel");
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

//some placeholders for the data received trough MQTT
var intensity = 0;
var duration = 0;
var continuity = 0;

//some placeholders to keep track of time
var messagereceivedTime = 0;
var timeLeftPercentage = 0;

let pg;

function setup() {
  createCanvas(windowWidth, windowHeight);
  pg = createGraphics(400, 250);
}

function draw() {
  fill(0, 12);
  rect(0, 0, width, height);
  fill(255);
  noStroke();
  ellipse(mouseX, mouseY, 60, 60);

  pg.background(51);
  pg.noFill();
  pg.stroke(255);
  pg.ellipse(mouseX - 150, mouseY - 75, 60, 60);

  //Draw the offscreen buffer to the screen with image()
  image(pg, 150, 75);



  //updateTime();
  //drawTimeRemaining()
}

function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("connected to mosquitto");
  client.subscribe("/j");
}

function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
}

function onMessageArrived(message) {
  console.log(message.destinationName + " -> " + message.payloadString);

  var payload = message.payloadString;

  try {
    valuesArray = payload.split(' ');

    duration = Number(valuesArray[0]);
    if (10000 <= duration) {
      duration = 10000;
    } else if (0 >= duration) {
      duration = 0;
    }
    intensity = Number(valuesArray[1]);
    if (100 <= intensity) {
      intensity = 100;
    } else if (0 >= intensity) {
      intensity = 0;
    }
    continuity = Number(valuesArray[2]);
    if (100 <= continuity) {
      continuity = 100;
    } else if (0 >= continuity) {
      continuity = 0;
    }
    if (0 < duration) {
      messagereceivedTime = millis();
      timeLeftPercentage = 1;
      strokeOn();
      setStrokeWidth();
      a = 0.0;
    }
  } catch (e) {
    console.log("error parsing data!")
  }

}

function sendMessage(topic, message) {
  message = new Paho.MQTT.Message(message);
  message.destinationName = topic;
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

function remapContinuity() {
  strokeColor = map(continuity, 0, 100, 50, 255);
  r = random(strokeColor);
  g = random(strokeColor);
  b = random(strokeColor);
}

function mapIntDur() {
  let intdur = intensity + duration;
  intdur = map(intdur, 0, 10100, 0, 20)
  return intdur;
}

function drawTimeRemaining() {
  noStroke()
  fill(0);
  rect(0, height - 5, width * timeLeftPercentage, 5);
}