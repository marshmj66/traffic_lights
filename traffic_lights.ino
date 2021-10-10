
const int extra[] = {5,4,3};
const int data = 10;
const int clock_pin = 8;
const int latch = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 0; i<sizeof(extra); i++){
    pinMode(extra[i],OUTPUT);
  }
  pinMode(data,OUTPUT);
  pinMode(clock_pin,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  static int count = 0;
  int ran = random(1000,10000);
  int ran2 = random(1000,10000);
  if(count == 1){
    left_turn_allowed();
    count = 0;
  }
  top_bottom(ran);
  left_right(ran2);
  count++;
}

void top_bottom(int ran){
  int yellow = random(1000,3000);
  digitalWrite(latch,LOW);
  shiftOut(data,clock_pin,LSBFIRST,B10000100);
  digitalWrite(latch,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(3,HIGH);
  delay(ran);
  digitalWrite(6,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(latch,LOW);
  shiftOut(data,clock_pin,LSBFIRST,B10001000);
  digitalWrite(latch,HIGH);
  delay(yellow);
  digitalWrite(12,LOW);
  digitalWrite(3,LOW);
}

void left_right(int ran){
  int yellow = random(1000,3000);
  digitalWrite(latch,LOW);
  shiftOut(data,clock_pin,LSBFIRST,B00110000);
  digitalWrite(latch,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(5,HIGH);
  delay(ran);
  digitalWrite(5,LOW);
  digitalWrite(latch,LOW);
  shiftOut(data,clock_pin,LSBFIRST,B01010000);
  digitalWrite(latch,HIGH);
  digitalWrite(4,HIGH);
  delay(yellow);
  digitalWrite(4,LOW);
  digitalWrite(13,LOW);
}

void left_turn_allowed(){
  int r = random(5,15);
  static int right_left = 0;
  if(right_left == 0){
    clear_();
    for(int i = 0; i<r;i++){
      digitalWrite(13,HIGH);
      digitalWrite(latch,LOW);
      shiftOut(data,clock_pin,LSBFIRST,B00110000);
      digitalWrite(latch,HIGH);
      digitalWrite(5,HIGH);
      delay(500);
      digitalWrite(5,LOW);
      digitalWrite(latch,LOW);
      shiftOut(data,clock_pin,LSBFIRST,B00010000);
      digitalWrite(latch,HIGH);
      delay(500);
    }
    right_left = 1;
  }else{
    clear_();
    for(int i = 0; i<r;i++){
      digitalWrite(3,HIGH);
      digitalWrite(latch,LOW);
      shiftOut(data,clock_pin,LSBFIRST,B10000100);
      digitalWrite(latch,HIGH);
      digitalWrite(6,HIGH);
      delay(500);
      digitalWrite(6,LOW);
      digitalWrite(latch,LOW);
      shiftOut(data,clock_pin,LSBFIRST,B10000000);
      digitalWrite(latch,HIGH);
      delay(500);
    }
    right_left = 0;
  }
  clear_();
}

void clear_(){
  int lights[] = {13,12,6,5,4,3};
  digitalWrite(latch,LOW);
  shiftOut(data,clock_pin,LSBFIRST,B00000000);
  digitalWrite(latch,HIGH);

  for(int i = 0; i<sizeof(lights);i++){
    digitalWrite(lights[i],LOW);
  }
}
