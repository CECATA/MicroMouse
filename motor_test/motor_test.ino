// Motor A
int AIN1 = 1;
int AIN2 = 2;
int Apwm = 5;
// Motor B
int BIN1 = 3;
int BIN2 = 4;
int Bpwm = 6;

void setup()
{
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);

  pinMode(Apwm, OUTPUT);
  pinMode(Bpwm, OUTPUT);
}

void loop()
{
  move_wheel_front(AIN1, AIN2, Apwm, 250); //setup variables
}

void move_wheel_front(int pin1, int pin2, int pwm, int speed_)
{ /* pin1: Motor pin (IN) 1
     pin2: Motor pin (IN) 2
     pwm: Motor pwm
     speed_: Motor speed range(0, 255)
  */
  
  analogWrite(pwm, speed_);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}
