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
var currentUser = 0;

// user connection possibilities
var userConnections = [];
userConnectionLines = [];

// sofa related values
var sofas = [];
var sofaSize = 80;
var sofaStandardColor = 0;
var sofaSwitchFade = true;
var sofaState = 0;
var sofaState_idle = 0;
var sofaState_Highlighting = 1;

// ambient light variables
var als = [];
var alStandardColor = 0;
var alSwitchFade = true;
var alState = 0;
var alState_idle = 0;
var alState_highlighting_1 = 1;
var alState_highlighting_2 = 2;
var alState_highlighting_all = -1;

// sofa seats
var sofaSeats = [];

// wave related values
var waves = [];
var waveCount = 0;
var waveState = 0;
var waveState_idle = 0;
var waveState_Washing = 1;
var waveState_Finished = 2;

// general state to try out different user trackings, lights, connections, ...
var displayState = 3;
var displayState_0 = 0;
var displayState_1 = 1;
var displayState_2 = 2;
var displayState_3 = 3;

// journey states
var journeyState = 0;
var journeyState_0 = 0;
var journeyState_1 = 1;
var journeyState_2 = 2;
var journeyState_3 = 3;
var journeyState_4 = 4;
var journeyState_5 = 5;
var journeyState_6 = 6;
var journeyState_7 = 7;
var journeyState_8 = 8;
var journeyState_Started = false;

// animation variables
var animationParticlesRight = [];


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
  users[currentUser] = new User();
  if (displayState_3 <= displayState) {
    users[currentUser].setupUserLine();
  }
}

function draw() {
  // going to next journey step by mouse click on display
  if (mouseIsPressed) {
    increaseJourneyState();
  }
  actOutJourney();
  background(0, 0, 0);
  users[currentUser].updatePosition(mouseX, mouseY);
  // ambient Light
  //for (let i = 0; i < als.length; i++) {
  //  switch (alState) {
  //    case alState_idle:
  //      als[i].setStandardFillColor();
  //      alState = alState_idle;
  //      break;
  //    case alState_highlighting_1:
  //      als[i].highlight();
  //      break;
  //    default:
  //      console.log("Error " + waveState);
  //      break;
  //  }
  //  als[i].drawLeft();
  //}
  for (let i = 0; i < sofas.length; i++) {

    // draw sofa
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
    if (journeyState_3 < journeyState && journeyState < journeyState_6) {
      var sofaInUse = false;
      for (let z = 0; z < sofaSeats.length; z++) {
        if (sofaSeats[z].inUse) {
          sofaInUse = true;
        }
      }
      if (sofaInUse) {
        for (let z = 0; z < sofaSeats.length; z++) {
          if (!sofaSeats[z].inUse) {
            sofas[i].drawSingleSeat(sofaSeats[z].x, sofaSeats[z].y)
          }
        }
      }
    }
    if (!sofaInUse || undefined === sofaInUse) {
      sofas[i].draw();
    }
  }

  if (animationParticlesRight.length < 200) animationParticlesRight.push(new AnimationRight());
  for (var i = 0; i < animationParticlesRight.length; i++) {
    animationParticlesRight[i].update();
    animationParticlesRight[i].display();
  }
  // draw users connection
  //if (1 <= currentUser) {
  //  if (displayState_2 === displayState) {
  //    for (let o = 0; o < userConnections.length; o++) {
  //      if (currentUser === userConnections[o].currentUserConnect)
  //        userConnections[o].updateNewestUserPoint();
  //    }
  //    for (let i = 0; i < userConnections.length; i++) {
  //      userConnections[i].draw();
  //    }
  //  } else {
  //    for (let o = 0; o < userConnectionLines.length; o++) {
  //      if (currentUser === userConnectionLines[o].currentUserConnect)
  //        userConnectionLines[o].updateNewestUserPoint();
  //    }
  //    for (let i = 0; i < userConnectionLines.length; i++) {
  //      userConnectionLines[i].highlight();
  //      userConnectionLines[i].draw();
  //    }
  //  }
  //}
  // draw wave
  //for (let i = 0; i < waves.length; i++) {
  //  switch (waveState) {
  //    case waveState_Finished:
  //      waves[i].reset();
  //      waveState = waveState_idle;
  //      break;
  //    case waveState_Washing:
  //      waves[i].update();
  //      if (windowHeight < waves[i].y - waves[i].ySize) {
  //        waveCount++;
  //        waves[i].reset();
  //      }
  //      if (5 < waveCount) {
  //        waveState = waveState_Finished;
  //        waveCount = 0;
  //      }
  //      break;
  //    case waveState_idle:
  //      break;
  //    default:
  //      console.log("Error " + waveState);
  //      break;
  //  }
  //  waves[i].draw();
  //}
  // draw user specific light
  //for (let i = 0; i < users.length; i++) {
  //  if (displayState_0 === displayState) {
  //    users[i].draw();
  //  } else if (displayState_3 > displayState) {
  //    users[i].drawInsideSofa();
  //  }
  //}
  //updateTime();
  //drawTimeRemaining()
}

function setJourneyState(newState) {
  journeyState = newState;
  checkIfValidJourneyState();
  console.log("journeyState set to: " + journeyState);
}

function increaseJourneyState() {
  journeyState += 1;
  checkIfValidJourneyState();
  console.log("journeyState increased to: " + journeyState);
}

function checkIfValidJourneyState() {
  if (journeyState_8 < journeyState) {
    journeyState = journeyState_0;
  } else if (journeyState_0 > journeyState) {
    journeyState = journeyState_0;
  }
  journeyState_Started = false;
  generateCurrentJourneyMessage("control");
}

function generateCurrentJourneyMessage(to) {
  var obj = {
    "from": clientName,
    "to": to,
    "journey": {
      "current": journeyState
    }
  };
  sendMessage(compileMessage(obj));
}

function actOutJourney() {
  switch (journeyState) {
    // ⓪ idle, nothing happens
    case journeyState_0:
      if (!journeyState_Started) {
        sofaState = sofaState_idle;
        console.log("sofa is idle");
        // TODO al off
        // TODO all animations off
        // TODO everything off
        journeyState_Started = true;
      }
      // maybe idle animation after a while standbye
      //setTimeout(function () {
      //  animationState = animationState_sofaIdle;
      //}, 2000);
      break;
    // ① person 1 enters, sofa lights up
    case journeyState_1:
      if (!journeyState_Started) {
        console.log("u1 sofa highlighted");
        sofaState = sofaState_Highlighting;
        journeyState_Started = true;
      }
      // maybe: sofa lights up when near to u2 (ambientlight?)
      break;
    // ② person 1 sits down, 
    case journeyState_2:
      if (!journeyState_Started) {
        console.log("u1 sits down");
        sofaState = sofaState_idle;
        journeyState_Started = true;
      }

      if (sofaStandardColor + 5 >= sofas[0].fillColor) {
        increaseJourneyState();
      }
      break;
    // ⓷ animation for 1
    case journeyState_3:
      if (!journeyState_Started) {
        console.log("u1 animation");
        journeyState_Started = true;
      }
      // TODO animation u1 runs
      break;
    // ⓸ person 1 sits, person 2 enters, sofa lights up partly
    case journeyState_4:
      if (!journeyState_Started) {
        console.log("u2 sofa highlighted");
        sofaState = sofaState_Highlighting;
        journeyState_Started = true;
      }
      // maybe: sofa lights up when near to u2 (ambientlight?)
      break;
    // ⓹ person 1 sits, person 2 sits down
    case journeyState_5:
      if (!journeyState_Started) {
        console.log("u2 sits down");
        sofaState = sofaState_idle;
        journeyState_Started = true;
      }
      if (sofaStandardColor + 5 >= sofas[0].fillColor) {
        increaseJourneyState();
      }
      break;
    // ⑥ person 1+2 sit, 1+2 animation
    case journeyState_6:
      if (!journeyState_Started) {
        console.log("u1+2 animations");
        setSofaSeatsInUse(true,true);
        sofaState = sofaState_idle;
        journeyState_Started = true;
      } else if (sofaState_idle === sofaState) {
        // TODO animations u1+2 run
      }
      break;
    // ⑦ person 1+2 sit, luggage enters
    case journeyState_7:
      if (!journeyState_Started) {
        console.log("‼️‼️‼️ LUGGAGE LIGHT ON ‼️‼️‼️");
        journeyState_Started = true;
      }
      break;
    // ⑧ person 1+2 exit
    case journeyState_8:
      if (!journeyState_Started) {
        // TODO u1+2 al off
        // TODO u1+2 animations off
        console.log("u1+2 leave")
        journeyState_Started = true;
      }
      setTimeout(function () {
        location.reload();
      }, 5000);
      break;
    default:
      console.log("journeyState: " + journeyState);
      break;
  }
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
            if ("reload" === inputs.debug) {
              location.reload();
            } else {
              console.log(inputs.debug + " : " + inputs.from);
            }
          }
          if (typeof inputs.wave === "boolean") {
            if (inputs.wave) {
              luggageNotification();
            }
          }
          if (typeof inputs.al === "boolean") {
            if (inputs.al) {
              alState = alState_highlighting;
            } else {
              alState = alState_idle;
            }
          }
          if (typeof inputs.journey === 'object' && inputs.journey !== null) {
            if (typeof inputs.journey.current === "number") {
              setJourneyState(inputs.journey.current);
            } else if (typeof inputs.journey.next === "boolean" && inputs.journey.next) {
              increaseJourneyState();
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
          if (typeof inputs.user === 'object' && inputs.user !== null) {
            if (typeof inputs.user.id === "number" && 0 <= inputs.user.id) {
              if (0 === inputs.user.id || users.length - 1 === inputs.user.id) {
                if (typeof inputs.user.size === "number") {
                  users[inputs.user.id].updateSize(inputs.user.size, inputs.user.size)
                }
                if (typeof inputs.user.posX === "number" && typeof inputs.user.posY === "number") {
                  users[inputs.user.id].updatePosition(inputs.user.posX, inputs.user.posY)
                }
              } else if (displayState_3 > displayState && 0 != inputs.user.id || users.length - 1 === inputs.user.id + 1) {
                currentUser = inputs.user.id;
                users[currentUser] = new User();

                if (2 === users.length) {
                  if (displayState_2 === displayState) {
                    userConnections[currentUser - 1] = new Userconnection(users[inputs.user.id - 1].x, users[inputs.user.id - 1].y, users[inputs.user.id].x, users[inputs.user.id].y, currentUser);
                    userConnections[currentUser].setup();
                  } else {
                    userConnectionLines[currentUser - 1] = new UserconnectionLines(users[inputs.user.id - 1].x, users[inputs.user.id - 1].y, users[inputs.user.id].x, users[inputs.user.id].y, currentUser);
                    userConnectionLines[currentUser].setup();
                  }
                } else {
                  if (displayState_2 === displayState) {
                    for (let i = 0; i < users.length; i++) {
                      userConnections[userConnections.length] = new Userconnection(users[i].x, users[i].y, users[currentUser].x, users[currentUser].y, currentUser);
                      userConnections[userConnections.length - 1].setup();
                    }
                  } else {
                    for (let i = 0; i < users.length; i++) {
                      userConnectionLines[userConnectionLines.length] = new Userconnection(users[i].x, users[i].y, users[currentUser].x, users[currentUser].y, currentUser);
                      userConnectionLines[userConnectionLines.length - 1].setup();
                    }
                  }
                }
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

function setSofaSeatsInUse(left, right) {
  if (typeof left === "boolean" && null !== left) {
    sofaSeats[0].inUse = left;
  }
  if (typeof right === "boolean" && null !== right) {
    sofaSeats[1].inUse = right;
  }
  generateSofaSeatsMessage(clientName, "console", sofaSeats[0].inUse, sofaSeats[1].inUse)
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

// Sofas, Wave, User

function setupSofas() {
  sofas[sofas.length] = new Sofa(20, 50, sofaSize, sofaSize, sofaStandardColor);
  sofaSeats[0] = new SofaSeat("left", false, -1, 250, 300);
  sofaSeats[1] = new SofaSeat("right", false, -1, 500, 300);
  als[als.length] = new AL();
}

function setupWave() {
  waves[waves.length] = new Wave();
}

class Userconnection {
  constructor(beginX, beginY, endX, endY, currentUserConnect) {
    this.beginX = beginX;
    this.beginY = beginY;
    this.endX = endX;
    this.endY = endY;
    this.distX = this.endX - this.beginX;
    this.distY = this.endY - this.beginY;
    this.exponent = 4;
    this.x = 0.0;
    this.y = 0.0;
    this.step = 0.01;
    this.pct = 0.0;
    this.fillOpacity = 0;
    this.currentUserConnect = currentUserConnect;
  }

  setup() {
    noStroke();
  }

  resetToCurrentValues() {
    this.x = 0.0;
    this.y = 0.0;
    this.pct = 0.0;
  }

  draw() {
    //fill(0, 2);
    //rect(0, 0, this.width, this.height);
    this.pct += this.step;
    if (0.5 > this.pct) {
      this.fillOpacity += this.step;
    } else {
      this.fillOpacity -= this.step;
    }
    if (0 > this.fillOpacity) {
      this.fillOpacity = 0;
    } else if (1 < this.fillOpacity) {
      this.fillOpacity = 1;
    }
    if (this.pct < 1.0) {
      this.x = this.beginX + this.pct * this.distX;
      this.y = this.beginY + pow(this.pct, this.exponent) * this.distY;
    } else {
      this.resetToCurrentValues();
    }
    let c = color('rgba(255%, 255%, 255%, ' + this.fillOpacity + ')');
    fill(c);
    ellipse(this.x, this.y, 20, 20);
  }

  updateNewestUserPoint() {
    this.endX = users[currentUser].x;
    this.endY = users[currentUser].y;
    this.distX = this.endX - this.beginX;
    this.distY = this.endY - this.beginY;
  }
}

class UserconnectionLines {
  constructor(beginX, beginY, endX, endY, currentUserConnect) {
    this.beginX = beginX;
    this.beginY = beginY;
    this.endX = endX;
    this.endY = endY;
    this.fillOpacityStatus = true;
    this.fillOpacity = 100;
    this.strokeWidthStatus = true;
    this.strokeWidth = 0;
    this.currentUserConnect = currentUserConnect;
  }

  setup() {
    noFill();
  }

  highlight() {
    // opacity
    if (150 <= this.fillOpacity) {
      this.fillOpacityStatus = true;
    } else if (50 >= this.fillOpacity) {
      this.fillOpacityStatus = false;
    }
    if (this.fillOpacityStatus) {
      this.fillOpacity -= 1;
    } else {
      this.fillOpacity += 1;
    }
    // opacity
    if (20 <= this.strokeWidth) {
      this.strokeWidthStatus = true;
    } else if (15 >= this.strokeWidth) {
      this.strokeWidthStatus = false;
    }
    if (this.strokeWidthStatus) {
      this.strokeWidth -= 0.05;
    } else {
      this.strokeWidth += 0.05;
    }
  }

  draw() {
    let c = color('rgba(' + this.fillOpacity + '%, ' + this.fillOpacity + '%, ' + this.fillOpacity + '%, ' + this.fillOpacity + ' )');
    stroke(c);
    strokeWeight(this.strokeWidth);
    noFill();
    let x1 = Math.floor(Math.random() * 1 + map(this.beginX, 0, windowWidth, 0, 250));
    let y1 = Math.floor(Math.random() * 1 + map(this.beginX, 0, windowHeight, 0, 250));
    let x2 = Math.floor(Math.random() * 1 + map(this.endX, 0, windowWidth, 0, 250));
    let y2 = Math.floor(Math.random() * 1 + map(this.endY, 0, windowHeight, 0, 250));
    bezier(this.beginX, this.beginY, x1, y1, x2, y2, this.endX, this.endY);
  }
  updateNewestUserPoint() {
    this.endX = users[currentUser].x;
    this.endY = users[currentUser].y;
    this.distX = this.endX - this.beginX;
    this.distY = this.endY - this.beginY;
  }
}


class Wave {
  constructor() {
    this.xSize = windowWidth;
    this.ySize = 40;
    this.x = 0;
    this.y = 0 - this.ySize;
    this.color1 = 255;
    this.color2 = 200;
    this.color3 = 150;
    this.color4 = 100;
  }

  reset() {
    this.x = 0;
    this.y = 0 - this.ySize;
  }

  update() {
    this.y = this.y + 10;
  }

  setGradient(x, y, w, h) {
    noFill();
    let inter = map(x, y, y + h, 0, 1);
    let c = lerpColor(color(204, 102, 0), color(0, 102, 153), inter);
    stroke(c);
    line(x, y, x, y + h);
  }

  draw() {
    noStroke();
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
    this.fillColor;

    this.x1 = 0;
    this.y1 = 0;
    this.x2 = this.x1;
    this.y2 = this.y2;
  }

  setupUserLine() {
    strokeWeight(20);
    stroke(255, 100);

    this.x1 = windowWidth / 2;
    this.y2 = windowHeight / 2;
    this.x2 = this.x1;
    this.y2 = this.y2;
    this.segLength = 80;
  }

  drawUserLine() {
    background(0);
    this.dragSegment(0, mouseX, mouseY);
    for (let i = 0; i < this.x.length - 1; i++) {
      this.dragSegment(i + 1, x[i], y[i]);
    }
  }

  dragSegment(i, xin, yin) {
    background(0);

    let dx = mouseX - this.x1;
    let dy = mouseY - this.y1;
    let angle1 = atan2(dy, dx);

    let tx = mouseX - cos(angle1) * this.segLength;
    let ty = mouseY - sin(angle1) * this.segLength;
    dx = tx - this.x2;
    dy = ty - this.y2;
    let angle2 = atan2(dy, dx);
    this.x1 = this.x2 + cos(angle2) * this.segLength;
    this.y1 = this.y2 + sin(angle2) * this.segLength;

    this.segment(this.x1, this.y1, angle1);
    this.segment(this.x2, this.y2, angle2);
  }

  segment(x, y, a) {
    push();
    translate(x, y);
    rotate(a);
    line(0, 0, this.segLength, 0);
    pop();
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

  drawInsideSofa() {
    noStroke();
    this.drawGradient();

    drawFloorAroundSofa();
  }

  update(fillColor) {
    if (0 > fillColor) {
      fillColor = 0;
    } else if (255 < fillColor) {
      fillColor = 255;
    }
    this.fillColor = fillColor;
  }

  drawGradient() {
    let radius = this.xSize;
    let h = 0;

    for (let r = radius; r > 0; --r) {
      let a = map(h, 0, 500, 0, 1)
      let c = color('rgba(255%, 255%, 255%, ' + a + ')');
      fill(c);
      ellipse(this.x, this.y, r, r);
      h = (h + 1) % 500;
    }
  }

  draw() {
    //fill(255);
    noStroke();
    //ellipse(this.x, this.y, this.xSize, this.ySize);
    this.drawGradient();
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

  drawSingleSeat(x, y) {
    noStroke();
    this.drawGradient(x, y);

    drawFloorAroundSofa();
  }

  setStandardFillColor() {
    if (sofaStandardColor < this.fillColor) {
      this.fillColor -= 2;
    } else {
      this.fillColor = sofaStandardColor;
    }
  }

  drawGradient(x, y) {
    ;
    let h = 0;

    for (let r = 350; r > 0; --r) {
      let a = map(h, 0, 3000, 0, 1)
      let c = color('rgba(' + this.fillColor + '%,' + this.fillColor + '%,' + this.fillColor + '%, ' + a + ')');
      fill(c);
      //ellipse(310, 440, r, r);
      rect(x - (r / 2), y - (r / 2), 100 + r, 100 + r, 100);
      h = (h + 1) % 3000;
    }
  }

  // Custom method for drawing the object
  draw() {

    noStroke();
    fill(this.fillColor);

    beginShape();
    vertex(142, 168);
    vertex(172, 155);
    vertex(420, 150);
    vertex(675, 160);
    vertex(703, 172);
    vertex(710, 475);
    vertex(703, 483);
    vertex(655, 526);
    vertex(205, 524);
    vertex(137, 470);
    endShape(CLOSE);
    noStroke();
  }
}

class SofaSeat {
  constructor(id, inUse, user, x, y) {
    this.id = id;
    this.inUse = inUse;
    this.user = user;
    this.x = x;
    this.y = y;
  }
}

class AL {
  constructor() {
    this.user = "user";
    this.fillColor = alStandardColor;
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
    if (100 <= this.fillColor) {
      alSwitchFade = true;
    } else if (50 >= this.fillColor) {
      alSwitchFade = false;
    }
    if (alSwitchFade) {
      this.fillColor -= 0.4;
    } else {
      this.fillColor += 0.4;
    }
  }

  setStandardFillColor() {
    if (alStandardColor < this.fillColor) {
      this.fillColor -= 2;
    } else {
      this.fillColor = alStandardColor;
    }
  }

  drawGradient() {
    ;
    let h = 0;

    for (let r = 200; r > 0; --r) {
      let a = map(h, 0, 3000, 0, 1)
      let c = color('rgba(255%, 255%, 255%, ' + a + ')');
      fill(c);
      //ellipse(310, 440, r, r);
      rect(250 - (r / 2), 400 - (r / 2), 100 + r, 100 + r, 100);
      h = (h + 1) % 3000;
    }
  }

  drawLeft() {
    // gradient
    //noFill();

    //var c1 = color(255, 204, 0);
    //var c2 = color(255);
    //var inter = map(y, 0, 20, 0, 1);
    //var c = lerpColor(c1, c2, inter);
    //stroke(c);
    //line(670, 525, 215, 550);
    //line(215, 550, 155, 510);
    //line(155, 510, 142, 340);

    noStroke();
    this.drawGradient();


    drawSofaOutline();
  }
}

class AnimationRight {
  
  constructor() {
    this.reset();
  }

  reset() {
    this.x = random(width);
    this.y = random(-150, 0);
    this.vy = random(0.1, 2);
    this.maxy = this.y + 450;
    this.r = 0;
    this.tr = 50;
    this.w = random(0.1, 2);
  }

  update() {
    if (this.y < this.maxy) {
      this.y += this.vy;
    } else {
      this.r++;
    }
    if (this.r > this.tr) this.reset();
  }

  display() {
    ellipseMode(RADIUS);
    noFill();
    strokeWeight(this.w);
    if (this.y < this.maxy) {
     stroke(255);
     push();
     translate(this.x,this.y);
     beginShape();
     strokeWeight(1);
     vertex(0,-5);
     quadraticVertex(3, 0, 0, 1);
     quadraticVertex(-3,0, 0, -5);
     endShape(CLOSE);
     pop();
    } else {
      stroke(255, map(this.r, 0, this.tr, 255, 0));
      ellipse(this.x, this.y, this.r, this.r*.5);
    }
  }
}

function drawSofaOutline() {
  fill(0, 0, 0);
  beginShape();
  vertex(142, 168);
  vertex(172, 155);
  vertex(420, 150);
  vertex(675, 160);
  vertex(703, 172);
  vertex(710, 475);
  vertex(703, 483);
  vertex(655, 526);
  vertex(201, 525);
  vertex(137, 470);
  endShape(CLOSE);
  noStroke();
}

function drawFloorAroundSofa() {
  fill(0, 0, 0);
  beginShape();
  vertex(0, 0);
  vertex(140, 205);//s
  vertex(700, 175);//s
  vertex(728, 475);//s
  vertex(670, 525);//s
  vertex(215, 550);//s
  vertex(155, 510);//s
  vertex(140, 205);//s again
  vertex(0, 0);
  vertex(0, windowHeight);
  vertex(windowWidth, windowHeight);
  vertex(windowWidth, 0);
  endShape(CLOSE);
  noStroke();
}

function drawSofaOnlySeatRight() {
  fill(0, 0, 0);
  beginShape();
  vertex(0, 0);
  vertex(140, 205);//s
  vertex(700, 175);//s
  vertex(728, 475);//s
  vertex(670, 525);//s
  vertex(215, 550);//s
  vertex(155, 510);//s
  vertex(140, 205);//s again
  vertex(0, 0);
  vertex(0, windowHeight);
  vertex(windowWidth, windowHeight);
  vertex(windowWidth, 0);
  endShape(CLOSE);
  noStroke();
}