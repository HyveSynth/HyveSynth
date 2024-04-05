// Hyve Tuning
// Skot Wiedmann
// 2018.02.05

// Pin 9 is audio output
// Pin 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12 are buttons to ground for each note

// Actual frequencies of the notes C6 through B6 with zero added for easy coding below
const int noteFreq[] = { 1976, 1865, 1760, 1661, 1568, 1480, 1397, 1319, 1245, 0, 1175, 1109, 1047 };
int noteCount[13];                      	// The number of clock cycles counted for each pitch

void setup ()
{
  TCCR1A = 0b01000000;                  	// Setup timer to toggle on compare match
  TCCR1B = 0b00001001;                  	// Setup timer for CTC mode
  for (int i=0; i<13; i++){
	pinMode (i, INPUT_PULLUP);          	// Setup all the button inputs
	noteCount[i] = 16000000 / noteFreq[i];  // Populate note counts based on frequency
  }
	pinMode (9, OUTPUT) ;               	// Setup audio output
}

void loop ()
{
  for (int i=0; i<13; i++){
	if (digitalRead(i) == LOW && i!=9) {	// Scan through buttons for any pressed, skip output pin
    	OCR1A = noteCount[i];           	// Update timer count for the note pressed
	}
  }
}
