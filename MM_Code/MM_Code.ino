// Ultrasonic pins
#define trig_left 1
#define echo_left 2
#define trig_right 3
#define echo_right 4
#define trig_front 5
#define echo_front 6

//MotorA pins
#define AIN1 7
#define AIN2 8
int Apwm = 11; //start motorA speed
//MotorB pins
#define BIN1 9
#define BIN2 10
int Bpwm = 12; //start motorB speed

// Setup start variables and arrays
const int min_distance = 3;
const int max_distance = 15;
const int factor = 1.2;
float distances[3] = {10, 10, 10}; //{left_distance, right_distance, left_distance}
float side_vector[2] = {0, 0}; // {0-1}
float front_ = 0; // 0-1
int speed_A = 150;
int speed_B = 150;
void setup()
{
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

void loop()
{
  move_forward(AIN1, AIN2, Apwm, speed_A);
  move_forward(BIN1, BIN2, Bpwm, speed_B);
  update_distance(distances);
  update_moves(distances, side_vector, front_, min_distance, max_distance, min_distance);
  
}


void move_forward(int pin1, int pin2, int pwm, int speed_)
{ /*
  "Move a wheel to front with a specific speed" 
    pin1: Motor pin (IN) 1
    pin2: Motor pin (IN) 2
    pwm: Motor pwm
    speed_: Motor speed range(0, 255)
  */

  analogWrite(pwm, speed_);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void move_backward(int pin1, int pin2, int pwm, int speed_)
{ /*
  "Move a wheel to front with a specific speed" 
    pin1: Motor pin (IN) 1
    pin2: Motor pin (IN) 2
    pwm: Motor pwm
    speed_: Motor speed range(0, 255)
  */

  analogWrite(pwm, speed_);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}



void update_distance(float* distances)
{
  /*
   "Update the distances for each sensor to a close object"
   distances: a distance array where {left_distance, front_distance, right_distance}
  */
   distances[0] = read_distance(trig_left, echo_left);
   distances[1] = read_distance(trig_front, echo_front);
   distances[2] = read_distance(trig_right, echo_right);
}

float read_distance(int trigger, int echo)
{ /*
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

void update_moves(float* distances, float* side_vector, float front_, int minimun_distance, int max_, int min_){
  /*
   * distances: a distance array where {left_distance, front_distance, right_distance}
   * side_vector: array {-1, 1}
   * front_: float -1,1
   * minimun_distance: int to change the state value of each element in side_vector
   */
  int iter[2] = {0, 2};
  for(int i=0; i<2; i++){
    side_vector[i] = scale_factor(distances[iter[i]], max_, min_, -1, 0);
  }

}

float scale_factor(int distance, int max_, int min_, int a, int b){
  /*
   * Return a float factor between a and b
   * distance: distance value (ultrasonic sensor)
   */
   return (b - a) * ((distance - min_) / (max_ - min_)) - a;
}
