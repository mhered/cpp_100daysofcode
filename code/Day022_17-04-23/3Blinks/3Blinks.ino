
// define number of blinks and port for each LED

const int BLUE_LED = 12;
const int N_BLUE = 2;

const int RED_LED = 11;
const int N_RED = 1;

const int GREEN_LED = 10;
const int N_GREEN = 3;

void setup()
{
  // setup code here, runs once when you power the board or press the reset button
  // initialize digital pins for output.
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop()
{
  // main code here, the loop runs over and over again forever
  int T_MS = 50;

  // blink N_BLUE times BLUE_LED 
  for (int i = 0; i < N_BLUE; i++)
  {
    digitalWrite(BLUE_LED, HIGH); // send HIGH voltage level to BLUE_LED pin to turn the LED on
    delay(T_MS);                  // wait for T_MS milliseconds
    digitalWrite(BLUE_LED, LOW);  // send LOW voltage level to BLUE_LED pin to turn the LED off
    delay(4 * T_MS);              // wait for T_MS milliseconds
  }

  // blink N_RED times RED_LED 
  for (int i = 0; i < N_RED; i++)
  {
    digitalWrite(RED_LED, HIGH); // send HIGH voltage level to RED_LED pin to turn the LED on
    delay(T_MS);                 // wait for T_MS milliseconds
    digitalWrite(RED_LED, LOW);  // send LOW voltage level to RED_LED pin to turn the LED off
    delay(4 * T_MS);             // wait for T_MS milliseconds
  }

  // blink N_GREEN times GREEN_LED 
  for (int i = 0; i < N_GREEN; i++)
  {
    digitalWrite(GREEN_LED, HIGH); // send HIGH voltage level to GREEN_LED pin to turn the LED on
    delay(T_MS);                   // wait for T_MS milliseconds
    digitalWrite(GREEN_LED, LOW);  // send LOW voltage level to GREEN_LED pin to turn the LED off
    delay(4 * T_MS);               // wait for T_MS milliseconds
  }
}
