#define dirPin 2 //the state of this pin determines the direction that the stepper motor will move in
#define stepPin 3 //cycling this pin will cause the motor to step
#define goPin 5 //this pin is connected to a switch and pulldown resistor, used to signal if movement is currently required or not
#define GCpin 6 //connected to the event port of the GC, currently configured for Agilent GCs

//these variables that will need to be set when modulator is first constructed
const float delta = 0.0000212; //declaring variable for clock drift adjustment, update this if you know the drift on your MPU clock, set to 1 if not.
const int stepsPerRotation = 400;  // declaring number of steps per rotation, this is inherent in the stepper motor that is used in construction
const float rotations = 1;  //declaring number of rotations required to move modulator desired distance, this will depend on the distance you want to move your CTE and the radius of your stepper motor sprocket
const int speed = 230;  //microsecond delay for motor steps, try increasing this number if theres too much friction for the modulator to move



//these variables should be left alone
int count = 0;  //declaring step counter
const int steps = (rotations * stepsPerRotation);  // calculate number of steps for each movement
unsigned long modStart = 0;  //declaring start time variable
bool upPos = true;  //declaring modulator starting position as "up"
bool first = 1; //declaring variable for identifying if a modulation is the first one for an analysis or not
bool go = false;

//these variables are your modulation period and desorption time in microseconds, change these to suit your analysis
cosnt unsigned long modulationPeriod = 6000000 * delta;  //declaring desired modulation period in us, adjusted for clock drift
const unsigned long desorpTime = 2000000 * delta;  //declaring desorption time in us, adjusted for clock drift

void setup() {
  Serial.begin(115200);
  // Declare stepper control pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  // Declare the two different pins that can signal the modulator to begin modulating as input
  pinMode(goPin, INPUT);
  pinMode(GCpin, INPUT);
}
  


void loop() {
  if (go){ //  check if go variable is true
      if(upPos == true ){  //if modulator is in the up position do this chunk
          if (first == 1){ //check if this it the first iteration of the loop take micros reading if it is, then turn off first mod indicator
            modStart = (micros() - (modulationPeriod - desorpTime));
            first = 0;
            digitalWrite(dirPin, HIGH);  //move the modulator
                for(count = 0; count <= steps; count++ ){
                    digitalWrite(stepPin, HIGH);
                    delayMicroseconds(speed);
                    digitalWrite(stepPin, LOW);
                    delayMicroseconds(speed);
                    };
            upPos = false;  //after moving modulator, cycle the bool variable for position
          }
          else if(micros() - modStart >= (modulationPeriod - desorpTime)){  //if statement to check how long has elapsed since the start of the modulation period and if that is equal to or greater than the accumulation time
              digitalWrite(dirPin, HIGH);  //move the modulator
              for(count = 0; count <= steps; count++ ){
                  digitalWrite(stepPin, HIGH);
                  delayMicroseconds(speed);
                  digitalWrite(stepPin, LOW);
                  delayMicroseconds(speed);
                  };
              upPos = false;  //after moving modulator, cycle the bool variable for position
          };
      };
  };
  if (upPos == false){  //if the modulator is in the down position, do this chunk
    if(micros() - modStart >= modulationPeriod){  //if statement to check if modulation period is over, if so, move back to the starting position
        digitalWrite(dirPin, LOW);
        for(count = 0; count <= steps; count++ ){
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(speed);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(speed);
        };
        //once back at the starting postion, cycle upPos bool var back to 1 and set modStart to the time the next mod period is expected to start at
        upPos = true;
        modStart += (modulationPeriod);
        if (digitalRead(goPin) || digitalRead(GCpin)){
          go = true;
        }
        else {
          go = false;
          first = 1;
        };
    };
  }
  else { //check if GC or manual switch are signaling that modulation should be active
      if (digitalRead(goPin) || digitalRead(GCpin)){
        go = true;
      }
      else {
        go = false; 
        first = 1;
      };
  };
};
