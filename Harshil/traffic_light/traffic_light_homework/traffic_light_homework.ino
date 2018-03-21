// Read Line from Serial Port


#define RED 0
#define GREEN 1
#define YELLOW 2
#define WALK 3

struct outputs
{
  int A_red_light;
  int A_yellow_light;
  int A_green_light;
  int A_walk_light;
  int B_red_light;
  int B_yellow_light;
  int B_green_light;
  int B_walk_light;
};

struct inputs
{
  int reset;
  int Sta;
  int Stb;
};


int reset, Sta, Stb;

struct inputs my_inputs;
struct outputs my_outputs;
struct outputs old_outputs;

int ENABLE_RECEIVE = 0;
int ENABLE_TRANSMIT = 0;
int COMM_SYNCED = 0;
int DEBUG = 0;

void get_inputs(struct inputs *in);
void transmit_outputs(struct outputs *out);
void traffic_light(struct inputs *in, struct outputs *out);

void setup()
{
  
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  my_inputs.reset = 1;
  my_inputs.Sta = 0;
  my_inputs.Stb = 0;
  
  old_outputs.A_red_light = 0;
  old_outputs.A_yellow_light = 0;
  old_outputs.A_green_light = 0;
  old_outputs.A_walk_light = 0;
  old_outputs.B_red_light = 0;
  old_outputs.B_yellow_light = 0;
  old_outputs.B_green_light = 0;
  old_outputs.B_walk_light =0;
  
}

void loop()
{
  digitalWrite(13,COMM_SYNCED);
  
  if (COMM_SYNCED)
  {
    get_inputs(&my_inputs);
    traffic_light(&my_inputs, &my_outputs);
    transmit_outputs(&my_outputs,&old_outputs);
    delay(1000); 
  }
  else
  {
    link_sync();
    delay(500);
  }
 
}

void link_sync()
{
  String sync_string;

    if (Serial.available() >0)
    {
      sync_string = Serial.readStringUntil('\n');
      
      if (sync_string.equals("SYNC") )
      {
        COMM_SYNCED = 1;
        ENABLE_RECEIVE = 1;
        ENABLE_TRANSMIT = 1;
        Serial.println("#STATUS -- RECEIVED SYNC");
        Serial.println("#STATUS -- WAITING FOR INPUT");
      }
    }
}

void get_inputs(struct inputs *in)
{
  char str_HEADER;
  char str_reset;
  char str_Sta;
  char str_Stb;
  String input_string;
  String input_header;

  if (ENABLE_RECEIVE)
  {
    if (Serial.available() >0)
    {
      input_string = Serial.readStringUntil('\n');
      
      str_HEADER = input_string[0];
      str_reset = input_string[6];
      str_Sta = input_string[8];
      str_Stb = input_string[10];
      
      input_header = input_string.substring(0,5);
      
      if (DEBUG = 1)
      {
        Serial.print("#DEBUG: ");
        Serial.print(input_header);
        Serial.print(" -- reset = ");
        Serial.print(str_reset);
        Serial.print(" Sta = ");
        Serial.print(str_Sta);
        Serial.print(" Stb = ");
        Serial.print(str_Stb);
                    
      }
      
 
      if (input_header.equals("INPUT"))
      {
        in->reset = str_reset - '0';
        in->Sta = str_Sta - '0';
        in->Stb = str_Stb - '0';
              
        Serial.println("#STATUS -- RECEIVED INPUT");
      }

    } //DATA AVAILABLE

  } //ENABLE_RECEIVE
}

void transmit_outputs(struct outputs *out, struct outputs *old)
{
  
  if (ENABLE_RECEIVE && ENABLE_TRANSMIT)
  {
    if ( (old->A_red_light != out->A_red_light) ||
         (old->A_yellow_light != out->A_yellow_light) ||
         (old->A_green_light != out->A_green_light) ||
         (old->A_walk_light != out->A_walk_light) ||
         (old->B_red_light != out->B_red_light) ||
         (old->B_yellow_light != out->B_yellow_light) ||
         (old->B_green_light != out->B_green_light)||
         (old->B_walk_light != out->B_walk_light)
         )
  
    {  
      Serial.print("OUTPUT,");
      Serial.print(out->A_red_light);
      Serial.print(",");
      Serial.print(out->A_yellow_light);
      Serial.print(",");
      Serial.print(out->A_green_light);
      Serial.print(",");
      Serial.print(out->A_walk_light);
      Serial.print(",");
      Serial.print(out->B_red_light);
      Serial.print(",");
      Serial.print(out->B_yellow_light);
      Serial.print(",");
      Serial.print(out->B_green_light);
      Serial.print(",");
      Serial.print(out->B_walk_light);
      Serial.println(",");
     
    if(DEBUG = 1)
      {
        Serial.print("#DEBUG: OUTPUT,");
        Serial.print(out->A_red_light);
        Serial.print(",");
        Serial.print(out->A_yellow_light);
        Serial.print(",");
        Serial.print(out->A_green_light);
        Serial.print(",");
        Serial.print(out->A_walk_light);
        Serial.print(",");
        Serial.print(out->B_red_light);
        Serial.print(",");
        Serial.print(out->B_yellow_light);
        Serial.print(",");
        Serial.print(out->B_green_light);
        Serial.print(",");
        Serial.print(out->B_walk_light);
        Serial.println(",");
      }
      
      old->A_red_light = out->A_red_light;
      old->A_yellow_light = out->A_yellow_light;
      old->A_green_light = out->A_green_light;
      old->A_walk_light = out->A_walk_light;
      old->B_red_light = out->B_red_light;
      old->B_yellow_light = out->B_yellow_light;
      old->B_green_light = out->B_green_light;
      old->B_walk_light = out->B_walk_light;
    }
  }
  
  
}


void traffic_light(struct inputs *in, struct outputs *out)
{
  static int ps;
  static int ns = 100;

  //Update Present State
  ps = ns;

//printf("DEBUG: ps = %d\n",ps);
  //Calculate Next State
  switch (ps)
  {
   case (100) : if (in->reset == 1)
                  ns = 100;
                else
                  ns = 0;

                out->A_red_light = 1;
                out->A_yellow_light = 0;
                out->A_green_light = 0;
                out->A_walk_light = 1;
                out->B_red_light = 1;
                out->B_yellow_light = 0;
                out->B_green_light = 0;
                out->B_walk_light =0;
                break;

   case (0) :  ns = 1;
                out->A_red_light = 0;
                out->A_yellow_light = 0;
                out->A_green_light = 1;
                out->A_walk_light = 1;
                out->B_red_light = 1;
                out->B_yellow_light = 0;
                out->B_green_light = 0;
                out->B_walk_light = 0;
                break;

   case (1) :  ns = 2;
                break;

   case (2) :  ns = 3;
                break;

   case (3) :  ns = 4;
                break;

   case (4) :  ns = 5;
                break;

   case (5) :  if (in->Stb == 0)
                 ns = 5;
               else
                 ns = 6;
                break;

   case (6) :  ns = 7;
                out->A_red_light = 0;
                out->A_yellow_light = 1;
                out->A_green_light = 0;
                out->A_walk_light = 1;
                out->B_red_light = 1;
                out->B_yellow_light = 0;
                out->B_green_light = 0;
                out->B_walk_light = 0;
                break;

   case (7) :  ns = 8;
                out->A_red_light = 1;
                out->A_yellow_light = 0;
                out->A_green_light = 0;
                out->A_walk_light = 0;
                out->B_red_light = 0;
                out->B_yellow_light = 0;
                out->B_green_light = 1;
                out->B_walk_light = 1;
                break;

   case (8) :  ns = 9;
                break;

   case (9) :  ns = 10;
                break;
  case (10) :  ns = 11;
                break;

   case (11) : if ((in->Sta == 0) && (in->Stb==1))
                 ns = 11;
               else
                 ns = 12;
               break;

   case (12) :  ns = 0;
                out->A_red_light = 1;
                out->A_yellow_light = 0;
                out->A_green_light = 0;
                out->A_walk_light = 0;
                out->B_red_light = 0;
                out->B_yellow_light = 1;
                out->B_green_light = 0;
                out->B_walk_light = 1;
                break;
  }

}




