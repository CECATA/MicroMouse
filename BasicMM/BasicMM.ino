// Ultrasonic pins
#define trig_left A2
#define echo_left A3
#define trig_right A4
#define echo_right A5
#define trig_front A0
#define echo_front A1

//MotorA pins > RIGHT MOTOR
#define AIN1 4
#define AIN2 3
int Apwm = 2; //start motorA speed
//MotorB pins > LEFT MOTOR
#define BIN1 5
#define BIN2 6
int Bpwm = 7; //start motorB speed

// Setup start variables and arrays
const int min_distance = 8;
const int max_distance = 15;
const int factor = 1.2;
float distances[3] = {10, 10, 10}; //{left_distance, right_distance, left_distance}
int side_vector[2] = {0, 0}; // {0-1}
int front_ = 0; // 0-1
int speed_A = 150;
int speed_B = 150;
int standard_speed = 150;

void setup(){
  Serial.begin(9600);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);

  pinMode(Apwm, OUTPUT);
  pinMode(Bpwm, OUTPUT);

  pinMode(trig_left, OUTPUT);
  pinMode(echo_left, INPUT);
  pinMode(trig_right, OUTPUT);
  pinMode(echo_right, INPUT);
  pinMode(trig_front, OUTPUT);
  pinMode(echo_front, INPUT);
}

void loop(){

  update_distance(distances);
  update_move(distances, side_vector, front_, min_distance, max_distance, speed_A, speed_B, standard_speed);
  /*if (distances[1]>=min_distance){
    move_wheel(AIN1, AIN2, Apwm, speed_A);
    move_wheel(BIN1, BIN2, Bpwm, speed_B);
  }else if ((distances[1]<min_distance) && (distances[0]>=min_distance)){
    move_wheel(AIN1, AIN2, Apwm, speed_A);
    move_wheel(BIN2, BIN1, Bpwm, speed_B); delay(100);
  }*/
  Serial.print(distances[0]);
  Serial.print(" ");
  Serial.print(distances[1]);
  Serial.print(" ");
  Serial.println(distances[2]);
  
}


void move_wheel(int pin1, int pin2, int pwm, int speed_){
  /*
  "Move a wheel to front with a specific speed" 
    pin1: Motor pin (IN) 1
    pin2: Motor pin (IN) 2
    pwm: Motor pwm
    speed_: Motor speed range(-255, 255)
  */
  analogWrite(pwm, speed_);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}


void update_distance(float* distances){
  /*
   "Update the distances for each sensor to a close object"
   distances: a distance array where {left_distance, front_distance, right_distance}
  */
   distances[0] = read_distance(trig_left, echo_left);
   distances[1] = read_distance(trig_front, echo_front);
   distances[2] = read_distance(trig_right, echo_right);
}

float read_distance(int trigger, int echo){
  /*
  "The function return a float distance"
    trigger: Ultrasonic's trigger pin
    echo: Ultrasonic's echo pin
  */
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float t = pulseIn(echo, HIGH);
  return t / 59;
}

int test_move(int speed1, int speed2){
  speed1 = 200;
  speed2 = 200;
  Serial.print("Algo2");
  return speed1, speed2;
}

void update_move(float* distance, int* side_vector, int front_, int min_, int max_, int speed_A, int speed_B, int stSpeed){
  /*
   * distances: a distance array where {left_distance, front_distance, right_distance}
   * side_vector: array {-1, 1}
   * front_: float -1,1
   * min_: minimun distance
   * max_: maximun distance
   * stSpeed: standard speed
   */
   //Case 1: left and right wall
  if ((distance[0]<=min_)&&(distance[1]>=min_)&&(distance[2]<=min_)){
    // >> Move forward
    move_wheel(AIN1, AIN2, Apwm, speed_A);
    move_wheel(BIN1, BIN2, Bpwm, speed_B);
  }// Case 2: left and front wall
  else if ((distance[0]<=min_)&&(distance[1]<=min_)&&(distance[2]>=min_)){
    // >> Move right
    move_wheel(AIN2, AIN1, Apwm, speed_A);
    move_wheel(BIN1, BIN2, Bpwm, speed_B);
  }// Case 3: front and right wall
  else if ((distance[0]>=min_)&&(distance[1]<=min_)&&(distance[2]<=min_)){
    // >> Move left
    move_wheel(AIN1, AIN2, Apwm, speed_A);
    move_wheel(BIN2, BIN1, Bpwm, speed_B);
  }// Case 4: front wall
  else if ((distance[0]>=min_)&&(distance[1]<=min_)&&(distance[2]>=min_)){
    // >> This could be random, move right
    move_wheel(AIN2, AIN1, Apwm, speed_A);
    move_wheel(BIN1, BIN2, Bpwm, speed_B);
  }// Case 5: left, front, right wall
  /*else if ((distance[0]<=min_)&&(distance[1]<=min_)&&(distance[2]<=min_)){
    // Spin until can go forward
    while (distance[1]<=min_){
      move_wheel(AIN2, AIN1, Apwm, speed_A);
      move_wheel(BIN1, BIN2, Bpwm, speed_B);
    }
  }*/
}

float scale_factor(int distance, int min_, int max_, int a, int b){
  /*
   * Return a float factor between a and b
   * distance: distance value (ultrasonic sensor)
   */
   return (b - a) * ((distance - min_) / (max_ - min_)) - a;
}
