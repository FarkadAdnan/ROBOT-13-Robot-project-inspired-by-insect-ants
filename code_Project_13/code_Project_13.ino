/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 https://linktr.ee/farkadadnan
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
 
#include <Servo.h>
#include <SoftwareSerial.h>
#define trigPin 7
#define echoPin 6
#define ledB 10

SoftwareSerial Bluetooth(12, 9);

Servo s24;
Servo s23;
Servo s22;

Servo s21;
Servo s20;
Servo s19;

Servo s18;
Servo s17;
Servo s16;

Servo s7;
Servo s8;
Servo s9;

Servo s10;
Servo s11;
Servo s12;

Servo s1;
Servo s2;
Servo s3;

Servo s15;
Servo s14;
Servo s13;

Servo s5;

int i0H1 = 0;
int i1H1 = 0;
int i2H1 = 0;
int i3H1 = 0;
int i4H1 = 0;
int i5H1 = 0;
int i6H1 = 0;
int i7H1 = 0;
int i8H1 = 0;

int i0T1 = 0;
int i1T1 = 0;
int i2T1 = 0;
int i3T1 = 0;
int i4T1 = 0;
int i5T1 = 0;
int i6T1 = 0;

int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 0;
int i4L1 = 0;
int i5L1 = 0;
int i6L1 = 0;

int i1L2 = 0;
int i2L2 = 0;
int i3L2 = 0;
int i4L2 = 0;
int i5L2 = 0;
int i6L2 = 0;
boolean l1status = LOW;
boolean l2status = LOW;
boolean aStatus = LOW;
boolean attStatus = LOW;
int k = 0;
int a = 0;
int aa = 0;
int period = 1000;
unsigned long time_now = 0;

float distance;
long duration;
int dataIn;
int m = 0;
int h = 0;
int t = 0;
int att = 0;
int speedV = 30;

void setup() {
  Serial.begin(38400);
  Bluetooth.begin(38400); 
  Bluetooth.setTimeout(1);
  delay(20);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledB, OUTPUT);
  // Head
  s15.attach(36, 600, 2400);
  s14.attach(35, 600, 2400);
  s13.attach(34, 600, 2400); 
  // Tail
  s5.attach(26, 600, 2400); 
  // Leg 4
  s10.attach(31, 600, 2400);
  s11.attach(32, 600, 2400);
  s12.attach(33, 600, 2400); 
  // Leg 5
  s7.attach(28, 600, 2400);
  s8.attach(29, 600, 2400);
  s9.attach(30, 600, 2400); 
  // Leg 6
  s1.attach(22, 600, 2400);
  s2.attach(23, 600, 2400);
  s3.attach(24, 600, 2400); 
  // Leg 1
  s18.attach(39, 600, 2400);
  s17.attach(38, 600, 2400);
  s16.attach(37, 600, 2400); 
  // Leg 2
  s21.attach(42, 600, 2400);
  s20.attach(41, 600, 2400);
  s19.attach(40, 600, 2400); 
  // Leg 3
  s24.attach(45, 600, 2400);
  s23.attach(44, 600, 2400);
  s22.attach(43, 600, 2400);

  s15.write(72);
  s14.write(50);
  s13.write(90); 
  
  s5.write(65); 
  
  // Leg 4
  s10.write(65);
  s11.write(35);
  s12.write(40);
  // Leg 5
  s7.write(80);
  s8.write(50);
  s9.write(25);
  // Leg 6
  s1.write(90);
  s2.write(45);
  s3.write(60);

  // Leg 1
  s18.write(60);
  s17.write(90);
  s16.write(100);
  // Leg 2
  s21.write(50);
  s20.write(85);
  s19.write(75);
  // Leg 3
  s24.write(50);
  s23.write(80);
  s22.write(80);

  delay(3000);
}
void loop() {

  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.read(); 
    if (dataIn == 2) {
      m = 2;
    }
    if (dataIn == 3) {
      m = 3;
    }
    if (dataIn == 4) {
      m = 4;
    }
    if (dataIn == 5) {
      m = 5;
    }
    if (dataIn == 10) {
      t = 10;
    }
    if (dataIn == 11) {
      h = 11;
    }
    if (dataIn >= 15) {
      speedV = dataIn;
    }
  }
  if (m == 2) {
    moveLeg1();
    moveLeg3();
    moveLeg5();
    if (l1status == HIGH) {
      moveLeg2();
      moveLeg4();
      moveLeg6();
    }
  }
  if (m == 3) {
    moveHeadLeft();
    moveLeg1();
    moveLeg3();
    moveLeg5Left();
    if (l1status == HIGH) {
      moveLeg2();
      moveLeg4Left();
      moveLeg6Left();
    }
  }
  if (m == 4) {
    moveHeadRight();
    moveLeg1Right();
    moveLeg3Right();
    moveLeg5();
    if (l1status == HIGH) {
      moveLeg2Right();
      moveLeg4();
      moveLeg6();
    }
  }
  if (m == 5) {
    moveLeg1Rev();
    moveLeg3Rev();
    moveLeg5Rev();
    if (l1status == HIGH) {
      moveLeg2Rev();
      moveLeg4Rev();
      moveLeg6Rev();
    }
  }
  if (dataIn == 6) {
    bite();
  }
  if (dataIn == 7) {
    prepareAttack();
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(1000);
        a = 1;
      }
      attack();
      if (attStatus == HIGH) {
        while (aa == 0) {
          delay(2000);
          aa = 1;
        } attStatus = LOW;
      }
    }
  }
  if (dataIn == 8) {
    grab();
  }
  if (dataIn == 9) {
    drop();
  }

  if (t == 10) {
    tail();
  }
  if (h == 11) {
    moveHead();
  }

  if (dataIn == 12) {
    initialPosTail();
  }
  if (dataIn == 13) {
    initialPosHead();
  }
  if (dataIn == 0) {
    initialPosition();
    if (getDistance() > 40) {
      att = 0;
    }
    if (getDistance() <= 40) {
      att = 1;
      dataIn = 99;
    }
    int sensorValue = analogRead(A3);
    float voltage = sensorValue * (5.00 / 1023.00) * 2.9; 
    Serial.println(voltage);
    if (voltage < 11) {
      digitalWrite(ledB, HIGH);
    }
    else {
      digitalWrite(ledB, LOW);
    }
  }
  if (att == 1) {
    prepareAttack();
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(2000);
        a = 1;
      }
      if (getDistance() > 30) {
        att = 2;
        a = 0;
        aStatus = LOW;
        initialPosHead();
      }
      if (getDistance() < 30) {
        att = 3;
        a = 0;
        aStatus = LOW;
        initialPosHead();
      }
    }
  }
  if (att == 2) {
    dismissAttack();
    if (aStatus == HIGH) {
      dataIn = 0;
      att = 0;
    }
  }
  if (att == 3) {
    attack();
    if (attStatus == HIGH) {
      while (aa == 0) {
        delay(2000);
        aa = 1;
      } attStatus = LOW;
    }
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(2000);
        a = 1;
      }
      dataIn = 0;
      att = 0;
      initialPosHead();
    }
  }
  delay(speedV);
}

void prepareAttack() {
  if (i1H1 <= 15) {
    s18.write(60 - i1H1);
    s17.write(90 - i1H1);
    s24.write(50 + i1H1 / 2);
    s23.write(80 + i1H1);
    s10.write(65 + i1H1);
    s11.write(35 + i1H1);
    s1.write(90 - i1H1);
    s2.write(45 - i1H1);
    s14.write(50 - i1H1 * 2);
    s13.write(90 - i1H1);

  }
  if (i1H1 <= 30) {
    s16.write(100 - i1H1);
    s19.write(75 - i1H1);
    s22.write(80 - i1H1);
    s12.write(35 + i1H1);
    s9.write(30 + i1H1);
    s3.write(60 + i1H1);
    i1H1++;
  }
  if (i1H1 >= 30) {
    aStatus = HIGH;
  }
}

void dismissAttack() {
  if (i2H1 <= 15) {
    s18.write(45 + i2H1);
    s17.write(75 + i2H1);
    s24.write(57 - i2H1 / 2);
    s23.write(95 - i2H1);
    s10.write(80 - i2H1);
    s11.write(50 - i2H1);
    s1.write(75 + i2H1);
    s2.write(30 + i2H1);
    s14.write(20 + i2H1 * 2);
    s13.write(75 + i2H1);
  }
  if (i2H1 <= 30) {
    s16.write(70 + i2H1);
    s19.write(45 + i2H1);
    s22.write(50 + i2H1);
    s12.write(65 - i2H1);
    s9.write(60 - i2H1);
    s3.write(90 - i2H1);
    i2H1++;
  }
  if (i2H1 >= 30) {
    aStatus = HIGH;
  }
}

void attack() {
  if (i3H1 <= 10) {
    s18.write(45 + i3H1 * 2);
    s17.write(75 + i3H1 * 3);
    s24.write(57 - i3H1 / 2);
    s23.write(95 - i3H1 * 3);
    s10.write(80 - i3H1 * 2);
    s11.write(50 - i3H1 * 3);
    s1.write(75 + i3H1 * 2);
    s2.write(30 + i3H1 * 3);
    s14.write(20 + i3H1 * 2);
    s13.write(75 + i3H1 * 3);
  }
  if (i3H1 <= 16) {
    s16.write(70 + i3H1 * 3);
    s19.write(45 + i3H1 * 3);
    s22.write(50 + i3H1 * 3);
    s12.write(65 - i3H1 * 3);
    s9.write(60 - i3H1 * 3);
    s3.write(90 - i3H1 * 3);
    i3H1++;
  }
  if (i3H1 >= 16) {
    attStatus = HIGH;
  }
  if (i3H1 >= 16 & i4H1 < 15) {
    s18.write(65 - i4H1 / 3);
    s17.write(105 - i4H1);
    s23.write(65 + i4H1);
    s10.write(60 + i4H1 / 3);
    s11.write(20 + i4H1);
    s1.write(95 - i4H1 / 5);
    s2.write(60 - i4H1);
    s14.write(40 + i4H1 / 2);
    s13.write(105 - i4H1);
  }
  if (i3H1 >= 16 & i4H1 <= 18) {
    s16.write(118 - i4H1);
    s19.write(93 - i4H1);
    s22.write(98 - i4H1);
    s12.write(17 + i4H1);
    s9.write(12 + i4H1);
    s3.write(42 + i4H1);
    i4H1++;
  }
  if (i4H1 >= 18) {
    aStatus = HIGH;
  }
}
void moveHead() {
  if (i0H1 <= 40) {
    s15.write(72 + i0H1);
    i0H1++;
  }
  if (i0H1 >= 40 & i1H1 <= 40) {
    s14.write(50 - i1H1 / 2);
    s15.write(112 - i1H1);
    i1H1++;
  }
  if (i1H1 >= 40 & i2H1 <= 20) {
    s13.write(90 - i2H1);
    i2H1++;
  }
  if (i2H1 >= 20 & i3H1 <= 10) {
    s13.write(70 + i3H1 * 4);
    i3H1++;
  }
  if (i3H1 >= 10 & i4H1 <= 40) {
    s13.write(110 - i4H1);
    i4H1++;
  }
  if (i4H1 >= 40 & i5H1 <= 10) {
    s13.write(70 + i5H1 * 4);
    i5H1++;
  }
  if (i5H1 >= 10 & i6H1 <= 20) {
    s13.write(110 - i6H1);
    i6H1++;
  }
  if (i6H1 >= 20 & i7H1 <= 40) {
    s14.write(30 + i7H1 / 2);
    s15.write(72 - i7H1);
    i7H1++;
  }
  if (i7H1 >= 40 & i8H1 <= 40) {
    s15.write(32 + i8H1);
    i8H1++;
  }
}

void bite() {
  if (i1H1 <= 20) {
    s13.write(90 - i1H1);
    i1H1++;
  }
  if (i1H1 >= 20 & i2H1 <= 10) {
    s13.write(70 + i2H1 * 4);
    i2H1++;
  }
  if (i2H1 >= 10 & i3H1 <= 40) {
    s13.write(110 - i3H1);
    i3H1++;
  }
  if (i3H1 >= 40 & i4H1 <= 10) {
    s13.write(70 + i4H1 * 4);
    i4H1++;
  }
  if (i4H1 >= 10 & i5H1 <= 40) {
    s13.write(110 - i5H1);
    i5H1++;
  }
  if (i5H1 >= 40 & i6H1 <= 20) {
    s13.write(70 + i6H1);
    i6H1++;
  }
}

void moveHeadLeft() {
  if (i0H1 <= 25) {
    s14.write(50 - i0H1);
    s15.write(72 - i0H1);
    s5.write(65 + i0H1); // Tail
    i0H1++;
  }
}
void moveHeadRight() {
  if (i2H1 <= 25) {
    s14.write(50 - i2H1);
    s15.write(72 + i2H1);
    s5.write(65 - i2H1); // Tail
    i2H1++;
  }
}

void grab() {
  if (i1H1 <= 20) {
    s13.write(90 + i1H1);
    i1H1++;
  }
}
void drop() {
  if (i2H1 <= 20) {
    s13.write(110 - i2H1);
    i2H1++;
  }
}

void tail() {
  if (i0T1 <= 25) {
    s5.write(65 - i0T1);
    i0T1++;
  }
  if ( i0T1 >= 25 & i1T1 <= 50) {
    s5.write(40 + i1T1);
    i1T1++;
  }
  if ( i1T1 >= 50 & i2T1 <= 50) {
    s5.write(90 - i2T1);
    i2T1++;
  }
  if ( i2T1 >= 50 & i3T1 <= 50) {
    s5.write(40 + i3T1);
    i3T1++;
  }
  if ( i3T1 >= 50 & i4T1 <= 50) {
    s5.write(90 - i4T1);
    i4T1++;
  }
  if ( i4T1 >= 50 & i5T1 <= 50) {
    s5.write(40 + i5T1);
    i5T1++;
  }
  if ( i5T1 >= 50 & i6T1 <= 25) {
    s5.write(90 - i6T1);
    i6T1++;
  }
}

void moveLeg1() {
  // Swign phase - move leg though air - from initial to final position
  // Rise the leg
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    s16.write(100 - i2L1);
    i2L1++;

  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    s16.write(70 + i4L1);
    i4L1++;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
  // Each iteration or step is executed in the main loop section where there is also a delay time for controlling the speed of movement
}
void moveLeg2() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(75 - i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(45 + i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(80 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(50 + i4L1);
  }
}

void moveLeg4() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(35 + i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(65 - i4L2);
  }
}

void moveLeg5() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(30 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(60 - i4L1);
  }
}

void moveLeg6() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(60 + i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(90 - i4L2);
  }
}

void moveLeg1Rev() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    Serial.println(s17.read());
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    Serial.println(s17.read());
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Rev() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Rev() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void moveLeg4Rev() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(65 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(35 + i4L2);
  }
}

void moveLeg5Rev() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void moveLeg6Rev() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(60 + i4L2);
  }
}

void moveLeg1Right() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Right() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Right() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void moveLeg4Left() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(60 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(30 + i4L2);
  }
}

void moveLeg5Left() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void moveLeg6Left() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(60 + i4L2);
  }
}

void initialPosTail() {
  i0T1 = 0;
  i1T1 = 0;
  i2T1 = 0;
  i3T1 = 0;
  i4T1 = 0;
  i5T1 = 0;
  i6T1 = 0;
  t = 0;
}

void initialPosHead() {
  attStatus = LOW;
  aStatus = LOW;
  i0H1 = 0;
  i1H1 = 0;
  i2H1 = 0;
  i3H1 = 0;
  i4H1 = 0;
  i5H1 = 0;
  i6H1 = 0;
  i7H1 = 0;
  i8H1 = 0;
  h = 0;
  aa = 0;
}

void initialPosition() {
  a = 0;
  aa = 0;
  m = 0;
  l1status = LOW;
  l2status = LOW;
  aStatus = LOW;
  attStatus = LOW;
  // Head
  s15.write(72);
  s14.write(55);
  s13.write(90); // Grip

  s5.write(65); // Tail

  // Leg 4
  s10.write(65);
  s11.write(35);
  s12.write(40);
  // Leg 5
  s7.write(80);
  s8.write(50);
  s9.write(25);
  // Leg 6
  s1.write(90);
  s2.write(45);
  s3.write(60);

  // Leg 1
  s18.write(60);
  s17.write(90);
  s16.write(100);
  // Leg 2
  s21.write(50);
  s20.write(80);
  s19.write(75);
  // Leg 3
  s24.write(50);
  s23.write(80);
  s22.write(80);
  i0H1 = 0;
  i1H1 = 0;
  i2H1 = 0;
  i3H1 = 0;
  i4H1 = 0;
  i5H1 = 0;
  i6H1 = 0;
  i7H1 = 0;
  i8H1 = 0;

  i0T1 = 0;
  i1T1 = 0;
  i2T1 = 0;
  i3T1 = 0;
  i4T1 = 0;
  i5T1 = 0;
  i6T1 = 0;

  i1L1 = 0;
  i2L1 = 0;
  i3L1 = 0;
  i4L1 = 0;
  i5L1 = 0;
  i6L1 = 0;

  i1L2 = 0;
  i2L2 = 0;
  i3L2 = 0;
  i4L2 = 0;
  i5L2 = 0;
  i6L2 = 0;
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  return distance;
}
