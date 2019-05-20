/*
The MIT License

Copyright (c) 2019 - Present Firebolt, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// "Bluebot" is a limited warranty and product of Firebolt, Inc. 
// and is strictly probihted to sell, refurnish, photocopy, copy, 
// etc. the code provided in "Bluebot".
//
// If copying any part or section or snippet from "Bluebot",
// please create a citation or have the comments.
//
// Failure to abide by this may result in serious penalty for
// damaging/destroying Firebolt, Inc. property.
//
#include <Wire.h>

#define LIDARLite_ADDRESS 0x62
#define RegisterMeasure 0x00
#define MeasureValue 0x04
#define RegisterHighLowB 0x8f

int reading = 0;
int speed = 250;
int motorpin1 = 0;
int motorpin2 = 2;
int speedpin1 = 7;
int speedpin2 = 9;
int beeb = 8;
void setup()
{
    pinMode(motorpin1, OUTPUT);
    pinMode(motorpin2, OUTPUT);
    pinMode(speedpin1, OUTPUT);
    pinMode(speedpin2, OUTPUT);
    pinMode(beeb, OUTPUT);
    Wire.begin();

    Serial.begin(9600);
}
void loop()
{

    while (Serial.available() > 0)
    {
        char incomingByte = Serial.read();
        Serial.println(incomingByte);
        if (incomingByte == 'w')
        {
            forward();
        }
        else if (incomingByte == 's')
        {
            backward();
        }
        else if (incomingByte == 'd')
        {
            right();
        }
        else if (incomingByte == 'a')
        {

            left();
        }

        else if (incomingByte == 'i')
        {
            if (speed <= 240)
            {
                speed += 10;
            }
        }

        else if (incomingByte == 'p')
        {
            if (speed >= 10)
            {
                speed -= 10;
            }
        }

        else if (incomingByte == 'z')
        {

            analogWrite(speedpin1, 0);
            analogWrite(speedpin2, 0);
        }

        else if (incomingByte == 'b')
        {

            digitalWrite(beeb, 1);
            delay(120);
            digitalWrite(beeb, 0);
        }
    }
    Serial.println(distance());
    if (distance() < 30)
    {
        analogWrite(speedpin1, 0);
        analogWrite(speedpin2, 0);
    }
}

void backward()
{
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, HIGH);
    analogWrite(speedpin1, speed);
    analogWrite(speedpin2, speed);
}

void forward()
{
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, LOW);
    analogWrite(speedpin1, speed);
    analogWrite(speedpin2, speed);
}

void right()
{
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, HIGH);
    analogWrite(speedpin1, speed);
    analogWrite(speedpin2, speed);
}

void left()
{
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
    analogWrite(speedpin1, speed);
    analogWrite(speedpin2, speed);
}

int distance()
{

    Wire.beginTransmission((int)LIDARLite_ADDRESS);
    Wire.write((int)RegisterMeasure);
    Wire.write((int)MeasureValue);
    Wire.endTransmission();

    delay(25);

    Wire.beginTransmission((int)LIDARLite_ADDRESS);
    Wire.write((int)RegisterHighLowB);
    Wire.endTransmission();

    delay(25);

    Wire.requestFrom((int)LIDARLite_ADDRESS, 2);

    if (2 <= Wire.available())
    {
        reading = Wire.read();
        reading = reading << 8;
        reading |= Wire.read();
        reading = reading - 15;
    }
    return reading;
}
