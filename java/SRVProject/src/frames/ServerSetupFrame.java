package frames;

import arduinocomm.ArduinoCommunication;
import jssc.SerialPortException;
import util.Constants;

import javax.swing.*;

import static util.MessageFormator.sendServerParams;

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
        server_period_label.setBounds(20, 10, 200, 30);
        JLabel server_capacity_label = new JLabel(Constants.INPUT_SERVER_CAPACITY, JLabel.LEFT);
        server_capacity_label.setBounds(220, 10, 200, 30);

        // Number selectors -> how many periodic & aperiodic tasks we want on startup
        JSpinner server_period_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_SERVER_PERIOD, 1));
        server_period_selector.setBounds(60, 50, 50, 30);
        JSpinner server_capacity_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_SERVER_CAPACITY, 1));
        server_capacity_selector.setBounds(270, 50, 50, 30);

        // Next button
        JButton ok_button = new JButton(Constants.OK);
        ok_button.setBounds(130, 100, 100, 30);
        ok_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame

            // Send to arduino cap and per
            sendServerParams((Integer) server_period_selector.getValue(), (Integer) server_capacity_selector.getValue());

            new OverviewFrame(); // Create the next frame
        });

        // Adding all elements to panel
        panel.add(ok_button);
        panel.add(server_period_label);
        panel.add(server_capacity_label);
        panel.add(server_period_selector);
        panel.add(server_capacity_selector);

        // Window setup
        setTitle(Constants.PORT_SELECTION);
        setSize(400, 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }

}
