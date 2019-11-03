var particles = [];

function setup() {
  createCanvas(windowWidth, windowHeight);
  ellipseMode(RADIUS);
  noFill();
}

function draw() {
  background(0);
  if (particles.length < 200) particles.push(new Particle());
  for (var i = 0; i < particles.length; i++) {
    particles[i].update();
    particles[i].display();
  }
}

class Particle {
  
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