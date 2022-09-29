/*
  @file Buzzer_tone_demo.ino
  @brief Interfacing Piezo Buzzer with ARIES V2 Board
  @detail This demo plays "Jana Gana Mana" National Anthem on Piezo Buzzer 

   Reference aries board: https://vegaprocessors.in/blog/buzzer-with-aries-v2-board/
   
   *** Piezoelectric buzzer ***
   Connections:
   Buzzer     Aries Board
   VCC      -   3.3V
   GND      -   GND
   IN       -   GPIO0
*/

#define BUZZER 0    // connect INPUT pin of the buzzer on GPIO-0

int length = 149;
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
               
char notes[] = "cdeeeeeeeeedef eeedddbdc ccgggggggggaf fffffeddf eedeedeggaff eeeeeddbdc cdeeeedf efgggfedfe feeeddbdc ccggggeggggga fffffedfe egc bab aga ccddeedef "; // A space represents a rest



int tempo = 200;
 
void setup()
{
  pinMode(BUZZER, OUTPUT);
}
 
void loop()
{
  for (int i = 0; i < length; i++)
    {
      // Take space as rest
      if (notes[i] == ' ')
      {
        // Rest
        delay(beats[i] * tempo);
      }
      else
      {
        // Play the corresponding note for the corresponding beat
        playNote(notes[i], beats[i] * tempo);
      }
  
      // Pause between notes
      delay(tempo / 2);
    }

    noTone(BUZZER);
}


void tone(uint8_t _pin, unsigned int frequency, unsigned long duration){
for (unsigned long i = 0; i < duration * 1000L; i += frequency * 2)
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

void playNote(char note, int duration)
{
char names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
  int tones[] = {956, 851, 758, 716, 638, 568, 1014, 478};
  for (int i = 0; i < 8; i++)
  {
    if (names[i] == note)
    {
      tone(BUZZER, tones[i], duration);
    }
  }
}
