package arduinocomm;

import jssc.*;

import javax.swing.*;

public class ArduinoCommunication {

    private static String port;
    private static SerialPort serialPort;

    public static void connect() throws SerialPortException, InterruptedException {
        serialPort = new SerialPort(port);
        serialPort.openPort();
        serialPort.setParams(SerialPort.BAUDRATE_9600,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);
        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                SerialPort.FLOWCONTROL_RTSCTS_OUT);
        Thread.sleep(3000);
    }

    // change this TODO
    public static void readFromSerial(JFrame context) throws SerialPortException {
        serialPort.addEventListener(serialPortEvent -> {
            if(serialPortEvent.isRXCHAR() && serialPortEvent.getEventValue() > 0) {
                try {
                    JOptionPane.showMessageDialog(context, serialPort.readString(serialPortEvent.getEventValue()));
                }
                catch (SerialPortException ex) {
                    JOptionPane.showMessageDialog(context, "Error in receiving string from COM-port: " + ex);
                }
            }
        }, SerialPort.MASK_RXCHAR);
    }

    public static void writeToSerial(String message) throws SerialPortException {
        serialPort.writeString(message);
    }

    public static String[] getAvailablePorts() {
        return SerialPortList.getPortNames();
    }

    public static void setPort(String _port) {
        port = _port;
    }

}
