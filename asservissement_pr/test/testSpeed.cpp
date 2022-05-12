#define A_RIGHT 2
#define B_RIGHT 3//18 
#define A_LEFT 19
#define B_LEFT 18//2
#define WHEEL_DIAMETER 56 // mm
#define TICKS_PER_ROTATION (48 * 47)
#define DISTANCE_PER_TICK WHEEL_DIAMETER * 3.14159265358979323846 / TICKS_PER_ROTATION
#define RATE_HZ 50000 // Hz
#define TIMER_MS 1000.0 / (float)RATE_HZ // ms


#include <Encoder.h>
#include <SimpleTimer.h>




int leftLastTicks = 0, rightLastTicks = 0; 
SimpleTimer timer2 = SimpleTimer();

void testloop(){
    static Encoder rightEnc = Encoder(A_RIGHT, B_RIGHT);
    static Encoder leftEnc = Encoder(A_LEFT, B_LEFT);
    int leftTicks = leftEnc.read();
    int rightTicks = - rightEnc.read();
    Serial.print("leftEnc.read() : ");
    Serial.println(leftTicks);
    Serial.print("- rightEnc.read() : ");
    Serial.println(rightTicks);
    
    float dLeft = (float)(leftTicks - leftLastTicks) * DISTANCE_PER_TICK;
    float dRight = (float)(rightTicks - rightLastTicks) * DISTANCE_PER_TICK;
    
    float speedLeft = dLeft * RATE_HZ;
    float speedsRight = dRight * RATE_HZ;
}
 
void setup(){
    Serial.begin(9600);
    timer2.setInterval(TIMER_MS, testloop);
   
}

void loop(){
    
}

