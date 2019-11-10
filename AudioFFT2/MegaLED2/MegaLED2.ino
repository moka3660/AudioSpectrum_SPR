/*
    Arduino Megaつかう
    SPRESENSEのsubcore (1or2未確定)からシリアルでデータ受信
    LED光らす

*/
int incomingByte[10];	// 受信データ用
void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    pinMode(8,OUTPUT);
    for (int i = 0; i < 10; i++)
    {
        incomingByte[i] = 0;
    }
    
}

void loop()
{
    digitalWrite(8,LOW);
	if (Serial1.available() > 9) 
    { // 受信したデータが存在する
        for (int i = 0; i < 10; i++)
        {
            incomingByte[i] = Serial1.read();
       		Serial.print(incomingByte[i], DEC);
        }
        Serial.println();        
	//	incomingByte = Serial1.read(); // 受信データを読み込む
    //	Serial.print("I received: "); // 受信データを送りかえす
    }
}