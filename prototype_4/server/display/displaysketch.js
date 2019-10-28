// setup MQTT client
client = new Paho.MQTT.Client("broker.shiftr.io", Number(443), "controlpanel");
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// some placeholders to keep track of time
var messagereceivedTime = 0;
var timeLeftPercentage = 0;

var userFollowSize_Slider;
var users = [];
var clientName = "display";

// sofa related values
var sofas = [];
var sofaSize = 80;
var sofaStandardColor = 0;
var sofaSwitchFade = true;
var sofaState = 0;
var sofaState_idle = 0;
var sofaState_Highlighting = 1;

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
  setupSofas();
  setupWave();
  users[users.length] = new User();

}

function draw() {
  background(0, 0, 0);
  users[0].updatePosition(mouseX, mouseY);

  for (let i = 0; i < sofas.length; i++) {
    switch (sofaState) {
      case sofaState_idle:
        sofas[i].setStandardFillColor();
        break;
      case sofaState_Highlighting:
        sofas[i].highlight();
        break;
      default:
        console.log("Error " + waveState);
        break;
    }
    sofas[i].draw();
  }
  for (let i = 0; i < waves.length; i++) {
    switch (waveState) {
      case waveState_Finished:
        waves[i].reset();
        waveState = waveState_idle;
        break;
      case waveState_Washing:
        waves[i].update();
        if (windowWidth < waves[i].x - waves[i].xSize) {
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
  //console.log(message.destinationName + " -> " + message.payloadString);

  try {
    inputs = JSON.parse(message.payloadString);

    if (typeof inputs === 'object' && inputs !== null) {
      if (typeof inputs.from === "string" && typeof inputs.to === "string") {
        if ("all" === inputs.to) { 
          generateMessage(clientName, inputs.from, "online")
        }
        if (clientName === inputs.to) {
          if (typeof inputs.debug === "string") {
            if (typeof inputs.debug === "string") {
              console.log(inputs.debug + " : " + inputs.from);
            }
          }
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
              if (typeof inputs.user.posX === "number" && typeof inputs.user.posY === "number") {
                users[inputs.user.id].updatePosition(inputs.user.posX, inputs.user.posY)
              }
            }
          }
          if (typeof inputs.sofa === 'object' && inputs.sofa !== null) {
            if (typeof inputs.sofa.id === "number" && 0 <= inputs.sofa.id && sofas.length >= inputs.sofa.id) {
              if (typeof inputs.sofa.sofaPosition === "number" && inputs.sofa.highlightStatus) {
                sofaState = sofaState_Highlighting;
                console.log("sofa highlighting");
              } else if (typeof inputs.sofa.sofaPosition === "number" && !inputs.sofa.highlightStatus) {
                sofaState = sofaState_idle;
                console.log("sofa is off");
              }
            }
          }
        } 
      }
    }
  } catch (e) {
    console.log("error parsing data!")
  }
}

function generateMessage(from, to, debug) {
  var obj = {
    "from": from,
    "to": to,
    "debug": debug
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

// Sofas, Wave, User

function setupSofas() {
  sofas[sofas.length] = new Sofa(20, 50, sofaSize, sofaSize, sofaStandardColor);
}

function setupWave() {
  waves[waves.length] = new Wave();
}


class Wave {
  constructor() {
    this.xSize = 40;
    this.ySize = windowHeight;
    this.x = 0 - this.xSize;
    this.y = 0;
    this.color1 = 255;
    this.color2 = 200;
    this.color3 = 150;
    this.color4 = 100;
  }

  reset() {
    this.x = 0 - this.xSize;
    this.y = 0;
  }

  update() {
    this.x = this.x + 5;
  }

  setGradient(x, y, w, h) {
    noFill();
    let inter = map(x, y, y + h, 0, 1);
    let c = lerpColor(color(204, 102, 0), color(0, 102, 153), inter);
    stroke(c);
    line(x, y, x, y + h);
  }

  draw() {
    fill(this.color1);
    rect(this.x, this.y, this.xSize, this.ySize);
    //this.setGradient(this.x, this.y, this.xSize, this.ySize);
  }
}

class User {
  constructor() {
    this.name = "User";
    this.x = windowWidth / 2;
    this.y = windowHeight;
    this.xSize = 130;
    this.ySize = 130;
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

  updatePosition(x, y) {
    this.x = x;
    this.y = y;
  }

  drawGradient(x, y) {
    let radius = this.xSize;
    let h = 0;//random(0, 360);
    for (let r = radius; r > 0; --r) {
      fill(h, h, h);
      ellipse(x, y, r, r);
      h = (h + 2) % 360;
    }
  }

  draw() {
    //fill(255);
    noStroke();
    //ellipse(this.x, this.y, this.xSize, this.ySize);
    this.drawGradient(this.x, this.y);
  }
}

class Sofa {
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

  highlight() {
    if (250 <= this.fillColor) {
      sofaSwitchFade = true;
    } else if (5 >= this.fillColor) {
      sofaSwitchFade = false;
    }
    if (sofaSwitchFade) {
      this.fillColor -= 2;
    } else {
      this.fillColor += 2;
    }
  }

  setStandardFillColor() {
    if (sofaStandardColor < this.fillColor) {
      this.fillColor -= 2;
    } else {
      this.fillColor = sofaStandardColor;
    }
  }

  // Custom method for drawing the object
  draw() {
    fill(this.fillColor);

    beginShape();
    vertex(0, 10);
    vertex(750, 60);
    vertex(750, 310);
    vertex(200, 290);
    vertex(200, 600);
    vertex(0, 600);
    endShape(CLOSE);
  }
}