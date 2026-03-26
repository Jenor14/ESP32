#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 53
#define RST_PIN 5
#define BUZZER_PIN 6

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Zustand
bool chipVorhanden = false;
unsigned long chipEntferntZeit = 0;

// Anzeige-Flag für aktives Medium
bool anzeigeAktiv = false;
unsigned long neueKarteZeit = 0;

// Liste der bekannten UIDs
struct Person {
  String uid;
  String name;
};

Person bekannt[] = {
  {"F7F80FB3", "Max"},
  {"1234567890", "Anna"},
  {"ABCDE12345", "Lisa"}
};
int anzahlBekannt = 3;

// Funktion für Buzzer
void piep(bool unbekannt) {
  if (unbekannt) {
    // zweimal lang piepen
    for (int i = 0; i < 2; i++) {
      tone(BUZZER_PIN, 1000, 500);
      delay(600); // Pause zwischen Pieptönen
    }
  } else {
    // einmal kurz piepen
    tone(BUZZER_PIN, 1000, 200);
  }
}

void setup() {
  SPI.begin();
  rfid.PCD_Init();

  lcd.begin(16, 2);
  lcd.print("RFID bereit");

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);
  Serial.println("System bereit");
}

void loop() {
  bool aktuelleKarte = rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();

  if (aktuelleKarte) {
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      if (rfid.uid.uidByte[i] < 0x10) uid += "0";
      uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();

    String anzeige = uid; // Standard: UID anzeigen
    bool istBekannt = false;
    for (int i = 0; i < anzahlBekannt; i++) {
      if (uid == bekannt[i].uid) {
        anzeige = bekannt[i].name;
        istBekannt = true;
        break;
      }
    }

    // Fall: während Anzeige aktiv → Warnung
    if (anzeigeAktiv) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Medium entfernen");
      neueKarteZeit = millis();
      anzeigeAktiv = false; // Reset Flag für Anzeige
      Serial.println("Neuer Chip während Anzeige! Bitte Medium entfernen.");
    } else {
      // Normale Anzeige
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Willkommen:");
      lcd.setCursor(0,1);
      lcd.print(anzeige);

      Serial.print("Chip erkannt: ");
      Serial.println(anzeige);

      // Buzzer
      piep(!istBekannt);
      anzeigeAktiv = true;
    }

    chipVorhanden = true; // Immer setzen
    chipEntferntZeit = 0; // Timer zurücksetzen
  }

  // Countdown bei entfernten Chips
  if (!aktuelleKarte && chipVorhanden) {
    if (chipEntferntZeit == 0) chipEntferntZeit = millis();

    unsigned long diff = millis() - chipEntferntZeit;
    int verbleibend = 5 - (diff / 1000);
    if (verbleibend < 0) verbleibend = 0;

    lcd.setCursor(0,1);
    lcd.print("Entfernung in: ");
    lcd.print(verbleibend);
    lcd.print("s  "); // alte Zahlenreste löschen

    if (diff >= 5000) {
      chipVorhanden = false;
      chipEntferntZeit = 0;
      lcd.clear();
      lcd.print("RFID bereit");
      Serial.println("Chip entfernt");

      // Buzzer beim Entfernen normal einmal piepen
      tone(BUZZER_PIN, 1000, 200);
    }
  }

  // Buzzer 5 Sekunden, wenn neuer Chip während aktiver Anzeige
  if (!anzeigeAktiv && neueKarteZeit != 0) {
    if (millis() - neueKarteZeit < 5000) {
      tone(BUZZER_PIN, 1000);
    } else {
      noTone(BUZZER_PIN);
      neueKarteZeit = 0;
    }
  }
}