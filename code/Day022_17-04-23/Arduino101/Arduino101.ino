
void setup()
{
  // setup code here, runs once when you power the board or press the reset button
  // initialize digital pin 13 (which is wired to the builtin LED) as an output.
  pinMode(13, OUTPUT);
}

void loop()
{
  // main code here, the loop runs over and over again forever
  int T_MS = 100;

  digitalWrite(13, HIGH); // send HIGH voltage level to pin 13 to turn the LED on
  delay(T_MS);            // wait for T_MS milliseconds
  digitalWrite(13, LOW);  // send LOW voltage level to pin 13 to turn the LED off
  delay(9*T_MS);            // wait for T_MS milliseconds
}