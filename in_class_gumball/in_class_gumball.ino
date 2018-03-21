struct inputs
{

  int N;
  int D;
  int Q;
  
};
struct output
{

  int value;
  int gumball;
  
};

void calculate_nextstate(struct inputs *in, struct outputs *out)
void display (struct inputs *in, struct outputs *out)


void setup() {
  // put your setup code here, to run once:
serial.begin(9600);
serial.println("start simulation");
  

}

void loop() {
  // put your main code here, to run repeatedly:

  while (RUN_SIM)
  {
    while(clk<20)
    {
      generate_inputs(&myinputs);
      calculate_nextstate(&my_inputs,&my_outputs);
      display(&my_inputs,&my_outputs);
      clk++;
      delay(1000);
      }
      
  }


}
