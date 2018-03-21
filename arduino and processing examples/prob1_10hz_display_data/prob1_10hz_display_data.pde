//prob1 -- Display 10hz signal Data from Arduino

import processing.serial.*;

Serial myPort;
char HEADER = 'H';
short LF = 10;

int portIndex = 0;
int ENTRIES = 600;
int [] in_10hz_array = new int [ENTRIES];
int array_index = 0;

int capture_data = 1;

void setup()
{
  size(700,500);
  printArray( Serial.list());
  println("Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex],115200);
  
  for(int i=0; i< in_10hz_array.length; i++)
    in_10hz_array[i] = 0;
    
}

void draw()
{
  int oldx =0; int oldy = 400;
  int newx, newy;

  if (capture_data == 0) 
  {
    for(int i=1; i < 50; i++)
    {
      newx = oldx + 10;
      newy = 400 - 400*in_10hz_array[i];
      
      if (in_10hz_array[i] != in_10hz_array[i-1])
      {
        //draw vertical line
        line(oldx,oldy,oldx,newy);
        line(oldx,newy,newx,newy);
      }
      else
      {
        line(oldx,oldy,newx,newy);
      }
           
      oldx = newx;
      oldy = newy;
    }
   }
  
  //delay(50);
}

void serialEvent(Serial p)
{
  String message = p.readStringUntil(LF);  //read serial data
  
  if (message != null)
  {
    print(message);
    String [] data = message.split(",");  //split message into array
    
    if (data[0].charAt(0) == HEADER && data.length > 2)
    {
      //println("out_10hz = " + data[1] + " in_10hz = " + data[2]);
      
      if (array_index == 50)
      { 
        capture_data = 0;
        array_index = 0;
 
      }
       
      if (capture_data == 1)  
      {
        println("out_10hz = " + data[1] + " in_10hz = " + data[2]);
        in_10hz_array[array_index++] = int(data[2]);
      }
    }
  }
}