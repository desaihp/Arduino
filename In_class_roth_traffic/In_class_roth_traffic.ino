//trafic light_roth_C

#define RED 0
#define GREEN 1
#define YELLOW 2
#define WALK 3

struct outputs
{
  int A_red_light;
  int A_yellow_light;
  int A_green_light;
  int B_red_light;
  int B_yellow_light;
  int B_green_light;
};

struct inputs
{
  int reset;
  int Sta;
  int Stb;
};

String input_string;
char str_HEADER;
char str_reset;
char str_Sta;
char str_Stb;
int reset,Sta,Stb;

  struct inputs my_inputs;
  struct outputs my_outputs;


void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  //get inputs

if(Serial.available() >0)
{
  input_string = Serial.readStringUntil('\n');
  str_HEADER = input_string[0];
  str_reset = input_string[2];
  str_Sta = input_string[4];
  str_Stb = input_string[6];

  if(str_HEADER =='H')
  {
    my_inputs.reset =str_reset - '0';
    my_inputs.Sta = str_Sta - '0';
    my_inputs.Stb = str_Stb -'0';

    Serial.print("RECEIVED: ");
    Serial.println(input_string);
    Serial.print("reset = ");
    Serial.println(reset);
    Serial.print("Sta = ");
    Serial.println(Sta);
    Serial.print("Stb = ");
    Serial.println(Stb);            
  
   }
  
}

//get next State

 traffic_light(&my_inputs,&my_outputs);

//send outputs
Serial.print("I,");
Serial.print(my_outputs.A_red_light);
Serial.print(",");
Serial.print(my_outputs.A_yellow_light);
Serial.print(",");
Serial.print(my_outputs.A_green_light);
Serial.print(",");
Serial.print(my_outputs.B_red_light);
Serial.print(",");
Serial.print(my_outputs.B_yellow_light);
Serial.print(",");
Serial.print(my_outputs.B_green_light);
Serial.print(",");
   delay(500);
   
}

void traffic_light(struct inputs *in, struct outputs *out)
{
  static int ps;
  static int ns = 100;


  //Update Present State
  ps = ns;

  printf("DEBUG: ps = %d\n", ps);
  //Calculate Next State
  switch (ps)
  {
  case (100): if (in->reset == 1)
    ns = 100;
        else
          ns = 0;

    out->A_red_light = 1;
    out->A_yellow_light = 0;
    out->A_green_light = 0;
//    out->A_walk_light = 1;
    out->B_red_light = 1;
    out->B_yellow_light = 0;
    out->B_green_light = 0;
   // out->B_walk_light = 0;
    break;

  case (0):   ns = 1;

    out->A_red_light = 0;
    out->A_yellow_light = 0;
    out->A_green_light = 1;
//    out->A_walk_light = 1;
    out->B_red_light = 1;
    out->B_yellow_light = 0;
    out->B_green_light = 0;
  //  out->B_walk_light = 0;
    break;

  case (1):   ns = 2;
    break;

  case (2):   ns = 3;
    break;

  case (3):   ns = 4;
    break;

  case (4):   ns = 5;
    break;

  case (5):   if (in->Stb == 0)
    ns = 5;
        else
          ns = 6;
    break;

  case (6):   ns = 7;

    out->A_red_light = 0;
    out->A_yellow_light = 1;
    out->A_green_light = 0;
//    out->A_walk_light = 1;
    out->B_red_light = 1;
    out->B_yellow_light = 0;
    out->B_green_light = 0;
   // out->B_walk_light = 0;
    break;

  case (7):   ns = 8;

    out->A_red_light = 1;
    out->A_yellow_light = 0;
    out->A_green_light = 0;
//    out->A_walk_light = 0;
    out->B_red_light = 0;
    out->B_yellow_light = 0;
    out->B_green_light = 1;
//    out->B_walk_light = 1;
    break;

  case (8):   ns = 9;
    break;

  case (9):   ns = 10;
    break;

  case (10):  ns = 11;
    break;

  case (11): if((in->Sta == 0) && (in->Stb == 1))

    ns = 11;
         else
           ns = 12;
    break;

  case (12):  ns = 0;

    out->A_red_light = 1;
    out->A_yellow_light = 0;
    out->A_green_light = 0;
//    out->A_walk_light = 0;
    out->B_red_light = 0;
    out->B_yellow_light = 1;
    out->B_green_light = 0;
//    out->B_walk_light = 1;
    break;

  

}
}
