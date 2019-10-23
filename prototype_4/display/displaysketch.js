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

var userFollowSize_Slider;
var pg;

//chair related values
var chairs = [];
var chairSize = 80;
var chairStandardColor = 100;


function setup() {
  client.connect({
    onSuccess: onConnect,
    userName: "connected-thing",
    password: "c784e41dd3da48d4",
    useSSL: true,
  });

  createCanvas(windowWidth, windowHeight);
  pg = createGraphics(500, 50);
  setupSliders();
  setupChairs();
}

function draw() {
  const userFollowSize_value = userFollowSize_Slider.value();
  background(0, 0, 0);

  for (let i = 0; i < chairs.length; i++) {
    //chairs[i].update();
    chairs[i].draw();
  }

  fill(0, 12);
  rect(0, 0, width, height);
  fill(255);
  noStroke();
  ellipse(mouseX, mouseY, userFollowSize_value, userFollowSize_value);

  pg.background(51);
  pg.noFill();
  pg.stroke(255);
  pg.ellipse(mouseX - 150, mouseY - 75, userFollowSize_value, userFollowSize_value);

  //Draw the offscreen buffer to the screen with image()
  image(pg, 150, 75);


  
  //updateTime();
  //drawTimeRemaining()
}

function setupSliders() {
  userFollowSize_Slider = createSlider(0, 255, 100);
  userFollowSize_Slider.position(10, 0);


  button = createButton('wave');
  button.position(10, 20);
  button.mousePressed(luggageNotification);
}

function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("connected to mosquitto");
  client.subscribe("/jan");
}

function luggageNotification() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("luggage incoming");
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

function drawTimeRemaining() {
  noStroke()
  fill(0);
  rect(0, height - 5, width * timeLeftPercentage, 5);
}

// Chairs

function setupChairs() {
  chairs[chairs.length] = new Chair(20, 50, chairSize, chairSize, chairStandardColor);
}


class Chair {
  constructor(x, y, xSize, ySize, fillColor) {
    this.x = x;
    this.y = y;
    this.xSize = xSize;
    this.ySize = ySize;
    this.fillColor = fillColor;
  }

  // Custom method for updating the variables
  update() {
    this.x = this.x;
    if (this.x >= this.unit || this.x <= 0) {
      this.x = this.x + 1;
      this.y = this.y + 1;
    }
    if (this.y >= this.unit || this.y <= 0) {
      this.y = this.y + 1;
    }
  }

  // Custom method for drawing the object
  draw() {
    fill(this.fillColor);
    rect(this.x, this.y, this.xSize, this.ySize);
  }
}