const int data_size = 4;
const int interval = 10000; // [us]
byte data[data_size] = {0, 1, 2, 3};

boolean flag = false;

unsigned int dataSent() 
{
  flag = true;
  return interval;
}

void setup() 
{
  // put your setup code here, to run once:
  Serial2.begin(115200);
  attachTimerInterrupt(dataSent, interval);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(flag) 
  {
    Serial2.write(data, data_size);
    flag = false;
  }
}
