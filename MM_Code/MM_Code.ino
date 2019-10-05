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
int Apwm = 250; //start motorA speed
//MotorB pins
#define BIN1 9
#define BIN2 10
int Bpwm = 250; //start motorB speed

// Setup start variables and arrays
const int min_distance = 3;
int distances[3] = {10, 10, 10}; //{left_distance, right_distance, left_distance}
float move_vector[3] = {0, 0, 0}; // {0-1}


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



void update_distance(int* distances)
{
  /*
   "Update the distances for each sensor to a close object"
   distances: a distance array where {left_distance, front_distance, right_distance}
  */
   distances[0] = read_distance(trig_left, echo_left);
   distances[1] = read_distance(trig_front, echo_front);
   distances[2] = read_distance(trig_right, echo_right);
}


void check_move(int* distances, int* move_vector, int minimun_distance)
{
  for(int i=0; i<3; i++)
  {
    if(distances[i]<=min_distance)
    {
      move_vector[i] = 1;
    }
    else
    {
      move_vector[i] = 0;
    }
  }
}
