// Ultrasonic pins
#define trig_left 9
#define echo_left 8
#define trig_right A5
#define echo_right A4
#define trig_front A7
#define echo_front A6

//MotorA pins > RIGHT MOTOR
#define AIN1 4
#define AIN2 3
int Apwm = 2; //start motorA speed
//MotorB pins > LEFT MOTOR
#define BIN1 5
#define BIN2 6
int Bpwm = 7; //start motorB speed


//setup start variables
const int min_distance = 10; //cm
const int stdSpeed = 70; //Motors speed
int distances[3] = {10, 10 ,10};

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


void move_forward(int speed_){
  analogWrite(Apwm, speed_);
  analogWrite(Bpwm, speed_);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void move_right(int speed_){
  analogWrite(Apwm, speed_);
  analogWrite(Bpwm, speed_);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void move_left(int speed_){
  analogWrite(Apwm, speed_);
  analogWrite(Bpwm, speed_);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void move_backward(int speed_){
  analogWrite(Apwm, speed_);
  analogWrite(Bpwm, speed_);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

int read_distance(int trigger, int echo){
  /*
  trigger: trigger pin (UltraSonic)
  echo: echo pin (UltraSonic)
  */
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float time_ = pulseIn(echo, HIGH);
  return time_ /59;
}

void update_distances(int* distances){
  /*
  distances: array shape=(1, 3) where {left, front, right}
  */
  distances[0] = read_distance(trig_left, echo_left);
  distances[1] = read_distance(trig_front, echo_front );
  distances[2] = read_distance(trig_right, echo_right);
}

void check_move(int speed_){
  // Go forward if not obstacule in front
  if (distances[1] > min_distance){
    move_forward(speed_);
  }else{
   // If obstacule in front => check sides
      if (distances[0] > min_distance){
          move_left(speed_);   
      }else if (distances[2] > min_distance){
          move_right(speed_);
      }else{
          move_backward(speed_);
      }
  }
}


void loop(){
  update_distances(distances);
  Serial.print(distances[0]);
  Serial.print(" ");
  Serial.print(distances[1]);
  Serial.print(" ");
  Serial.print(distances[2]);
  Serial.println();
  move_forward(stdSpeed);
  //update_distances(distances);
  //check_move(stdSpeed);
}


