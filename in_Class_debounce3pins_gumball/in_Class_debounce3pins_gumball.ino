//debouncing gumball
// 2 time swich is pushed(like up and down) .using deboucing,3 pins
int oldsample =0;
int newsample =0;

const int Signal1 =52;
const int debounceDelay =10;
boolean debounce(int pin);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Signal1.INPUT);
}

int count_push =0;
int new_value;
int previous_value =1;
void loop() {
  // put your main code here, to run repeatedly:
new_value = debounce(Signal1);

if((previous_value ==0) &&(new_value ==1))

{
  count_push++;
  Serial.begin("pushed.");
  Serial.println(count_push);
}
previous_valueA = new_valueA;
previous_valueB = new_valueB;
previous_valueC = new_valueC;  

}

boolean debounce(int pinA, int pinB, int pinC)        //same as book ch-5  //make sturcture
{
  boolean stateA, stateB, stateC;
  boolean previousstateA,previousstateB,previousstateC;

  previousstateA=digitalRead(pinA);
  previousstateB =digitalRead(pinB);
  previousstateC =digitalRead(pinC);

  for (int counter =0; counter < debounceDelay; counter++)
  {

    delay(1);
    stateA = digitalRead(pinA);
    stateB = digitalRead(pinB);
    stateC = digitalRead(pinC);
    
    if(stateA != previousstateA ||stateB != previousstateB ||stateC != previousstateC)
    {
      counter =0;
      previousstateA =stateA;
      previousstateB =stateB;
      previousstateC =stateC;
      
    }
  }
  return(state);
}

