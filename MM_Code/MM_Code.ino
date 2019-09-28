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
{/*
  "The function return a float distance"
    trigger: Ultrasonic's trigger pin
    echo: Ultrasonic's echo pin
  */
}
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float t = pulseIn(echo, HIGH);
  return t / 59;
}

void move_wheel_front(int pin1, int pin2, int pwm, int speed_)
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
