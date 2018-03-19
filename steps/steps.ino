
#include <SparkFun_MMA8452Q.h>

MMA8452Q accel;

const int len = 100;

float buf[len]; // buffer
int loc;        // current location in buffer array

const float threshold = .4;
const int debounce = 250;

unsigned long delta;

bool isPeaking;   // true if currently in a peak

int numPeaks;

enum State {
  xd,   // in x-direction
  yd,   // in y-direction
  zd    // in z-direction
};

State state;

void setup() {
  Serial.begin(9600);
  accel.init();
  loc = 0;
  isPeaking = false;
  numPeaks = 0;
  delta = millis();
}

void loop() {
  if (accel.available()) {
    readState();
    updateState();
    checkPeak();
    
    Serial.print(mag());
    Serial.print(", ");
//    Serial.print(" ");
//    Serial.print(numPeaks);
//    Serial.print(" ");
//    Serial.println(avg());
  }
}


void checkPeak() {
  if (mag() - avg() > threshold) {
    if (!isPeaking && delta < millis()) {
      isPeaking = true;
      numPeaks ++;
      //Serial.println(numPeaks);
    }
  } else {
    if (isPeaking) {
      delta = millis() + debounce;
    }
    isPeaking = false;
  }
}

void readState() {
  accel.read();
  place(mag());
}

void place(float num) {
  buf[(loc++) % len] = num;
}

float avg() {
  if (loc == 0) {
    return 0;
  }
  float sum = 0;
  for (float i : buf) {
    sum += i;
  }
  return sum / min(loc, len);
}

void printA() {
  Serial.print(cx());
  Serial.print("\t");
  Serial.print(cy());
  Serial.print("\t");
  Serial.println(cz());
}

void printState() {
  if (state == xd) {
    Serial.println("x");
  } else if (state == yd) {
    Serial.println("y");
  } else {
    Serial.println("z");
  }
}

void printMag() {
  Serial.println(mag());
}

float mag() {
  return sqrt(cx() * cx() + cy() * cy() + cz() * cz());
}

void updateState() {
  float xx = abs(cx());
  float yy = abs(cy());
  float zz = abs(cz());
  if (xx > yy && xx > zz) {
    state = xd;
    return;
  }
  if (yy > xx && yy > zz) {
    state = yd;
    return;
  }
  state = zd;
}

float x() {
  return accel.x;
}

float y() {
  return accel.y;
}

float z() {
  return accel.z;
}

float cx() {
  return accel.cx;
}

float cy() {
  return accel.cy;
}

float cz() {
  return accel.cz;
}



