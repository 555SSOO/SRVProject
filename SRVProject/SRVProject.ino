#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 128

# define NUMBER_OF_LEDS 5
# define MAX_TASKS 5

StackType_t task0Stack[STACK_SIZE];
StaticTask_t task0Handle;
StackType_t task1Stack[STACK_SIZE];
StaticTask_t task1Handle;
StackType_t task2Stack[STACK_SIZE];
StaticTask_t task2Handle;
StackType_t task3Stack[STACK_SIZE];
StaticTask_t task3Handle;
StackType_t task4Stack[STACK_SIZE];
StaticTask_t task4Handle;

int LED_PINS[] = {2, 3, 4, 5, 6};
int periodic_task_durations[MAX_TASKS];
int periodic_task_periods[MAX_TASKS];
int aperiodic_task_durations[MAX_TASKS];
int p_duration_index = 0, p_period_index = 0, a_duration_index = 0;
int zero = 0, one = 1, two = 2;
void setup() {

  // Start serial
  Serial.begin(9600);

  for (int i = 0; i < MAX_TASKS; i++) { // Init the arrays
    periodic_task_durations[i] = i;
    periodic_task_periods[i] = i;
    aperiodic_task_durations[i] = i;
  }
  // Set all led pins to output mode
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  Serial.println(F("Input your command"));

}

//example
//b5,4;3,3;4,1;1,2;5,2;_3-1-3-3-0-
//b5,10;5,15;_3-
void parseBatchModeInput() {
  char tmpchar = "";
  int tmpint;
  char tmp[4];
  int i = 0;

  // Read all the periodic task params
  while (tmpchar != '_') {
    tmpchar = Serial.read();
    if (tmpchar >= '0' && tmpchar <= '9') {
      tmp[i] = tmpchar;
      i++;
    } else if (tmpchar == ',') {
      tmp[i] = '\0';
      i = 0;
      sscanf(tmp, "%d", & tmpint);
      periodic_task_durations[p_duration_index] = tmpint;
      p_duration_index++;
    } else if (tmpchar == ';') {
      tmp[i] = '\0';
      i = 0;
      sscanf(tmp, "%d", & tmpint);
      periodic_task_periods[p_period_index] = tmpint;
      p_period_index++;
    }
  }
  // Read untill the end of input for all of the aperiodic tasks
  while (tmpchar != '\n') {
    tmpchar = Serial.read();
    if (tmpchar >= '0' && tmpchar <= '9') {
      tmp[i] = tmpchar;
      i++;
    } else if (tmpchar == '-') {
      tmp[i] = '\0';
      i = 0;
      sscanf(tmp, "%d", & tmpint);
      aperiodic_task_durations[a_duration_index] = tmpint;
      a_duration_index++;
    }
  }

  createBatchTasks();

}
void parseStartPeriodicTaskInput() {

}
void parseStartAperiodicTaskInput() {

}
void parseStopPeriodicTaskInput() {

}

void createBatchTasks() {

  for (int i = 0; i < p_duration_index; i++) { // Loop and start each periodic task
    switch (i) {
    case 0:
      xTaskCreateStatic(turnOnLED,
        "task0",
        STACK_SIZE,
        (void * ) & zero,
        2,
        task0Stack,
        &task0Handle,
        periodic_task_periods[i], // deadline
        periodic_task_durations[i], // duration
        1, // isPeriodic
        0, // isEnded
        0, // iEndTimeSection
        0); // uxTicksDone
      break;
    case 1:
      xTaskCreateStatic(turnOnLED,
        "task1",
        STACK_SIZE,
        (void * ) & one,
        2,
        task1Stack,
        &task1Handle,
        periodic_task_periods[i], // deadline
        periodic_task_durations[i], // duration
        1, // isPeriodic
        0, // isEnded
        0, // iEndTimeSection
        0); // uxTicksDone
      break;
    case 2:
      xTaskCreateStatic(turnOnLED,
        "task2",
        STACK_SIZE,
        (void * ) & two,
        2,
        task2Stack,
        &task2Handle,
        periodic_task_periods[i], // deadline
        periodic_task_durations[i], // duration
        1, // isPeriodic
        0, // isEnded
        0, // iEndTimeSection
        0); // uxTicksDone
      break;
//    case 3:
//      xTaskCreateStatic(turnOnLED,
//        "task3",
//        STACK_SIZE,
//        (void * ) & testint,
//        2,
//        task3Stack,
//        &task3Handle,
//        periodic_task_periods[i], // deadline
//        periodic_task_durations[i], // duration
//        1, // isPeriodic
//        0, // isEnded
//        0, // iEndTimeSection
//        0); // uxTicksDone
//      break;
//    case 4:
//      xTaskCreateStatic(turnOnLED,
//        "task4",
//        STACK_SIZE,
//        (void * ) & testint,
//        2,
//        task4Stack,
//        &task4Handle,
//        periodic_task_periods[i], // deadline
//        periodic_task_durations[i], // duration
//        1, // isPeriodic
//        0, // isEnded
//        0, // iEndTimeSection
//        0); // uxTicksDone
//      break;
    }
  }
}

void turnOnLED(void * pvParameters) {
  int * ledPin = (int * ) pvParameters;
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    if (i == * ledPin) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
  //Serial.println(*ledPin);
  if(*ledPin == 0){
      for(int j = 0; j< 500; j++){
    Serial.println(j);}
    }
    else if (*ledPin == 1){
        for(int j = 1500; j> 1000; j--){
    Serial.println(j);}
      }

  
  vTaskDeletePeriodic(0);
}

void loop() {

  Serial.println("In idle");

  if (Serial.available() > 0) {
    // If we are sent batch tasks
    switch (Serial.read()) {
      // Batch mode
    case 'b':
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
