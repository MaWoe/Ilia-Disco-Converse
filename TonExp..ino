#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0
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

    Serial.print("Note: ");
    Serial.println(aktuelleNote);

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
