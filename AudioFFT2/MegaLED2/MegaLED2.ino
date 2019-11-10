/*
    Arduino Megaつかう
    SPRESENSEのsubcore (1or2未確定)からシリアルでデータ受信
    LED光らす
    これはレベルシフタです
*/
int val =0;

void setup()
{
    for (int i = 30; i < 46; i++)
    {
        pinMode(i,OUTPUT);
        digitalWrite(i,LOW);
    }
}

void loop()
{
    for (int i = 0; i < 16; i++)
    {
        val = analogRead(i);
        if (val > 300)
        {
            digitalWrite(i+30,HIGH);
        }else
        {
            digitalWrite(i+30,LOW);
        }
    }
}