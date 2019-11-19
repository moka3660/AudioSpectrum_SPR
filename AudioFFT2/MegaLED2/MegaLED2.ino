/*
    Arduino Megaつかう
    SPRESENSEのsubcore (1or2未確定)からシリアルでデータ受信
    LED光らす

*/
byte incomingByte = 0;	// 受信データ用
void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    pinMode(8,OUTPUT);
}

void loop()
{
    digitalWrite(8,LOW);
	if (Serial1.available() >= 10) 
    { // 受信したデータが存在する
        for (int i = 0; i != 10; i++)
        {
            incomingByte = Serial1.read();
       		Serial.print(incomingByte, DEC);
            Serial.print(",");
        }
        Serial.println();        
    }
}