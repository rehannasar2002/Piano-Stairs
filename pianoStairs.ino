int note_P[10]={59,60,62,64,65,67,69,71,72,74};  //Select the notes to play

int v[10]={0,0,0,0,0,0,0,0,0,0};                 // Input array

byte i,count;
int th =300,pd;
const int d=300;                                 //maximum delay

int k=0,j;
int flag[10]={0,0,0,0,0,0,0,0,0,0};


void lights(int i)
{
  for(j = 0;j < 10;j++)
  {
    if(j==i)
      digitalWrite(j+40,HIGH);
    else
      digitalWrite(j+40,LOW);
  }
}

void off()    //Switching off all RGB Strips
{
  for(j=0;j<10;j++)
     digitalWrite(j+40, LOW);
}

void RGBRand()
{
  int a=random(0,255);
  int b=random(0,255);
  int c=random(0,255);
  analogWrite(2,a);
  analogWrite(3,b);
  analogWrite(4,c);
}

void RGB(int i)            //colour coding for the RGB strips
{
  if(i==0)
  {
   analogWrite(2, 220);
   analogWrite(3, 20);
   analogWrite(4, 100);
  }
  else if(i==1)
  {
    analogWrite(2, 0);
    analogWrite(3, 250);
    analogWrite(4, 100);
  }
  else if(i==2)
  {
    analogWrite(2, 20);
    analogWrite(3, 20);
    analogWrite(4, 20);
  }
  else if(i==3)
  {
    analogWrite(2, 100);
    analogWrite(3, 200);
    analogWrite(4, 200);
  }
  else if(i==4)
  {
    analogWrite(2, 100);
    analogWrite(3, 100);
    analogWrite(4, 100);
  }
  else if(i==5)
  {
    analogWrite(2, 100);
    analogWrite(3, 175);
    analogWrite(4, 175);
  }
  else if(i==6)
  {
    analogWrite(2, 36);
    analogWrite(3, 36);
    analogWrite(4, 0);
  }
  else if(i==7)
  {
    analogWrite(2, 100);
    analogWrite(3, 125);
    analogWrite(4, 205);
  }
  else if(i==8)
  {
    analogWrite(2, 0);
    analogWrite(3, 0);
    analogWrite(4, 0);
  }
  else if(i==9)
  {
    analogWrite(2, 0);
    analogWrite(3, 60);
    analogWrite(4, 156);
  }
}


void MidiWrite(int cmd,int note,int vel)
{
  Serial.write(cmd);
  Serial.write(note);                     // sending note to Hairless midi
  Serial.write(vel);
}


void setup()
{
  for(i=0;i<10;i++)
  {
     pinMode(i+22,INPUT);
     pinMode(i+40,OUTPUT);
  }
  //RGB Pins
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);

  //Music Changer
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  
  Serial.begin(9600);
}

void loop()
{  
  for(int j=0 ; j<4 ; j++ )   //Selecting the instrument
  {
      if(digitalRead(j+9) == HIGH)
         k = j;
  }
  count=0;
  for( i=0 ; i<10 ; i++ )  //Detecting the Stairs
  {
      if(digitalRead(i+22) == HIGH)
      {
        v[i]=1;
        if(flag[i] == 0)
        {
          flag[i] = 1;
        } 
      }
      else
      {
        v[i] = 0;
        flag[i] = 0;
      }
  }
  for( i=0 ; i<10 ; i++ )
  {
    if(v[i] == 1)
       count++;
  }
    
  if(count!= 0 )
      pd=d/count;
  else if(count==0)
      pd=d;
  for(i=0;i<10;i++)
  {
      if(v[i]==1 && flag[i]==1) //sending the note to FLStudio
      {
         MidiWrite(144 + k , note_P[i] , 100); 
         RGBRand();
         lights(i);
         delay(pd);
         off();  
         flag[i] = 2;
      }
      else
      {
        analogWrite( 2, 0 );
        analogWrite( 3, 0 );
        analogWrite( 4, 0 );
      }
  }
    
  int v[10]={0,0,0,0,0,0,0,0,0,0}; //Switching off all the RGB Strips
}
