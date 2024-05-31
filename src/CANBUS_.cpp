#include "CANBUS_.h"

//unsigned long t_canbus = 0;

/*
void TEST_canbus()
{

    //      SETUP

    // start the CAN bus at 500 kbps
    if (!CAN.begin(500E3))
    {
        Serial.println("Starting CAN failed!");
        while (1)
            ;
    }

    CAN.loopback();

    //  -----------------------------------------------------------------------------------------------------------------------

    while (1)
    {

        //      READ PACKET

        // try to parse packet
        int packetSize = CAN.parsePacket();

        if (packetSize)
        {
            // received a packet
            Serial.print("Received ");

            if (CAN.packetExtended())
            {
                Serial.print("extended ");
            }

            if (CAN.packetRtr())
            {
                // Remote transmission request, packet contains no data
                Serial.print("RTR ");
            }

            Serial.print("packet with id 0x");
            Serial.print(CAN.packetId(), HEX);

            if (CAN.packetRtr())
            {
                Serial.print(" and requested length ");
                Serial.println(CAN.packetDlc());
            }
            else
            {
                Serial.print(" and length ");
                Serial.println(packetSize);

                // only print packet data for non-RTR packets
                while (CAN.available())
                {
                    Serial.print((char)CAN.read());
                }
                Serial.println();
            }

            Serial.println();
        }

        //  -----------------------------------------------------------------------------------------------------------------------

        //      SEND PACKET

        if ((millis() - t_canbus) > 1000)
        {
            // send packet: id is 11 bits, packet can contain up to 8 bytes of data
            Serial.print("Sending packet ... ");

            CAN.beginPacket(0x12);
            CAN.write('h');
            CAN.write('e');
            CAN.write('l');
            CAN.write('l');
            CAN.write('o');
            CAN.endPacket();

            Serial.println("done");
            Serial.println();

            t_canbus = millis();
        }

        delay(10);
    }
}
*/

void TEST_canbus() {
    Serial.println();
    Serial.println("TEST CANBUS");
    Serial.println();

    unsigned long t_canbus = 0;
    bool success = false;

    //      SETUP
    // start the CAN bus at 500 kbps
    if (!CAN.begin(500E3)) {
        Serial.println("Starting CAN failed!");
        Serial.println("---> TEST ERROR <---");
        Serial.println("{ \"name\": \"Canbus\", \"result\": \"error\"}");
        Serial.println();
        Serial.println("FINE TEST CANBUS");
        Serial.println();
        return;
    }

    CAN.loopback();

    //  -----------------------------------------------------------------------------------------------------------------------

    String messaggio = "";

    unsigned long t_timeout = millis();
    while (!success && ((millis() - t_timeout) < 10000)) {

        //      READ PACKET
        // try to parse packet
        int packetSize = CAN.parsePacket();

        if (packetSize) {
            if (CAN.packetId() == 119) {

                while (CAN.available())
                {
                    messaggio += (char)CAN.read();
                }

                if (messaggio == "hello") {
                    Serial.println("messaggio ricevuto");
                    Serial.println();
                    success = 1;
                }
            }
        }

        //  -----------------------------------------------------------------------------------------------------------------------

        //      SEND PACKET
        if ((millis() - t_canbus) > 1000) {
            // send packet: id is 11 bits, packet can contain up to 8 bytes of data

            CAN.beginPacket(0x77);
            CAN.write('h');
            CAN.write('e');
            CAN.write('l');
            CAN.write('l');
            CAN.write('o');
            CAN.endPacket();

            Serial.println("messaggio inviato");
            Serial.println();

            t_canbus = millis();
        }
        
        delay(10);
    }

    if (success) {
        Serial.println("---> TEST OK <---");
        Serial.println("{ \"name\": \"Canbus\", \"result\": \"ok\"}");
    } else {
        Serial.println("---> TEST ERROR <---");
        Serial.println("{ \"name\": \"Canbus\", \"result\": \"error\"}");
    }

    Serial.println();
    Serial.println("FINE TEST CANBUS");
    Serial.println();
}
