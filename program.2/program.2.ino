#include<SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
#define trigPin 12
#define echoPin 13
void setup()
{
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
delay(100);
}
void loop()
{
long duration, distance;
int max = 80; // Let consider as Height of the Garbage Bin is = 80 cm.
float diff, perc;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
diff = max - distance; // 'diff' variable tells u that, how much the Garbage Bin is Left to fill.
perc = (diff/max)*100; // 'perc' variable tells u that, how much percentage the Garbage Bin is filled.
if (perc>=90)
{
//Serial.println("Garbage Bin is FULL."); // When the Garbage Bin is filled more than 90%, then this Error Message will Displayed.
// Call the Function of Send SMS.
SendMessage(); // Send Message Function Call.
}
/*
else
{
Serial.print("Garbage Bin is Filled ");
Serial.print(perc);
Serial.print(" %."); // These 3 Lines are print, that how much the Garbage 
Bin is Filled...Ex. "Garbage Bin is Filled 70%.".
}
*/
/*
if (distance >= 400 || distance <= 2)
{
Serial.println("Out of range");
}
else
{
Serial.print(distance);
Serial.println(" cm");
}
 */
delay(500);
}
void SendMessage()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+918792574742\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Garbage Bin is Full."); // The SMS text you want to send
delay(100);
mySerial.println((char)26); // ASCII code of CTRL+Z
delay(1000);
}
