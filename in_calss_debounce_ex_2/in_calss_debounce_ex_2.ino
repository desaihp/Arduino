//debouncing
// 2 time swich is pushed(like up and down) .using deboucing,2 pins
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
previous_value = new_value;  

}

boolean debounce(int pin)        //same as book ch-5
{
  boolean state;
  boolean previousstate;

  previousstate =digitalRead(pin);

  for (int counter =0; counter < debounceDelay; counter++)
  {

    delay(1);
    state = digitalRead(pin);
    if(state != previousstate)
    {
      counter =0;
      previousstate =state;
      
    }
  }
  return(state);
}

