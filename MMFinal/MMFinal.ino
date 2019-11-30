// Pins
int pinsMotorA[3] = {};
int pinsMotorB[3] = {};
int triggerPins[3] = {6, 3, 19};
int echoPins[3] = {5, 2, 18};
// Constants
int speed_;
int minDistance;

class MicroMouse;
class Node;


class MicroMouse{

    public:
        //MotorA pins
        int AIN1;
        int AIN2;
        int Apwm;
        //MotorB pins
        int BIN1;
        int BIN2;
        int Bpwm;
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

        void setTestPins(int trigger, int echo){
            triggerRight = trigger;
            echoRight = echo;
        }
        void setTest(){
            pinMode(triggerRight, OUTPUT);
            pinMode(echoRight, INPUT);
        }
        /**
         * Setup speed
         * 
         * @param speed_ : integer type [0-250]
         */
        void setSpeed(int speed_){
            speed_ = speed_;
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
         * Setup the pins of the motor
         * 
         * @param pinsA : int array type [IN1, IN2, PWM]
         * @param pinsB : int array type [IN1, IN2, PWM]
         */
        void setMotorPins(int *pinsA, int *pinsB){
            AIN1 = pinsA[0];
            AIN2 = pinsA[1];
            Apwm = pinsA[2];
            BIN1 = pinsB[0];
            BIN2 = pinsB[1];
            Bpwm = pinsB[2];
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
            /*pinMode(AIN1, OUTPUT);
            pinMode(AIN2, OUTPUT);
            pinMode(BIN1, OUTPUT);
            pinMode(BIN2, OUTPUT);

            pinMode(Apwm, OUTPUT);
            pinMode(Bpwm, OUTPUT);*/

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
         * Move single wheel
         *
         * @param side : char type. Where "r"==Right, "l"==Left
         */
        void moveWheel(char side){
            if (side=="r"){
                analogWrite(Apwm, speed_);
                digitalWrite(AIN1, HIGH);
                digitalWrite(AIN2, LOW);
            }
            else if (side=="l"){
                analogWrite(Bpwm, speed_);
                digitalWrite(BIN1,HIGH);
                digitalWrite(BIN2, LOW);
            }
        }
        /**
         * Move Fordward
         */
        void moveFordward(){
            analogWrite(Apwm, speed_);
            analogWrite(Bpwm, speed_);
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            digitalWrite(BIN1, HIGH);
            digitalWrite(BIN2, LOW);
        }
        /**
         * Move Backward
         */
        void moveBackward(){
            analogWrite(Apwm, speed_);
            analogWrite(Bpwm, speed_);
            digitalWrite(AIN1, LOW);
            digitalWrite(AIN2, HIGH);
            digitalWrite(BIN1, LOW);
            digitalWrite(BIN2, HIGH);
        }
        /**
         * Move Left
         */
        void moveLeft(){
            analogWrite(Apwm, speed_);
            analogWrite(Bpwm, speed_);
            digitalWrite(AIN1, HIGH);
            digitalWrite(AIN2, LOW);
            digitalWrite(BIN1, LOW);
            digitalWrite(BIN2, HIGH);
        }
        /**
         * Move Right
         */
        void moveRight(){
            analogWrite(Apwm, speed_);
            analogWrite(Bpwm, speed_);
            digitalWrite(AIN1, LOW);
            digitalWrite(AIN2, HIGH);
            digitalWrite(BIN1, HIGH);
            digitalWrite(BIN2, LOW);
        }
        void moveStop(){
            digitalWrite(AIN1, LOW);
            digitalWrite(AIN2, LOW);
            digitalWrite(BIN1, LOW);
            digitalWrite(BIN2, LOW);
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
};

MicroMouse mouse;

void setup(){
    Serial.begin(9600);
    mouse.setUltrasonicPins(triggerPins, echoPins);
    mouse.initPins();
}

void loop(){
    mouse.moveFordward()
    // mouse.updateDistances();
    // int lDistance = mouse.leftDistance;
    // int fDistance = mouse.frontDistance;
    // int rDistance = mouse.rightDistance;
}
