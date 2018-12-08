package frames;

import arduinocomm.ArduinoCommunication;
import jssc.SerialPortException;
import util.Constants;

import javax.swing.*;

public class PortSelectionFrame extends JFrame{

    public PortSelectionFrame() {
        initUI();
        this.setVisible(true);
    }

    private void initUI() {

        // Panel setup
        JPanel panel = new JPanel();
        getContentPane().add(panel);
        panel.setLayout(null);

        // Labels
        JLabel port_selection_label = new JLabel(Constants.SELECT_A_PORT, JLabel.LEFT);
        port_selection_label.setBounds(10, 10, 200, 30);

        // List all the available ports
        String[] available_ports = ArduinoCommunication.getAvailablePorts();
        JComboBox<String> port_selection = new JComboBox<>(available_ports);
        port_selection.setBounds(130, 50, 100, 30);

        // Next button
        JButton ok_button = new JButton(Constants.OK);
        ok_button.setBounds(130, 100, 100, 30);
        ok_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame
            ArduinoCommunication.setPort((String) port_selection.getSelectedItem()); // Set the port globally
            try {
                ArduinoCommunication.connect(); // Start communication
            } catch (SerialPortException | InterruptedException e) {
                e.printStackTrace();
            }
            new NumberOfTasksFrame(Constants.INITIAL_SETUP); // Create the next frame
        });

        // Adding all elements to panel
        panel.add(ok_button);
        panel.add(port_selection_label);
        panel.add(port_selection);

        // Window setup
        setTitle(Constants.PORT_SELECTION);
        setSize(400, 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }

}
