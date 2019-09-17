int trig_left = 1;
int echo_left = 2;
int trig_right = 3;
int echo_right = 4;
int trig_front = 5;
int echo_front = 6;

void setup()
{
    Serial.begin(9600);
    pinMode(trig_left, OUTPUT);
    pinMode(echo_left, INPUT);
    pinMode(trig_right, OUTPUT);
    pinMode(echo_right, INPUT);
    pinMode(trig_front, OUTPUT);
    pinMode(echo_front, INPUT);
}

void loop()
{
  int distance = read_distance(trig_left, echo_left);
  Serial.print(distance);
  Serial.print(" cm");
  Serial.println();
}

float read_distance(int trigger, int echo)
{
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float t = digitalRead(echo);
  return t / 59;
}
