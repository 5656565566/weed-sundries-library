#include "card.h"

MFRC522 mfrc522(RC_NSS, RC_RST);
Preferences preferences;
int save = 0;

void init_mfrc()
{
    SPI.begin(RC_SCK, RC_MISO, RC_MOSI, RC_NSS);
    mfrc522.PCD_Init();
    pinMode(TIP_LED, OUTPUT);
}

void storeUIDToPreferences()
{
    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        uidString += String(mfrc522.uid.uidByte[i], HEX);
    }

    if (uidString != "")
    {
        preferences.begin("card");
        preferences.putString("uid", uidString);
        Serial.println("Card UID stored in Preferences: " + uidString);
        preferences.end();
        save = 0;
        digitalWrite(TIP_LED, LOW);

    }
}

void clearUID()
{
    memset(mfrc522.uid.uidByte, 0, sizeof(mfrc522.uid.uidByte));
    mfrc522.uid.size = 0;
}

bool isStoredCard()
{
    preferences.begin("card");
    String storedUID = preferences.getString("uid", "");
    preferences.end();
    if (storedUID == "")
    {
        return false;
    }

    String currentUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        currentUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    if (storedUID == currentUID)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void loop_mfrc()
{
    save --;
    if (!mfrc522.PICC_IsNewCardPresent()) {
        Serial.println("No new card detected.");
        return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
        Serial.println("Card reading failed.");
        return;
    }

    // Print card UID to serial monitor

    if (mfrc522.uid.size)
    {
        Serial.print("\nCard UID: ");
        if (save > 0)
        {
            storeUIDToPreferences();
        }
        else if (isStoredCard())
        {
            add_new_record(2);
            open_door();
        }
        else {
            digitalWrite(TIP_LED, LOW);
        }
    }
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX); // Print each byte of the UID in HEX
    }
    clearUID();

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}

void save_card()
{
    save = 15;
    digitalWrite(TIP_LED, HIGH);
}

void clear_card()
{
    preferences.begin("card");
    preferences.putString("uid", "");
    preferences.end();
}