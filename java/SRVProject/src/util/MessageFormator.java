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
        // For example b5,4;3,3;4,1;1,2;5,2;_3-1-3-3-0-

        try {
            ArduinoCommunication.writeToSerial(message.toString());
        } catch (SerialPortException e) {
            e.printStackTrace();
        }

    }


}
