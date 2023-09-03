//7 segments nums
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

// turn off all leds in 5 leds
void shutter2(){
  for(int i=2; i<= 6; i++)
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

//loop over 5 leds
void light_led(int delay_time){
  for(int i=2; i<= 6; i++)
  {
    digitalWrite(i, HIGH);
    delay(delay_time);
    shutter2();
  }
}

void light_mode_2(int delay_time, int max_value){
  int num = random(0, max_value);
  display_number(num);
  delay(delay_time);
}

//set initial fund
int fund = 5;

// fruit nums
const int num_type = 5;

char fruits[num_type][10] = {
  "apple",
  "banana",
  "cherry",
  "orange",
  "lemon"
};

int bets[num_type] = {0, 0, 0, 0, 0};

int led[num_type] = {6, 5, 4, 3, 2};

//decide number of digits
int get_digits(int num){
  if (num == 0){ return 1; }
  
  //c = count
  int c = 0;
  while(num != 0){
    num = num / 10;
    c++;
  }
  return c;
}

//adding white spaces
void padding(int num){
  for (int i = 0; i < num; i++){
    Serial.print(" ");
  }
}

void show_status(){
  for (int i = 0; i < num_type; i++){
    Serial.print(fruits[i]);
    Serial.print(" ");
  }
  Serial.println("");
  for (int i = 0; i < num_type; i++){
    padding(strlen(fruits[i]) - get_digits(bets[i]));
    Serial.print(bets[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

void clear_bets(){
  for (int i = 0; i < num_type; i++){
    bets[i] = 0;
  }
}

int sum_bets(){
  int r = 0;
  for (int i = 0; i < num_type; i++){
    r += bets[i];
  }
  return r;
}

bool is_bet(){
  return sum_bets() > 0;
}

void update_bets(){
  for (int i = 0; i < num_type;){
    if (Serial.peek() == -1){
      break;
    }

    int value = Serial.read() - 48;
    if (value < 0 || value > 9){
      continue;
    }

    bets[i] = value;
    i++;
  }
  while(Serial.read() != -1){}
}

void show_fund(){
  Serial.print("Total fund: ");
  Serial.println(fund);
}

void update_fund(int num){
  for (int i = 0; i < num_type; i++){
    fund -= bets[i];
    if(i == num){
      fund += bets[i] * 3; //bonus 3 times
    }
  }
}

void setup() {
  for(int i=7; i<= 13; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  for(int i=0; i<num_type; i++)
  {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
  
  // Serial setting
  Serial.begin(9600);
}

int state = 0;

void loop() {
  if (state == 0){
    shutter();
    shutter2();
    show_fund();
    show_status();
    state++;
  }

  if (state == 1){
    update_bets();
    light_mode_1(100);
    light_led(100);
  }

  if (is_bet() && state == 1){
    show_status();
    if (sum_bets() > fund){
      clear_bets();
      Serial.println("total bets exceed total fund");
      show_status();
    } else{
      state++;
    }
  }

  if (state == 2){
    for (int i = 0; i < 50; i++){
      light_mode_2(100, num_type);
    }
    int num = random(0, num_type);
    display_number(num);
    
    Serial.print("The lucky fruit is ");
    Serial.println(fruits[num]);
    digitalWrite(led[num], HIGH);
    Serial.print("You can earn ");
    Serial.println(3 * bets[num]);
    
    update_fund(num);
    clear_bets();
    show_fund();
    delay(5000);
    state = 0;
  }
  delay(200);
}
