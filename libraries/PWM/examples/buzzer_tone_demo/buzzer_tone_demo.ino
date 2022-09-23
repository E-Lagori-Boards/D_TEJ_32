/*
* PIEZO BUZZER
* BLOG Link : https://vegaprocessors.in/blog/buzzer-with-aries-v2-board/
*/

int SPEAKER = 0;    // The speaker is on GPIO-0
int freq = 50;      // Starting frequency
static int i;

int beats[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
               2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1,
               2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
               1, 1, 1, 1, 2, 2, 2, 1, 1,
               1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
               2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
               1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
               2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
               1, 1, 4, 1, 1, 1, 4, 1, 1, 1, 4, 1,
               1, 1, 1, 1, 1, 1, 1, 1, 4, 1};

int tempo = 200;
 
void setup()
{
    pinMode(SPEAKER, OUTPUT);
}
 
void loop()
{
    freq += 100;      // add 100 to freq
 
    if (freq > 8000)
    {
        noTone(SPEAKER);
        freq = 50;
    }
 
    tone(SPEAKER, freq, beats[i] * tempo);
    i++;
    Serial.println(freq);
    delay(100);
}


void tone(uint8_t _pin, unsigned int frequency, unsigned long duration){
for (long i = 0; i < duration * 1000L; i += frequency * 2)
  {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(frequency);
    digitalWrite(_pin, LOW);
    delayMicroseconds(frequency);
  }
}


void noTone(uint8_t _pin){
    digitalWrite(_pin, LOW);
}