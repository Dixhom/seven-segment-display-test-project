/*
   This code is for lighting 7 segment displays.
   There are 4 display units (unit), i.e. they can display 4 digit number.

   digital input pin assign is as follows.
   pin 2-5: unit 3,1,2,4 switch
   pin 6-13: segment f,g,a,b,c,d,e,DP
*/

// maps numbers to the "bits" of segments
bool num_array[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 1, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1} //9
};

// segment pin number
// in the order of a,b,c,d,e,f,g,DP
int segment_pin[8] = {
  8, 9, 10, 11, 12, 6, 7, 13
};

// maps units to pin numbers
int unit_map[4] = {
  3, 4, 2, 5
};

void setup() {
  Serial.begin(9600);

  // initialize units
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  // initialize segments
  for (int i = 6; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

}



void print_one_number(int n) {
  for (int i = 0; i < 7; i++) {
    int seg_flag = num_array[n][i];

    if (seg_flag == 1)
      digitalWrite(segment_pin[i], LOW);
    else
      digitalWrite(segment_pin[i], HIGH);
  }
}

// parse a float to an array to show which number to display on which unit.
// -1 means don't display anything on this unit.
void parse_to_segments(float f, int decimal_point, int ret[]) {
  // if the number is too big, return the largest possible number
  if (f >= powf(10, 4 - decimal_point)) {
    for (int i = 0; i < 4; i++) {
      ret[i] = 9;
    }
    return;
  }

  for (int i = 0; i < decimal_point; i++)
  {
    f *= 10;
  }
  int n = (int) f;

  for (int i = 0; i < 4; i++)
  {
    ret[3 - i] = n % 10;
    n = n / 10;
  }

  for (int i = 0; i < 4; i++)
  {
    if (ret[i] == 0 && i < 3 - decimal_point) {
      ret[i] = -1;
    }
  }
}


void print_float_primitive(float f, int decimal_point, float duration) {
  int segs[4];
  parse_to_segments(f, decimal_point, segs);

  // iterate through units
  for (int j = 0; j < 4; j++) {
    delay(duration);
    if (segs[j] == -1) continue; // no display

    for (int i = 0; i < 4; i++) {
      if (i == j)  digitalWrite(unit_map[i], HIGH);
      else digitalWrite(unit_map[i], LOW);
    }

    print_one_number(segs[j]);

    if (j == 3 - decimal_point && j != 3)
      digitalWrite(segment_pin[7], LOW);
    else
      digitalWrite(segment_pin[7], HIGH);

    
  }
}

void print_float(float f, int decimal_point, float duration) {
  int wait = 5;
  int n = (int)(duration / 4 / wait);
  for (int i = 0; i < n; i++) {
    print_float_primitive(f, decimal_point, wait);
  }
}

void loop() {
  print_float(1.234, 0, 500);
  print_float(1.234, 1, 500);
  print_float(1.234, 2, 500);
  print_float(1.234, 3, 500);
}
