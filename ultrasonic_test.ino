int trig = 1;
int echo = 2;

void setup()
{
    Serial.begin(9600);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void loop()
{
}

int read_distance(int trig, int echo)
{
}