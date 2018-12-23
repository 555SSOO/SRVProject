#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 128

StackType_t task1Stack[STACK_SIZE];
StaticTask_t task1Handle;

StackType_t task2Stack[STACK_SIZE];
StaticTask_t task2Handle;

#define NUMBER_OF_LEDS 5
#define MAX_TASKS 5

int LED_PINS[] = {2,3,4,5,6};
int periodic_task_durations[MAX_TASKS];
int periodic_task_periods[MAX_TASKS];
int aperiodic_task_durations[MAX_TASKS];
int p_duration_index = 0, p_period_index = 0, a_duration_index = 0;

void setup() {

  for (int i = 0; i < MAX_TASKS; i++) { // Init the arrays
    periodic_task_durations[i] = i;
    periodic_task_periods[i] = i;
    aperiodic_task_durations[i] = i;
  }
  // Set all led pins to output mode
  for(int i = 0; i < NUMBER_OF_LEDS; i++){
    pinMode(LED_PINS[i], OUTPUT);
  }

  // Read from serial
  Serial.begin(9600);
  char read_char;
 
  while(1){
    //vTaskDelay(10);
    Serial.println(F("test3"));
    if (Serial.available() > 0) {
      // If we are sent batch tasks
      switch (Serial.read()){
        // Batch mode
        case 'b':
          xTaskCreateStatic(turnOnLED,
                    "task",
                    STACK_SIZE,
                    (void*)&LED_PINS[2],
                    2,
                    task1Stack, //stek za task - obavezan - treba da bude niz velicine kao treci parametar
                    &task1Handle); //handle je obavezan
          parseBatchModeInput();
          break;
        // Start periodic task
        case 'p':
          parseStartPeriodicTaskInput();
          break;
        // Start aperiodic task
        case 'a':
          parseStartAperiodicTaskInput();
          break;
        // Stop periodic task
        case 's':
          parseStopPeriodicTaskInput();
          break;
      }
    }
  }

//  xTaskCreateStatic(task1,
//                    "task",
//                    STACK_SIZE,
//                    (void*)&LED_PINS[2],
//                    2,
//                    task1Stack, //stek za task - obavezan - treba da bude niz velicine kao treci parametar
//                    &task1Handle); //handle je obavezan
//
//
//
//  xTaskCreateStatic(task1,
//                    "task9",
//                    STACK_SIZE,
//                    (void*)&LED_PINS[4],
//                    2,
//                    task2Stack, //stek za task - obavezan - treba da bude niz velicine kao treci parametar
//                    &task2Handle); //handle je obavezan
                    

}


void parseBatchModeInput(){
  char tmpchar = "";
  int tmpint;
  char tmp[4];
  int i = 0;

digitalWrite(2, HIGH);
  
        Serial.println(F("test1"));
  // Read all the periodic task params
  while(tmpchar != '_'){
    //vTaskDelay(1);
    tmpchar = Serial.read();
    if (tmpchar >= '0' && tmpchar <= '9') {
      tmp[i] = tmpchar;
      i++;
    } 
    else if (tmpchar == ',') {
        tmp[i] = '\0';
        i = 0;
        sscanf(tmp, "%d", & tmpint);
        periodic_task_durations[p_duration_index] = tmpint;
        p_duration_index++;
    }
    else if (tmpchar == ';') {
        tmp[i] = '\0';
        i = 0;
        sscanf(tmp, "%d", & tmpint);
        periodic_task_periods[p_period_index] = tmpint;
        p_period_index++;
    }
  }
  // Read untill the end of input for all of the aperiodic tasks
  while(tmpchar != '\n'){
    //vTaskDelay(1);
    tmpchar = Serial.read();
    if (tmpchar >= '0' && tmpchar <= '9') {
      tmp[i] = tmpchar;
      i++;
    } 
    else if (tmpchar == '-') {
        tmp[i] = '\0';
        i = 0;
        sscanf(tmp, "%d", & tmpint);
        aperiodic_task_durations[a_duration_index] = tmpint;
        a_duration_index++;
    }
  }
   
        Serial.println(F("test"));
        for (int i = 0; i < MAX_TASKS; i++) {
        Serial.print(F("1 : "));
        Serial.println(periodic_task_durations[i]);
      }
      for (int i = 0; i < MAX_TASKS; i++) {
        Serial.print(F("2 : "));
        Serial.println(periodic_task_periods[i]);
      }
      for (int i = 0; i < MAX_TASKS; i++) {
        Serial.print(F("3 : "));
        Serial.println(aperiodic_task_durations[i]);
      }
    
}
void parseStartPeriodicTaskInput(){
  
}
void parseStartAperiodicTaskInput(){
  
}
void parseStopPeriodicTaskInput(){
  
}

void turnOnLED(void* pvParameters){
  int * ledPin = (int * ) pvParameters;
  for(int i = 0; i < NUMBER_OF_LEDS; i++){
    if(LED_PINS[i] == *ledPin){
        digitalWrite(*ledPin, HIGH);
      }
     else{
        digitalWrite(LED_PINS[i], LOW);
      }
  }
  vTaskDelete(0);
}

void loop() {
}
