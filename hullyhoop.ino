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
#define PATTERN_TIME 15000 // 1000 = 1sec                    
// RECTANGLE
#define SIZE_OF_RECTANGLE 4
#define REC_DELAY 200

// RHOMBUSE (MEUYAN)
#define SIZE_OF_RHOMBUSE 5 // how many rows it will contain:
// Example of 5
//   *    1 
//  * *   2 
// *   *  3 
//  * *   4 
//   *    5 
#define RHOMBUS_DELAY 50


// TREACE
#define TRACE_DELAY 100
// How many colors do you want (more colors, more gradient)
#define NUMOFCOLORS      7


// jump between to traces
#define JUMP 10

// light level 1=255
float HIGHLEVEL=0.4;
float MEDIUMLEVEL=0.2;
float LOWLEVEL=0.06;

int head_color = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(9600);  
  pixels.begin(); // This initializes the NeoPixel library.

}

void loop() {
  rectangle();
  rhombus(); //MEUYAN
  trace();



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
      
      delay(REC_DELAY);
      rectangle_time+=REC_DELAY;
      //Serial.println(rectangle_time);
    } 
  
  }
}
//-------------------------------
void draw_rhombuse (int color[3],int start) {
//-------------------------------
  int led,led2;
  for (int i = 0; i <(NUMPIXELS/(2*(SIZE_OF_RHOMBUSE)))+0.5; ++i) {
    if (start <= SIZE_OF_RHOMBUSE/2) {
      led = SIZE_OF_RHOMBUSE/2+start;
      led2 = SIZE_OF_RHOMBUSE/2-start;
    } else {
      int new_start = SIZE_OF_RHOMBUSE - 1 -start ;
      led = SIZE_OF_RHOMBUSE/2+new_start;
      led2 = SIZE_OF_RHOMBUSE/2-new_start;        
    }
    pixels.setPixelColor(i*2*SIZE_OF_RHOMBUSE+led,pixels.Color(color[0],color[1],color[2]));
    pixels.setPixelColor(i*2*SIZE_OF_RHOMBUSE+led2,pixels.Color(color[0],color[1],color[2]));
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
        delay(RHOMBUS_DELAY);
        rhombus_time+=RHOMBUS_DELAY;
      }
    }
      
  }
}

//-------------------------------
void trace () {
//-------------------------------
  int trace_time;  
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  int i = -1;
  clear_all();
  while (trace_time < PATTERN_TIME) {
    i++;
//    Serial.println(head_color);
    if (i == NUMPIXELS-1) {
      i = LastLed(i);
      trace_time+=(3*TRACE_DELAY);
      continue;    
    }      
    //Serial.println(i);
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    lightAllTraces(i, HIGHLEVEL); // the first led.
    if (i>0) {
        lightAllTraces(i-1, MEDIUMLEVEL); 
        if (i>1) {
           lightAllTraces(i-2, LOWLEVEL); 
           if(i>2) {
                lightAllTraces(i-3, 0); // turn off the distant led.            
           }
        }        
    }  
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(TRACE_DELAY); // Delay for a period of time (in milliseconds).
    trace_time+=TRACE_DELAY;
  }
}
//-------------------------------
int LastLed (int i) {
//-------------------------------
  lightAllTraces(i, HIGHLEVEL); 
  lightAllTraces(i-1, MEDIUMLEVEL);
  lightAllTraces(i-2, LOWLEVEL); 
  lightAllTraces(i-3, 0); 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(TRACE_DELAY); // Delay for a period of time (in milliseconds).

  
  lightAllTraces(i, MEDIUMLEVEL);                     
  lightAllTraces(i-1,LOWLEVEL);
  lightAllTraces(i-2, 0);                 
  head_color = (head_color+1)%NUMOFCOLORS;                    
  lightAllTraces(i-JUMP+1,HIGHLEVEL); 


  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(TRACE_DELAY); // Delay for a period of time (in milliseconds).

  lightAllTraces(i-JUMP+2,HIGHLEVEL); 
  lightAllTraces(i-JUMP+1, MEDIUMLEVEL);                     
  head_color = (head_color-1)%NUMOFCOLORS;                    
  lightAllTraces(i, LOWLEVEL);
  lightAllTraces(i-1, 0);                                 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(TRACE_DELAY); // Delay for a period of time (in milliseconds).

  lightAllTraces(i, 0);    
  head_color = (head_color+1)%NUMOFCOLORS;                    
  lightAllTraces(i-JUMP+3, HIGHLEVEL); 
  lightAllTraces(i-JUMP+2, MEDIUMLEVEL);                     
  lightAllTraces(i-JUMP+1, LOWLEVEL);

  i=i-JUMP+3;
  return i;
}
//-------------------------------
void lightAllTraces(int i, float power) {
//-------------------------------
  int trace_num = 0;
   while (i >= 0 ) {
     int color = (head_color+trace_num)%NUMOFCOLORS;
      pixels.setPixelColor(i, Wheel(color,power));
      i-=JUMP;     
      trace_num++;
   } 
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// the level is how brigt will be tghe light (0 to 255).
//-------------------------------
uint32_t Wheel(byte color, float level) {
//-------------------------------
  if (level==0) return pixels.Color(0, 0, 0);
  //level=100;   
  float power;
 // Serial.println(color);
  if(color < NUMOFCOLORS/3) {
     power=1.0*color/(NUMOFCOLORS/3)*255;
     return pixels.Color(level*(255 - power), 0, level*power); 
  } else if(color < 2*NUMOFCOLORS/3) {
      color -= NUMOFCOLORS/3;
      power=1.0*color/(NUMOFCOLORS/3)*255;
      return pixels.Color(0, level*power, level*(255 - power));
  } else {
     color -= 2*NUMOFCOLORS/3;
     power=1.0*color/(NUMOFCOLORS/3)*255;
     return pixels.Color(level*power, level*(255 - power), 0);
  }
}
