/*
    Arduino Megaつかう
    SPRESENSEのsubcore (1or2未確定)からシリアルでデータ受信
    LED光らす

*/
const int lowside[20] = { A8, A9, A10, A11, A12, 
                          A13, A14, A15, 53, 51,
                          49, 47, 45, 43, 41,
                          39, 35, 33, 31, 29 };
const int highside[10] = { 52, 50, 48, 46, 44,
                           42, 40, 38, 36, 34 };

byte incomingByte = 0;	// 受信データ用
byte data[10];  //処理用データ
void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    for (int i = 0; i != 20; i++)
    {
        pinMode(lowside[i],OUTPUT);
    }
    for (int i = 0; i != 10; i++)
    {
        pinMode(highside[i],OUTPUT);
    }
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