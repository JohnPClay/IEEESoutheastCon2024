


//void line_Follow() {
//
//
//
//
//  if ( mySensorBar.getDensity() < 7 )
//  {
//
//    if ( mySensorBar.getPosition() < -25 ) //checking to see if the line is on the left side of the sensor
//    {
//      Serial.println("turning left");
//      turnLeft(50, 90);
//    }
//    if ( mySensorBar.getPosition() > 25 ) //checking to see if the line is on the right side of the sensor
//    {
//      Serial.println("turning right");
//      //turnRight(50, 90);
//    }
//    else if (mySensorBar.getPosition() >= -25 and mySensorBar.getPosition() <= 25){ //checking to see if the line is in the center of the sensor
//        Serial.println("going forward");
//        forwardS(50, 0.25);
//    }
//  }
//  else if (mySensorBar.getDensity() > 7){ //checking to see if the line is more "dense" than usual i.e brighter/the entire length of sensor.
//    Serial.println("white line found");
//   //ebreak(20);
//  }
//
//}


/*
void line_Follow() {
  currentDensity = mySensorBar.getDensity(); 
  while ((currentDensity <= 7) or (previousDensity <= 7)) { // While loop to check if yellow line is detected (i.e. normal sequence for yellow line)
    Serial.println(mySensorBar.getDensity());
    currentDensity = mySensorBar.getDensity(); 
    //Serial.println(mySensorBar.getDensity());
    if ((currentDensity == 0) and (previousDensity == 0)) { // If statement used for turning the robot 90 dgrees once a 90 degree turn is detected
      ebreak(20);
      backward(55,0.25);
      //Serial.println("This is where the turn code will go");
      delay(500);

      return;

    } // End of 90 degree turn if statement

    if ((currentDensity > 7) and (previousDensity > 7)) { // If statement used for detecting the white line in the course
      ebreak(20);
      backward(55,0.25);

      //Serial.println("This is where the white line code will go");
      delay(500);
//      backward(70,0.35);
//      ebreak(500);
      return;

    }
    
    error = mySensorBar.getPosition();
    if ( error > 20) // checking to see if the line is on the left side of the sensor
    {

      R_Speed = MAXSPEED;
      L_Speed = MINSPEED;//MAXSPEED + (Kp * error) + (Kd * (error - lastError)); // plus since error is negative, will result in negative values for proportionate term
      //L_Speed = constrain(L_Speed, MINSPEED, MAXSPEED);
      Serial.println("Robot Turn Left Statement");


    } // End of line on left side of robot if statement
    else if (error <- 20) { // checking to see if the line is on the right side of the sensor
      

      R_Speed = MINSPEED;//MAXSPEED - (Kp * error) - (Kd * (error - lastError));
      L_Speed = MAXSPEED; // plus since error is negative, will result in negative values for proportionate term
      //R_Speed = constrain(R_Speed, MINSPEED, MAXSPEED);
      Serial.println("Robot Turn Right Statement");

    } // End of line on right side of robot else if statement
    else { //checking to see if the line is in the center of the sensor

      L_Speed = MAXSPEED;
      R_Speed = MAXSPEED;
     // Serial.println("Robot Goes Straight Statement");


    } // End of center line else statement
    previousDensity = currentDensity;
    forwardS(L_Speed, R_Speed);
    lastError = error;
    delay(50);
  } // End of yellow line While loop



} // End of line_Follow() function

*/
void ebreak(float delay_Time) { //forces the robot to stop moving when called
  
  // turn the motor speed to zero
  analogWrite(left_Motor_Enable, 0);
  analogWrite(right_Motor_Enable, 0);

  // turn the motors off
  digitalWrite(left_Motor_S1, HIGH);
  digitalWrite(left_Motor_S2, HIGH);
  digitalWrite(right_Motor_S1, HIGH);
  digitalWrite(right_Motor_S2, HIGH);


  delay(delay_Time);

}


void backward(float motor_Speed, float delay_Time) {

  analogWrite(left_Motor_Enable, motor_Speed);
  analogWrite(right_Motor_Enable, motor_Speed);

  digitalWrite(left_Motor_S1, HIGH);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, HIGH);
  digitalWrite(right_Motor_S2, LOW);

  int seconds = ceil(delay_Time * 1000);
  delay(seconds);

  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, LOW);


}

void forward(float motor_Speed, float delay_Time) {

  analogWrite(left_Motor_Enable, motor_Speed);
  analogWrite(right_Motor_Enable, motor_Speed);

  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, HIGH);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, HIGH);

  int seconds = ceil(delay_Time * 1000);
  delay(seconds);

  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, LOW);


}

void forwardS(float L_speed, float R_speed) {


  analogWrite(left_Motor_Enable, L_speed);
  analogWrite(right_Motor_Enable, R_speed);

  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, HIGH);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, HIGH);
  //  Serial.println(mySensorBar.getPosition());
  //  delay(20);



}


void DC_Motor_Encoder1() {


  Count_pulses1++;


}

////void DC_Motor_Encoder2(){
////
////
////    Count_pulses2++;
////
////
////  Serial.println(Count_pulses1+Count_pulses2);
////}



void turnLeft(float motor_Speed, float turn_Degrees) {

  analogWrite(left_Motor_Enable, motor_Speed);
  analogWrite(right_Motor_Enable, motor_Speed);

  Count_pulses1 = 0;

  //750 pulse ;=in a full rotaion
  int pulses = 3.9 * 760 * (turn_Degrees / 360); //16 is the number of pulses in a full rotaion when using the rising edge of ENCA
  // int pulses = ((turn_Degrees*160*16)/(67.5*3.1415*360*sqrt(2)));

  digitalWrite(left_Motor_S1, HIGH);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, HIGH);

  //while(abs(Count_pulses1 + Count_pulses2) < pulses)

  while (Count_pulses1 < pulses) { //comparing the number of pulses since the wheel started turning to the number of pulses needed to turn

    // 67.5mm diameter, 160 mm base
    
    if((mySensorBar.getDensity() >0 )and (mySensorBar.getPosition()==0) and (Count_pulses1 > (0.5*pulses))){
      break;
    }
    //number_of_encoder_ticks = (90 * wheel_base_distance * encoder_resolution) / (wheel_diameter * pi * 360 * sqrt(2))
    Serial.print(pulses);
    Serial.print(" , ");
    Serial.println(Count_pulses1);

  }

  ebreak(20);
  Count_pulses1 = 0;
  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, LOW);
  ebreak(20);

}

void turnRight(float motor_Speed, float turn_Degrees) {

  analogWrite(left_Motor_Enable, motor_Speed);
  analogWrite(right_Motor_Enable, motor_Speed);

  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, HIGH);
  digitalWrite(right_Motor_S1, HIGH);
  digitalWrite(right_Motor_S2, LOW);

  delay(1000);

  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, LOW);

}

void left(float motor_Speed, float time_delay){

  analogWrite(left_Motor_Enable, motor_Speed);
  analogWrite(right_Motor_Enable, motor_Speed);



  digitalWrite(left_Motor_S1, HIGH);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, HIGH);

  delay(time_delay*1000);
   digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, LOW);

  
}



void right(float motor_Speed, float time_delay){

  analogWrite(left_Motor_Enable, motor_Speed);
  analogWrite(right_Motor_Enable, motor_Speed);



  digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, HIGH);
  digitalWrite(right_Motor_S1, HIGH);
  digitalWrite(right_Motor_S2, LOW);

  delay(time_delay*1000);
   digitalWrite(left_Motor_S1, LOW);
  digitalWrite(left_Motor_S2, LOW);
  digitalWrite(right_Motor_S1, LOW);
  digitalWrite(right_Motor_S2, LOW);

  
}

void zipline() {

  //this will be the code for the zipline/canyon


}

void spinClock(int rotations) { //will spin the sign. it is the code for the celebration
  // by Haley Glenn

  for (int i = 0; i < (rotations*StepsPerRev); i++){
    
      CCW(A8,A9,A10,A15);
  }
}
void spinCounter(int rotations) { //will spin the sign. it is the code for the celebration
  // by Haley Glenn

  for (int i = 0; i < (rotations*StepsPerRev); i++){
    
      CW(A8,A9,A10,A15);
  }
}

void sendSignal(){
  digitalWrite(slavePin, HIGH);
  delay(100);
  digitalWrite(slavePin, LOW);


}
