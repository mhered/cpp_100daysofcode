int incomingByte = 0; // for incoming serial data

String Buffer, Msg;

boolean newData = false;

const int TIME_UNIT = 200;
const int LED_PIN = 10;

void setup()
{
    // set pin to output
    pinMode(LED_PIN, OUTPUT);

    // opens serial port, sets data rate to 9600 bps
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop()
{
    receiveMessageWithEndMarker();
    // SOS: 1010100011101110111000101010000000
    sendMessage();
}

bool sendMessage()
{
    if (newData == true)
    {
        Serial.print("Just received: ");
        Serial.println(Msg);
        delay(10 * TIME_UNIT); // give time to look at LED

        int output_lvl;

        for (int i = 0; i < Msg.length(); i++)
        {
            if (Msg[i] == '\n' || Msg[i] == '\r') // char 13  == '\r' carriage return
            {
                Serial.println("SUCCESS Message sent!");
                newData = false;
                return true;
            }
            else if (Msg[i] == '0' || Msg[i] == '1')
            {
                output_lvl = Msg[i] - '0'; // convert char to int
                digitalWrite(LED_PIN, output_lvl);
                delay(TIME_UNIT);
            }
            else // invalid character
            {
                Serial.print("ERROR Invalid character: ");
                Serial.print((int)Msg[i]);
                Serial.print(" (");
                Serial.print((int)'\0');
                Serial.println(")");
                break;
            }
        }

        newData = false;
        return true;
    }
}


void receiveMessageWithEndMarker()
{
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    while (Serial.available() > 0 && newData == false)
    {
        rc = Serial.read();

        if (rc != endMarker)
        {
            Buffer += rc;
        }
        else
        {
            newData = true;
            Msg = Buffer;
            Buffer = "";
        }
    }
}