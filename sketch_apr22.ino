const int button_pin = 2;
const int leds[10][7] = {
  {1, 0, 1, 1, 1, 1, 1}, // 0
  {0, 0, 0, 0, 1, 1, 0}, // 1
  {0, 1, 1, 1, 0, 1, 1}, // 2
  {0, 1, 0, 1, 1, 1, 1}, // 3
  {1, 1, 0, 0, 1, 1, 0}, // 4
  {1, 1, 0, 1, 1, 0, 1}, // 5
  {1, 1, 1, 1, 1, 0, 1}, // 6
  {0, 0, 0, 0, 1, 1, 1}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 0, 1, 1, 1, 1}, // 9
};

// turn off all leds in 7 segments
void shutter(){
  for(int i=7; i<= 13; i++)
  {
    digitalWrite(i, LOW);
  }
}

void display_number(int num){
  int arr_i = 0;
  for(int i=7; i<= 13; i++)
  {
    digitalWrite(i, leds[num][arr_i]);
    arr_i++;
  }
}

bool is_pressed(){
  bool b1 = digitalRead(button_pin);
  if (b1){
    delay(20);
    bool b2 = digitalRead(button_pin);
    return b1 == b2;
  }
  return false;
}

// loop over outer led in 7segements
void light_mode_1(int delay_time){
  for(int i=7; i<= 13; i++)
  {
    if (i==8){
      continue;
    }
    digitalWrite(i, HIGH);
    delay(delay_time);
    shutter();
  }
}

void light_mode_2(int delay_time){
  int num = random(0, 10);
  display_number(num);
  delay(delay_time);
}

void setup() {
  for(int i=7; i<= 13; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(button_pin, INPUT);

  // Serial setting
  Serial.begin(9600);
  Serial.print("Welcome to Arduino!\n");
}

int state = 0;

void loop() {
  
  if (is_pressed()){
    state = state + 1;
    if (state > 2){
      state = 0;
    }
  }
  
  if (!state){
    shutter();
  }
  
  if (state == 1){
    shutter();
    
    light_mode_1(100);
    light_mode_1(200);
    light_mode_1(300);
    light_mode_1(400);

    for (int i = 0; i < 30; i++){
      light_mode_2(200);
    }

    int num = random(0, 10);
    display_number(num);
    state = 2;
  }
  delay(500);
}
