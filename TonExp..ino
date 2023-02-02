#include "pitches.h"

// bei Rest kein Licht

int tempo = 140;

// change this to whichever pin you want to use
int buzzer = 4;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Take on me, by A-ha
  // Score available at https://musescore.com/user/27103612/scores/4834399
  // Arranged by Edward Truong

  NOTE_FS5, 8, NOTE_FS5, 8, NOTE_D5, 8, NOTE_B4, 8, REST, 8, NOTE_B4, 8, REST, 8, NOTE_E5, 8,
  REST, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, NOTE_GS5, 8, NOTE_GS5, 8, NOTE_A5, 8, NOTE_B5, 8,
  NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, REST, 8, NOTE_D5, 8, REST, 8, NOTE_FS5, 8,
  REST, 8, NOTE_FS5, 8, REST, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8,
  NOTE_FS5, 8, NOTE_FS5, 8, NOTE_D5, 8, NOTE_B4, 8, REST, 8, NOTE_B4, 8, REST, 8, NOTE_E5, 8,

  REST, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, NOTE_GS5, 8, NOTE_GS5, 8, NOTE_A5, 8, NOTE_B5, 8,
  NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, REST, 8, NOTE_D5, 8, REST, 8, NOTE_FS5, 8,
  REST, 8, NOTE_FS5, 8, REST, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8,
  NOTE_FS5, 8, NOTE_FS5, 8, NOTE_D5, 8, NOTE_B4, 8, REST, 8, NOTE_B4, 8, REST, 8, NOTE_E5, 8,
  REST, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, NOTE_GS5, 8, NOTE_GS5, 8, NOTE_A5, 8, NOTE_B5, 8,

  NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, REST, 8, NOTE_D5, 8, REST, 8, NOTE_FS5, 8,
  REST, 8, NOTE_FS5, 8, REST, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8,

};
//LichtPins Rechts
#define RECHTS_ROT       10
#define RECHTS_BLAU      11
#define RECHTS_GRUEN      9

//LichtPins Links
#define LINKS_ROT         5
#define LINKS_BLAU        3
#define LINKS_GRUEN       6

#define INTERRUPT_PIN      2
#define ANZAHL_LICHT_MODI        3


// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int ganzeNote = (60000 * 4) / tempo;

int divider = 0, Notenlaenge = 0;

volatile byte lightMode = 0;
volatile int letzteAenderung = 0;

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C Lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  pinMode(RECHTS_ROT, OUTPUT);
  pinMode(RECHTS_BLAU, OUTPUT);
  pinMode(RECHTS_GRUEN, OUTPUT);
  pinMode(LINKS_ROT, OUTPUT);
  pinMode(LINKS_BLAU, OUTPUT);
  pinMode(LINKS_GRUEN, OUTPUT);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  //Funktion(isr) wird mit intterupt verbunden, von + auf -
  //Hauptprogramm wird bei Fall unterbrochen, verbundene Funktion aussgeführt
  //Interrupt wird benutzt, um staendiges Abfragen(polling) zu vermeiden
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), changeLightMode, FALLING);
  delay(500);
  letzteAenderung = 0;
  lightMode = 0;

  Lcd.init();
  Lcd.backlight();
  Lcd.setCursor(3, 0);
  Lcd.print("Disco Converse");

}
//isr(kurz, um Hauptprogramm nicht aus Takt zu bringen):
void changeLightMode() {
  const int millisSeitStart = millis();
  const int ZeitSeitLetzterAenderung = millisSeitStart - letzteAenderung;

  if (ZeitSeitLetzterAenderung > 500) {
    letzteAenderung = millisSeitStart;
    lightMode++;
    if (lightMode >= ANZAHL_LICHT_MODI) {
      lightMode = 0;
    }
  }
}

void spieleLichtmodusMusik(int aktuelleNote, int Notenlaenge) {
  if (lightMode == 0) {
    lightMode0(aktuelleNote, Notenlaenge);
  } else if (lightMode == 1) {
    lightMode1(aktuelleNote, Notenlaenge);
  } else if (lightMode == 2) {
    lightMode2(aktuelleNote, Notenlaenge);
  }
}

void lightMode0(int aktuelleNote, int Notenlaenge) {
  analogWrite(RECHTS_ROT, 255);
  analogWrite(LINKS_GRUEN, 255);
}

int lightMode1LinksLeuchten = true;
int lightMode1RGBCounter = 0;
void lightMode1(int aktuelleNote, int Notenlaenge) {
  if (lightMode1LinksLeuchten) {
    if (lightMode1RGBCounter == 0) {
      analogWrite(LINKS_ROT, 255);
    } else if (lightMode1RGBCounter == 1) {
      analogWrite(LINKS_GRUEN, 255);
    } else if (lightMode1RGBCounter == 2) {
      analogWrite(LINKS_BLAU, 255);
    }
    lightMode1RGBCounter++;
    if (lightMode1RGBCounter == 3) {
      lightMode1RGBCounter = 0;
    }
  } else {
    if (lightMode1RGBCounter == 0) {
      analogWrite(RECHTS_BLAU, 255);
    } else if (lightMode1RGBCounter == 1) {
      analogWrite(RECHTS_ROT, 255);
    } else if (lightMode1RGBCounter == 2) {
      analogWrite(RECHTS_GRUEN, 255);
    }
  }

  lightMode1LinksLeuchten = !lightMode1LinksLeuchten;
}

void lightMode2(int aktuelleNote, int Notenlaenge) {
  if (aktuelleNote <= NOTE_B4) {
    analogWrite(LINKS_ROT, 255);
    analogWrite(RECHTS_ROT, 255);
  } else if (aktuelleNote <= NOTE_E5) {
    analogWrite(LINKS_GRUEN, 255);
    analogWrite(RECHTS_ROT, 255);
  } else if (aktuelleNote < NOTE_B5) {
    analogWrite(LINKS_BLAU, 255);
    analogWrite(RECHTS_ROT, 255);
  } else {
    analogWrite(LINKS_GRUEN, 255);
    analogWrite(RECHTS_GRUEN, 255);
  }
}

void alleLampenAus() {
  analogWrite(RECHTS_ROT, 0);
  analogWrite(RECHTS_GRUEN, 0);
  analogWrite(RECHTS_BLAU, 0);
  analogWrite(LINKS_ROT, 0);
  analogWrite(LINKS_GRUEN, 0);
  analogWrite(LINKS_BLAU, 0);
}

void play() {

  int aktuelleNote;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    aktuelleNote = melody[thisNote];
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      Notenlaenge = (ganzeNote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      Notenlaenge = (ganzeNote) / abs(divider);
      Notenlaenge *= 1.5; // incre
      //the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, aktuelleNote, Notenlaenge * 0.9);

    if (aktuelleNote != REST) {
      spieleLichtmodusMusik(aktuelleNote, Notenlaenge);
    }

    delay(Notenlaenge / 2);
    alleLampenAus();
    delay(Notenlaenge / 2);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void loop() {
  play();
}
