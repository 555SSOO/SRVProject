#include <Arduino_FreeRTOS.h>

# define BTN_PIN 7

# define STACK_SIZE 128

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
int zero = 0, one = 1, two = 2, three = 3, four = 4;
int busy_queue[] = {0,0,0,0,0};

void clearSerial(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}

void setup() {

  int server_period, server_capacity;

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
  
  // Server setup
  //Serial.println(F("Input your server period"));
  digitalWrite(2, HIGH);
  while(1){
    if (Serial.available() > 0) {
      server_period = Serial.parseInt();
      clearSerial();
      break;
    }
  }

  digitalWrite(4, HIGH);
  //Serial.println(F("Input your server capacity"));
  while(1){
    if (Serial.available() > 0) {
      server_capacity = Serial.parseInt();
      clearSerial();
      break;
    }
  }

  setSporadicServerParams(server_period, server_capacity);

  attachInterrupt(digitalPinToInterrupt(BTN_PIN),btn_isr, RISING);

}

//example
//b5,4;3,3;4,1;1,2;5,2;_3-1-3-3-0-
//b5,10;5,15;_3-
//a3

// ===================================== PARSE BLOCK START ===========================================

void parseBatchModeInput() {
  char tmpchar = '[';
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
  clearSerial();
  createPeriodicTasks();
  createAperiodicTasks();

}
void parseStartPeriodicTaskInput() {

  char tmpchar = '[';
  int tmpint;
  char tmp[4];
  int i = 0;

  // Read all the periodic task params
  while (tmpchar != '\n') {
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
    } 
  }
  tmp[i] = '\0';
  i = 0;
  sscanf(tmp, "%d", & tmpint);
  periodic_task_periods[p_period_index] = tmpint;
  p_period_index++;

  clearSerial();
  createPeriodicTasks();

}
void parseStartAperiodicTaskInput() {
  char tmpchar = '[';
  int tmpint;
  char tmp[4];
  int i = 0;

  // Read untill the end of input for all of the aperiodic tasks
  while (tmpchar != '\n') {
    tmpchar = Serial.read();
    if (tmpchar >= '0' && tmpchar <= '9') { // Get the duration number
      tmp[i] = tmpchar;
      i++;
    }  
  }
  tmp[i] = '\0';
  sscanf(tmp, "%d", & tmpint);
  aperiodic_task_durations[a_duration_index] = tmpint;
  a_duration_index++;

  clearSerial();
  createAperiodicTasks();

}

// Read one number and stop that task
void parseStopPeriodicTaskInput() {
  int tmpint;
  char tmp[4];
  tmp[0] = Serial.read();
  tmp[1] = '\0';
  sscanf(tmp, "%d", & tmpint);
  clearSerial();
  stopPeriodicTask(tmpint);
}


// ===================================== PARSE BLOCK END ===========================================

// ===================================== UTIL BLOCK START ===========================================


void createPeriodicTasks() {

  int number_of_started_tasks = 0;
  int j = 0;

  for(int i = 0; i < MAX_TASKS; i++){ // We count how many tasks are aready started
    if(busy_queue[i] == 1) number_of_started_tasks++;
  }

  for (int i = number_of_started_tasks; i < p_duration_index; i++) { // Loop and start each new periodic task

    for(j = 0; j < MAX_TASKS; j++){ // We find an empty queue spot
      if(busy_queue[j] == 0) break;
    }
    switch (j) { // We make a task on that empty queue spot
    case 0:
      busy_queue[0] = 1;
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
      busy_queue[1] = 1;
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
      busy_queue[2] = 1;
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
   case 3:
     busy_queue[3] = 1;
     xTaskCreateStatic(turnOnLED,
       "task3",
       STACK_SIZE,
       (void * ) & three,
       2,
       task3Stack,
       &task3Handle,
       periodic_task_periods[i], // deadline
       periodic_task_durations[i], // duration
       1, // isPeriodic
       0, // isEnded
       0, // iEndTimeSection
       0); // uxTicksDone
     break;
   case 4:
     busy_queue[4] = 1;
     xTaskCreateStatic(turnOnLED,
       "task4",
       STACK_SIZE,
       (void * ) & four,
       2,
       task4Stack,
       &task4Handle,
       periodic_task_periods[i], // deadline
       periodic_task_durations[i], // duration
       1, // isPeriodic
       0, // isEnded
       0, // iEndTimeSection
       0); // uxTicksDone
     break;
    }
  }
}

void createAperiodicTasks(){

  int number_of_started_tasks = 0;
  int j = 0;

  for(int i = 0; i < MAX_TASKS; i++){ // We count how many tasks are aready started
    if(busy_queue[i] == 1) number_of_started_tasks++;
  }

  for (int i = number_of_started_tasks; i < p_duration_index + a_duration_index; i++) { // Loop and start each new aperiodic task

    for(j = 0; j < MAX_TASKS; j++){ // We find an empty queue spot
      if(busy_queue[j] == 0) break;
    }
    switch (j) { // We make a task on that empty queue spot
    case 0:
      busy_queue[0] = 1;
      xTaskCreateStatic(turnOnLEDa,
        "task0",
        STACK_SIZE,
        (void * ) & zero,
        2,
        task0Stack,
        &task0Handle,
        0, // deadline
        aperiodic_task_durations[i], // duration
        0, // isPeriodic
        0, // isEnded
        0, // iEndTimeSection
        0); // uxTicksDone
      break;
    case 1:
      busy_queue[1] = 1;
      xTaskCreateStatic(turnOnLEDa,
        "task1",
        STACK_SIZE,
        (void * ) & one,
        2,
        task1Stack,
        &task1Handle,
        0, // deadline
        aperiodic_task_durations[i], // duration
        0, // isPeriodic
        0, // isEnded
        0, // iEndTimeSection
        0); // uxTicksDone
      break;
    case 2:
      busy_queue[2] = 1;
      xTaskCreateStatic(turnOnLEDa,
        "task2",
        STACK_SIZE,
        (void * ) & two,
        2,
        task2Stack,
        &task2Handle,
        0, // deadline
        aperiodic_task_durations[i], // duration
        0, // isPeriodic
        0, // isEnded
        0, // iEndTimeSection
        0); // uxTicksDone
      break;
   case 3:
     busy_queue[3] = 1;
     xTaskCreateStatic(turnOnLEDa,
       "task3",
       STACK_SIZE,
       (void * ) & three,
       2,
       task3Stack,
       &task3Handle,
       0, // deadline
       aperiodic_task_durations[i], // duration
       0, // isPeriodic
       0, // isEnded
       0, // iEndTimeSection
       0); // uxTicksDone
     break;
   case 4:
     busy_queue[4] = 1;
     xTaskCreateStatic(turnOnLEDa,
       "task4",
       STACK_SIZE,
       (void * ) & four,
       2,
       task4Stack,
       &task4Handle,
       0, // deadline
       aperiodic_task_durations[i], // duration
       0, // isPeriodic
       0, // isEnded
       0, // iEndTimeSection
       0); // uxTicksDone
     break;
    }
  }

}

void stopPeriodicTask(int number_of_task_to_delete) {

  switch(number_of_task_to_delete){
    case 0:
      busy_queue[0] = 0;
      p_duration_index--;
      p_period_index--;
      vTaskDelete( xTaskGetHandle( "task0" ));
      break;
    case 1:
      busy_queue[1] = 0;
      p_duration_index--;
      p_period_index--;
      vTaskDelete( xTaskGetHandle( "task1" ));
      break;
    case 2:
      busy_queue[2] = 0;
      p_duration_index--;
      p_period_index--;
      vTaskDelete( xTaskGetHandle( "task2" ));
      break;
    case 3:
      busy_queue[3] = 0;
      p_duration_index--;
      p_period_index--;
      vTaskDelete( xTaskGetHandle( "task3" ));
      break;
    case 4:
      busy_queue[4] = 0;
      p_duration_index--;
      p_period_index--;
      vTaskDelete( xTaskGetHandle( "task4" ));
      break;
  }
}


void btn_isr() {
  a_duration_index++;
  aperiodic_task_durations[a_duration_index] = 3;
  createAperiodicTasks();
}

// ===================================== UTIL BLOCK END ===========================================


void turnOnLED(void * pvParameters) {
  int * ledPin = (int * ) pvParameters;
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    if (i == * ledPin) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
 
  while(1){}

  vTaskDeletePeriodic(0);
}

void turnOnLEDa(void * pvParameters) {

  int * task_number = (int * ) pvParameters;



  int ledPin = 4;
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    if (i == ledPin) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
  Serial.println("APERIODICCCCC");
  busy_queue[*task_number] = 0;
  vTaskDelete(0);
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
