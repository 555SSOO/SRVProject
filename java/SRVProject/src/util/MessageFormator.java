package util;

import arduinocomm.ArduinoCommunication;
import jssc.SerialPortException;

import java.util.List;

public class MessageFormator {

    public static void sendBatchTaskMessage(List<Integer> periodic_task_durations, List<Integer> periodic_task_periods,
                                            List<Integer> aperiodic_task_durations){

        StringBuilder message = new StringBuilder();
        message.append("b");
        for(int i = 0; i < periodic_task_durations.size(); i++){
            message.append(periodic_task_durations.get(i)).append(",").append(periodic_task_periods.get(i)).append(";");
        }
        message.append("_");
        for (Integer aperiodic_task_duration : aperiodic_task_durations) {
            message.append(aperiodic_task_duration).append("-");
        }
        // The message will have b char to indicate batch mode, a ',' separator between periodic task durations and periods,
        // a ';' separator between periodic tasks, a '_' separator between periodic and aperiodic tasks,
        // and a '-' separator between aperiodic tasks
        // For example b5,4;3,3;4,1;1,2;5,2;_3-1-3-3-0-~
        message.append("~");
        System.out.println(message);
        try {
            ArduinoCommunication.writeToSerial(message.toString());
        } catch (SerialPortException e) {
            e.printStackTrace();
        }

    }

    public static void sendServerParams(int server_period, int server_capacity){
        try {
            ArduinoCommunication.writeToSerial(String.valueOf(server_period));
            Thread.sleep(3000);
            ArduinoCommunication.writeToSerial(String.valueOf(server_capacity));
        } catch (SerialPortException | InterruptedException e) {
            e.printStackTrace();
        }
    }
    public static void sendStopTaskMessage(int number_of_task_to_stop){
        StringBuilder message = new StringBuilder();
        message.append("s");
        message.append(number_of_task_to_stop);
        System.out.println(message);
        try {
            ArduinoCommunication.writeToSerial(message.toString());
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }

    public static void sendStartPeriodicTaskMessage(int period, int duration){
        StringBuilder message = new StringBuilder();
        message.append("p");
        message.append(period);
        message.append(",");
        message.append(duration);
        message.append("~");
        System.out.println(message);
        try {
            ArduinoCommunication.writeToSerial(message.toString());
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }

    public static void sendStartAperiodicTaskMessage(int duration){
        StringBuilder message = new StringBuilder();
        message.append("a");
        message.append(duration);
        message.append("~");
        System.out.println(message);
        try {
            ArduinoCommunication.writeToSerial(message.toString());
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }



}
