#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS       20
// colors           R,G,B
int colors[][3] = {{50,0,0},
                  {0,50,0},
                  {0,0,50},
                  };
                    

#define SIZE_OF_RECTANGLE 4
#define REC_DELAY 500

#define SIZE_OF_RHOMBUSE 5 //(MEUYAN) how many rows it will contain:
// Example of 5
//   *    1 
//  * *   2 
// *   *  3 
//  * *   4 
//   *    5 

#define PATTERN_TIME 10000

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(9600);  
  pixels.begin(); // This initializes the NeoPixel library.

}

void loop() {
  rectangle();
 // rhombus(); //MEUYAN



}
//-------------------------------
void clear_all() {
//-------------------------------
   for (int i = 0; i <NUMPIXELS; ++i) {
    pixels.setPixelColor(i,0,0,0);
   }
}
//-------------------------------
void draw_rectangle (int color[3],int start) {
//-------------------------------
  for (int i = 0; i <(NUMPIXELS/(2*(SIZE_OF_RECTANGLE)))+0.5; ++i) {
    for (int j=start;j<SIZE_OF_RECTANGLE+start;++j) {
        pixels.setPixelColor(i*2*SIZE_OF_RECTANGLE+j,pixels.Color(color[0],color[1],color[2]));
    }
  }
  pixels.show();      
}

//-------------------------------
void rectangle () {
//-------------------------------
  int rectangle_time,start;
  while (rectangle_time < PATTERN_TIME) {
    for (int color_idx = 0; color_idx <sizeof(colors)/sizeof(int[3]); ++color_idx) {
      clear_all();
      draw_rectangle(colors[color_idx],start);
      start = !start*4;
      //Serial.println(start);  
      //pixels.setPixelColor(1,pixels.Color(colors[color_idx][0],colors[color_idx][1],colors[color_idx][2]));
      //pixels.show();
      delay(REC_DELAY);
      rectangle_time+=REC_DELAY;
    } 
 //   Serial.println(rectangle_time);
  }
}
//-------------------------------
void draw_rhombuse (int color[3],int start) {
//-------------------------------
  int led,led2;
  for (int i = 0; i <(NUMPIXELS/(2*(SIZE_OF_RHOMBUSE)))+0.5; ++i) {
    for (int j=start;j<SIZE_OF_RECTANGLE+start;++j) {
      if (j <= SIZE_OF_RECTANGLE/2) {
        led = SIZE_OF_RECTANGLE/2+j;
        led2 = SIZE_OF_RECTANGLE/2-j;
      } else {
        int new_j = SIZE_OF_RECTANGLE/2 - j;
        led = SIZE_OF_RECTANGLE/2+new_j;
        led2 = SIZE_OF_RECTANGLE/2-new_j;        
      }
      Serial.println(led);
      Serial.println(led2);

   //   pixels.setPixelColor(i*2*SIZE_OF_RHOMBUSE+led,pixels.Color(color[0],color[1],color[2]));
      pixels.setPixelColor(i*2*SIZE_OF_RHOMBUSE+led2,pixels.Color(color[0],color[1],color[2]));
    }
  }
  pixels.show();   
}
//-------------------------------
void rhombus () {
//-------------------------------
  int rhombus_time;  
  while (rhombus_time < PATTERN_TIME) {
    for (int color_idx = 0; color_idx <sizeof(colors)/sizeof(int[3]); ++color_idx) {
      for (int start = 0; start<SIZE_OF_RHOMBUSE; ++start) {
        clear_all();
        draw_rhombuse(colors[color_idx],start);
        delay(50);
        rhombus_time+=50;
      }
    }
      
  }
}
