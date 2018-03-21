struct inputs
{
  int N;
  int D;
  int Q;
};

struct outputs
{
  int value;
  int gumball;
};

void calculate_nextstate(struct inputs *in, struct outputs *out);
void display(struct inputs *in, struct outputs *out);
void generate_inputs(struct inputs *in);


int clk =0;
int RUN_SIM =1;

  struct inputs my_inputs;
  struct outputs my_outputs;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Start Simulation");
}

void loop() {
  // put your main code here, to run repeatedly:
while (RUN_SIM)
{
  while (clk < 20)
  {

    generate_inputs(&my_inputs);
    calculate_nextstate(&my_inputs, &my_outputs);
    display(&my_inputs, &my_outputs);
    clk++;
    delay(1000);
  }
  RUN_SIM =0;
  Serial.println("End Simulation");
}

}



void generate_inputs(struct inputs *in)
{
  if (clk < 5)
  {
    in->Q = 0; in->D = 0; in->N = 0;
  }

  if ((clk >= 5) && (clk <= 12))

  {
    in->Q = 0; in->D = 0; in->N = 1;
  }

  if (clk > 12)
  {
    in->Q = 1; in->D = 0; in->N = 0;
  }
}


void display(struct inputs *in, struct outputs *out)

{
 // cout << "clk : "<<   "N,D,Q =" << in->N << "," << in->D << "," << in->Q << "," << endl;

Serial.print("\nclk: ");
Serial.print(clk);
Serial.print("\nN,D,Q = ");
Serial.print(in->N);
Serial.print(",");
Serial.print(in->D);
Serial.print(",");
Serial.print(in->Q);

 
//  cout << "value = " << out->value <<  "gumball = " << out->gumball << endl;

Serial.print("\tvalue = ");
Serial.print(out->value);
Serial.print("\tgumball = ");
Serial.print(out->gumball);

}

void calculate_nextstate(struct inputs *in, struct outputs *out)
{
  static int ps = 0;
  static int ns = 0;

  ps = ns;

  out->value = ps;
  out->gumball = 0;

  switch (ps)
  {

  case 0: if (in->N == 1)
    ns = 5;
      else if (in->D = 1)
        ns = 10;
      else if (in->Q == 1)
        ns = 25;
      else
        ns = 0;
    break;

  case 5: if (in->N == 1)
    ns = 10;
      else if (in->D = 1)
        ns = 15;
      else if (in->Q == 1)
        ns = 30;
      else
        ns = 5;
    break;

  case 10: if (in->N == 1)
    ns = 15;
       else if (in->D = 1)
         ns = 20;
       else if (in->Q == 1)
         ns = 30;
       else
         ns = 10;
    break;

  case 15: if (in->N == 1)
    ns = 20;
       else if (in->D = 1)
         ns = 30;
       else if (in->Q == 1)
         ns = 30;
       else
         ns = 15;
    break;

  case 20: if (in->N == 1)
    ns = 25;
       else if (in->D = 1)
         ns = 30;
       else if (in->Q == 1)
         ns = 30;
       else
         ns = 20;
    break;

  case 25: if (in->N == 1)
    ns = 30;
       else if (in->D = 1)
         ns = 30;
       else if (in->Q == 1)
         ns = 30;
       else
         ns = 25;
    break;

  case 30: ns = 100;
    break;

  case 100:
    ns = 0;
    out->gumball = 1;
    break;
  }

  }

  

