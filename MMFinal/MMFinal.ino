/**
 * {
     A0 : 14
     A1 : 15
     A2 : 16
     A3 : 17
     A4 : 18
     A5 : 19
     A6 : 20
     A7 : 21
 }*/

// Pins
int pinsMotorRight[3] = {6, 7, 8}; // IN1, IN2, PWM
int pinsMotorLeft[3] = {4, 3, 2}; // IN1, IN2, PWM
int triggerPins[3] = {10, 18, 17}; // Left, Front, Right
int echoPins[3] = {9, 19, 16}; // Left, Front, Right
int stby = 5;
// Constants
int speed_ = 150;
int minDistance = 6;


class MicroMouse{

    public:
        //MotorA pins
        int RIN1;
        int RIN2;
        int Rpwm;
        //MotorB pins
        int LIN1;
        int LIN2;
        int Lpwm;
        // StandBy
        int stby;
        // Ultrasonic pins
        int triggerLeft;
        int triggerFront;
        int triggerRight;
        int echoLeft;
        int echoFront;
        int echoRight;
        // Other variables
        int leftDistance;
        int frontDistance;
        int rightDistance;
        int speed_;
        int minDistance;
        // Follow wall
        bool RightWall = false;
        bool LeftWall = false;


        /**
         * Setup speed
         * 
         * @param s : integer type [0-255]
         */
        void set_speed(int s){
            speed_ = s;
        }
        /**
        * Setup minimun distance
        *
        * @param dist : integer type
        */
        void setMinDistance(int dist){
            minDistance = dist;
        }
        /**
         * Setup the pins of the motors
         * 
         * @param pinsMotorRight : int array type [IN1, IN2, PWM]
         * @param pinsMotorLeft : int array type [IN1, IN2, PWM]
         */
        void setMotorPins(int *pinsMotorRight, int *pinsMotorLeft){
            RIN1 = pinsMotorRight[0];
            RIN2 = pinsMotorRight[1];
            Rpwm = pinsMotorRight[2];
            LIN1 = pinsMotorLeft[0];
            LIN2 = pinsMotorLeft[1];
            Lpwm = pinsMotorLeft[2];
        }
        /**
         * Setup stand by
         *
         * @param stPin : int type
         */
        void setSTBY(int stPin){
            stby = stPin;
        }
        /**
         * Setup ultrasonic pins
         * 
         * @param trigger : int array type [left, front, right]
         * @param echo : int array type [left, front right]
         */
        void setUltrasonicPins(int* trigger, int* echo){
            triggerLeft = trigger[0];
            triggerFront = trigger[1];
            triggerRight = trigger[2];
            echoLeft = echo[0];
            echoFront = echo[1];
            echoRight = echo[2];
        }
        /**
         * Initialize pins
         */
        void initPins(){
            pinMode(RIN1, OUTPUT);
            pinMode(RIN2, OUTPUT);
            pinMode(LIN1, OUTPUT);
            pinMode(LIN2, OUTPUT);

            pinMode(Rpwm, OUTPUT);
            pinMode(Lpwm, OUTPUT);
            pinMode(stby, OUTPUT);
            digitalWrite(stby, HIGH);

            pinMode(triggerLeft, OUTPUT);
            pinMode(triggerFront, OUTPUT);
            pinMode(triggerRight, OUTPUT);
            pinMode(echoLeft, INPUT);
            pinMode(echoFront, INPUT);
            pinMode(echoRight, INPUT);
        }
        /**
         * Read the distance between a sensor and 
         * the next proximity object
         * 
         * @param trigger : integer type.
         * @param echo : integer type.
         * 
         * @return an integer that represent the distance.
         */
        int readDistance(int trigger, int echo){
            digitalWrite(trigger, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigger, LOW);
            float t = pulseIn(echo, HIGH);
            return t / 59;
        }
        /**
         * Update each sensor's distance
         */
        void updateDistances(){
            leftDistance = readDistance(triggerLeft, echoLeft);
            frontDistance = readDistance(triggerFront, echoFront);
            rightDistance = readDistance(triggerRight, echoRight);
        }
        /**
         * Move Fordward
         */
        void moveFordward(){
            analogWrite(Rpwm, speed_);
            analogWrite(Lpwm, speed_);
            digitalWrite(RIN1, HIGH);
            digitalWrite(RIN2, LOW);
            digitalWrite(LIN1, HIGH);
            digitalWrite(LIN2, LOW);
        }
        /**
         * Move Backward
         */
        void moveBackward(){
            analogWrite(Rpwm, speed_);
            analogWrite(Lpwm, speed_);
            digitalWrite(RIN1, LOW);
            digitalWrite(RIN2, HIGH);
            digitalWrite(LIN1, LOW);
            digitalWrite(LIN2, HIGH);
        }
        /**
         * Move Left
         */
        void moveLeft(){
            analogWrite(Rpwm, speed_);
            analogWrite(Lpwm, speed_);
            digitalWrite(RIN1, HIGH);
            digitalWrite(RIN2, LOW);
            digitalWrite(LIN1, LOW);
            digitalWrite(LIN2, HIGH);
        }
        /**
         * Move Right
         */
        void moveRight(){
            analogWrite(Rpwm, speed_);
            analogWrite(Lpwm, speed_);
            digitalWrite(RIN1, LOW);
            digitalWrite(RIN2, HIGH);
            digitalWrite(LIN1, HIGH);
            digitalWrite(LIN2, LOW);
        }
        /**
         * Stop Mouse
         */
        void moveStop(){
            digitalWrite(RIN1, LOW);
            digitalWrite(RIN2, LOW);
            digitalWrite(LIN1, LOW);
            digitalWrite(LIN2, LOW);
        }
        /**
         * Turn around
         */
        void moveSpin(){
            for (int i; i<10; i++){
                moveRight();
            }
        }
        /**
        * Look up the next move
        */
        void nextMove(){
            if (frontDistance >= minDistance){
                moveFordward();
            }
            else if (rightDistance >= minDistance){
                moveRight();
            }
            else if (leftDistance >= minDistance){
                moveLeft();
            }
            else{
                moveRight();
            }
        }


        // Debug / Test Methods


        void setTestPins(int* pinsMotor, int stPin){
            LIN1 = pinsMotor[0];
            LIN2 = pinsMotor[1];
            Lpwm = pinsMotor[2];
            stby = stPin;
        }
        void initTestPins(){
            pinMode(LIN1, OUTPUT);
            pinMode(LIN2, OUTPUT);
            pinMode(Lpwm, OUTPUT);
            pinMode(stby, OUTPUT);
            digitalWrite(stby, HIGH);
        }
        void moveTest(){
            moveFordward();
            delay(1500);
            moveBackward();
            delay(1500);
        }
        void printDistances(){
            Serial.print(leftDistance);
            Serial.print(" ");
            Serial.print(frontDistance);
            Serial.print(" ");
            Serial.println(rightDistance);
        }
};

MicroMouse mouse;

void setup(){
    Serial.begin(9600);
    mouse.setMotorPins(pinsMotorRight,  pinsMotorLeft);
    mouse.setUltrasonicPins(triggerPins, echoPins);
    mouse.setSTBY(stby);
    mouse.setMinDistance(minDistance);
    mouse.set_speed(speed_);
    mouse.initPins();
}

void loop(){
    mouse.updateDistances();
    mouse.nextMove();
}
