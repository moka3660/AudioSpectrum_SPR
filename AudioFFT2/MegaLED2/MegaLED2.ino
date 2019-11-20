/*
    Arduino Megaつかう
    SPRESENSEのsubcore (1or2未確定)からシリアルでデータ受信
    LED光らす

*/
byte incomingByte = 0;	// 受信データ用
byte data[10];  //処理用データ
void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    pinMode(8,OUTPUT);
    for (int i = 0; i < 10; i++)
    {
        data[i] = 0;
    }
}

void loop()
{
    digitalWrite(8,LOW);
	if (Serial1.available() >= 10) 
    { // 受信したデータが存在する
        for (int i = 0; i != 10; i++)
        {
            incomingByte = Serial1.read();
            data[i] = incomingByte;
       	    //	Serial.print(incomingByte, DEC);
            //    Serial.print(",");
        }
        //    Serial.println();        
    }
    //光らせる
    for (int i = 0; i < 10; i++)
    {
        /* code */
        data[i] &= 0b00001111;  //座標を消す
    }
    
}