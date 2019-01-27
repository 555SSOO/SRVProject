package frames;

import arduinocomm.ArduinoCommunication;
import jssc.SerialPortException;
import util.Constants;

import javax.swing.*;

public class ServerSetupFrame extends JFrame {

    public ServerSetupFrame() {
        initUI();
        this.setVisible(true);
    }

    private void initUI() {

        // Panel setup
        JPanel panel = new JPanel();
        getContentPane().add(panel);
        panel.setLayout(null);

        // Labels
        JLabel server_period_label = new JLabel(Constants.INPUT_SERVER_PERIOD, JLabel.LEFT);
        server_period_label.setBounds(10, 10, 200, 30);
        JLabel server_capacity_label = new JLabel(Constants.INPUT_SERVER_CAPACITY, JLabel.LEFT);
        server_capacity_label.setBounds(10, 10, 200, 30);

        // Next button
        JButton ok_button = new JButton(Constants.OK);
        ok_button.setBounds(130, 100, 100, 30);
        ok_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame
            //ArduinoCommunication.setPort((String) port_selection.getSelectedItem()); // Set the port globally
            try {
                ArduinoCommunication.connect(); // Start communication
                ArduinoCommunication.readFromSerial();
            } catch (SerialPortException | InterruptedException e) {
                e.printStackTrace();
            }
            new NumberOfTasksFrame(Constants.INITIAL_SETUP); // Create the next frame
        });

        // Adding all elements to panel
        panel.add(ok_button);
        panel.add(server_period_label);
        panel.add(server_capacity_label);

        // Window setup
        setTitle(Constants.PORT_SELECTION);
        setSize(400, 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }

}
