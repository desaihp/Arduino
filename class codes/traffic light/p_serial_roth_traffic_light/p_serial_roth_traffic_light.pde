// Transmit and Receive Line of Data from Serial Port

import processing.serial.*;

Serial myPort;

int portIndex = 0;
short LF = 10;
int SYNC = 0;
int clk = 0;

int old_reset = 0;
int old_Sta = 0;
int old_Stb = 0;

int reset;
int Sta;
int Stb;

int A_red_light;
int A_yellow_light;
int A_green_light;
int B_red_light;
int B_yellow_light;
int B_green_light;

class struct_outputs
{
  public int A_red_light;
  public int A_yellow_light;
  public int A_green_light;
  public int B_red_light;
  public int B_yellow_light;
  public int B_green_light;
};

class struct_inputs
{
  public int reset;
  public int Sta;
  public int Stb;
};
  
 struct_outputs my_outputs;
 //struct_inputs my_inputs;

void setup()
{
  size(700,700);
  printArray(Serial.list());
  println("Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex],115200);
  
  fill(#000000);
  rect(100,100,200,400);
  rect(400,100,200,400);
  
  fill(#CCFFAA);
  fill(#FF0000);
  ellipse(200,200,100,100);
  
  fill(#FFFF00);
  ellipse(200,300,100,100);
  
  fill(#00FF00);
  ellipse(200,400,100,100);
  
  fill(#FF0000);
  ellipse(500,200,100,100);
  fill(#FFFF00);
  ellipse(500,300,100,100);
  fill(#00FF00);
  ellipse(500,400,100,100);  
  
  fill(#000000);
  textSize(32);
  text("Light A",150,50);
  text("Light B",450,50);
  
}  
  
void draw()
{
  int i;
  String test1;
  
  if (SYNC == 0)
  {
    myPort.write('\n');
    myPort.write('\n');
    myPort.write("SYNC\n");
    SYNC = 1;
  }
  else
  {
    generate_inputs();
    transmit_inputs();
    update_lights();
  }
   
  delay(1000);
}


void update_lights()
{
  
  if (A_red_light == 1)
    fill(#FF0000);
  else
    fill(#000000);
  ellipse(200,200,100,100);
  
  if (A_yellow_light == 1)
    fill(#FFFF00);
  else
    fill(#000000);
  ellipse(200,300,100,100);
  
  if (A_green_light == 1)
    fill(#00FF00);
  else
    fill(#000000);
  ellipse(200,400,100,100);
  
  if (B_red_light == 1)
    fill(#FF0000);
  else
    fill(#000000);
  ellipse(500,200,100,100);
  
  if (B_yellow_light == 1)
    fill(#FFFF00);
  else
    fill(#000000);
  ellipse(500,300,100,100);
  
  if (B_green_light == 1)
    fill(#00FF00);
  else
    fill(#000000); 
  ellipse(500,400,100,100);
    
}





void transmit_inputs()
{
  if ( (reset != old_reset) || 
       (Sta != old_Sta) ||
       (Stb != old_Stb) )
  {
    myPort.write("INPUT,");
    myPort.write(str(reset));
    myPort.write(',');
    myPort.write(str(Sta));
    myPort.write(',');
    myPort.write(str(Stb));
    myPort.write(',');
    myPort.write('\n');
  }
  
  old_reset = reset;
  old_Sta = Sta;
  old_Stb = Stb;
}
           

void generate_inputs()
{
  
  
  if (clk <= 5)
  {
    reset = 1;
    Sta = 0;
    Stb = 0;
  }
    else if (clk >5 && clk <=10)
   {
    reset = 0;
    Sta = 1;
    Stb = 0;
  
   }
    else if (clk >10 && clk <15)
   {
    reset = 0;
    Sta = 0;
    Stb = 1;
   }
    else
  {
    reset = 0;
    Sta = 1;
    Stb = 0;
  } 
  
  clk++;
}


void serialEvent(Serial p)
{
  String message;
  String header;
  
  message = p.readStringUntil(LF);  //read serial data
  
 
  if (message != null)
  {
    println(message);
    
    if (message.charAt(0) != '#') 
    {
      header = message.substring(0,6);
      
      if (header.equals("OUTPUT") )
      {
        //my_outputs.A_red_light = int(message.charAt(7)) - 48;
        A_red_light = int(message.charAt(7)) - 48;
        A_yellow_light = int(message.charAt(9)) - 48;
        A_green_light = int(message.charAt(11)) - 48;
        B_red_light = int(message.charAt(13)) - 48;
        B_yellow_light = int(message.charAt(15)) - 48;
        B_green_light = int(message.charAt(17)) -48;
      
        println("STATUS A:" + A_red_light + " " + A_yellow_light + " " + A_green_light);
        println("STATUS B:" + B_red_light + " " + B_yellow_light + " " + B_green_light);
      }
    }
  }
}


  