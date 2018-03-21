//Generate and Sample 10hz Signal

int out_10hz = 44;
int in_10hz = 45;

void setup()
{
  pinMode(out_10hz, OUTPUT);
  pinMode(in_10hz, INPUT);

  Serial.begin(115200);  
}

int out_10hz_value;
int in_10hz_value;

void loop()
{
  out_10hz_value = 1;
  digitalWrite(out_10hz, out_10hz_value);
     
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
     
  out_10hz_value = LOW;
  digitalWrite(out_10hz,out_10hz_value);
    
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
  sample_10hz();
  delay (10); //10 ms
  
  
}

void sample_10hz()
{
  in_10hz_value = digitalRead(in_10hz);
  Serial.print("H");
  Serial.print(",");
  Serial.print(out_10hz_value);
  Serial.print(",");
  Serial.print(in_10hz_value);
  Serial.print(",");
  Serial.println();
}
