// setup MQTT client
client = new Paho.MQTT.Client("broker.shiftr.io", Number(443), "controlpanel");
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// some placeholders to keep track of time
var messagereceivedTime = 0;
var timeLeftPercentage = 0;

var userFollowSize_Slider;
var pg;

var users = [];

// chair related values
var chairs = [];
var chairSize = 80;
var chairStandardColor = 100;

// wave related values
var waves = [];
var waveState = 0;
var waveState_idle = 0;
var waveState_Washing = 1;
var waveState_Finished = 2;

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
  setupChairs();
  setupWave();
  users[users.length] = new User();

}

function draw() {
  background(0, 0, 0);

  for (let i = 0; i < chairs.length; i++) {
    //chairs[i].update();
    chairs[i].draw();
  }
  for (let i = 0; i < waves.length; i++) {
    switch (waveState) {
      case waveState_Finished:
        waves[i].reset();
        waveState = waveState_idle;
        break;
      case waveState_Washing:
        waves[i].update();
        if (0 > waves[i].x + waves[i].xSize) {
          waveState = waveState_Finished;
        }
        break;
      case waveState_idle:
        break;
      default:
        console.log("Error " + waveState);
        break;
    }
    waves[i].draw();
  }

  for (let i = 0; i < users.length; i++) {
    users[i].draw();
  }
  //updateTime();
  //drawTimeRemaining()
}

function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("connected to mosquitto");
  client.subscribe(subscribedTopic);
}

function luggageNotification() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("luggage incoming");
  waveState = waveState_Washing;
}

function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
}

function onMessageArrived(message) {
  console.log(message.destinationName + " -> " + message.payloadString);

  try {
    inputs = JSON.parse(message.payloadString);

    if (typeof inputs === 'object' && inputs !== null) {
      if (typeof inputs.wave === "boolean") {
        if (inputs.wave) {
          luggageNotification();
        }
      }
      if (typeof inputs.user === 'object' && inputs.user !== null) {
        if (typeof inputs.user.id === "number" && 0 <= inputs.user.id && users.length >= inputs.user.id) {
          if (typeof inputs.user.size === "number") {
            users[inputs.user.id].updateSize(inputs.user.size, inputs.user.size)
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

function generateMessage(wave, users) {
  var obj = {
    "wave": wave,
    "users": users,
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

// Chairs, Wave, User

function setupChairs() {
  chairs[chairs.length] = new Chair(20, 50, chairSize, chairSize, chairStandardColor);
  chairs[chairs.length] = new Chair(300, 400, chairSize, chairSize, chairStandardColor);
}

function setupWave() {
  waves[waves.length] = new Wave();
}


class Wave {
  constructor() {
    this.x = windowWidth;
    this.y = 0;
    this.xSize = 40;
    this.ySize = windowHeight;
    this.color1 = 255;
  }

  reset() {
    this.x = windowWidth;
    this.y = 0;
  }

  update() {
    this.x = this.x - 2;
  }

  draw() {
    fill(this.color1);
    rect(this.x, this.y, this.xSize, this.ySize);
  }
}

class User {
  constructor() {
    this.name = "User";
    this.x = 0;
    this.y = 0;
    this.xSize = 70;
    this.ySize = 70;
    this.timeOfApperance = millis();
  }

  // Custom method for updating the variables
  updateSize(xSize, ySize) {
    if (700 < xSize) {
      xSize = 700;
    } else if (10 > xSize) {
      xSize = 10;
    }
    if (700 < ySize) {
      ySize = 700;
    } else if (10 > ySize) {
      ySize = 10;
    }
    this.xSize = xSize;
    this.ySize = ySize;
  }

  // Custom method for drawing the object
  draw() {
    fill(0, 12);
    rect(0, 0, this.xSize, this.ySize);
    fill(255);
    noStroke();
    ellipse(mouseX, mouseY, this.xSize, this.ySize);
  }
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
  update(fillColor) {
    if (0 > fillColor) {
      fillColor = 0;
    } else if (255 < fillColor) {
      fillColor = 255;
    }
    this.fillColor = fillColor;
  }

  // Custom method for drawing the object
  draw() {
    fill(this.fillColor);
    rect(this.x, this.y, this.xSize, this.ySize);
  }
}