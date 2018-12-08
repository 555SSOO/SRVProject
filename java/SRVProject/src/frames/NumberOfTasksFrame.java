package frames;

import util.Constants;

import javax.swing.*;

class NumberOfTasksFrame extends JFrame {

    NumberOfTasksFrame(String title) {
        initUI(title);
        this.setVisible(true);
    }

    private void initUI(String title) {

        // Panel setup
        JPanel panel = new JPanel();
        getContentPane().add(panel);
        panel.setLayout(null);

        // Labels
        JLabel number_of_periodic_tasks_label = new JLabel(Constants.NUMBER_OF_PERIODIC_TASKS, JLabel.LEFT);
        number_of_periodic_tasks_label.setBounds(20, 10, 200, 30);
        JLabel number_of_aperiodic_tasks_label = new JLabel(Constants.NUMBER_OF_APERIODIC_TASKS, JLabel.LEFT);
        number_of_aperiodic_tasks_label.setBounds(220, 10, 200, 30);

        // Number selectors -> how many periodic & aperiodic tasks we want on startup
        JSpinner number_of_periodic_tasks_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_PERIODIC_TASKS, 1));
        number_of_periodic_tasks_selector.setBounds(60, 50, 50, 30);
        JSpinner number_of_aperiodic_tasks_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_APERIODIC_TASKS, 1));
        number_of_aperiodic_tasks_selector.setBounds(270, 50, 50, 30);

        // Next button
        JButton ok_button = new JButton(Constants.OK);
        ok_button.setBounds(100, 100, 200, 30);
        ok_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame
            new BatchTasksSetupFrame((Integer) number_of_periodic_tasks_selector.getValue() // Start the task setup frame
                    , (Integer) number_of_aperiodic_tasks_selector.getValue());
        });

        // Adding all elements to panel
        panel.add(ok_button);
        panel.add(number_of_periodic_tasks_selector);
        panel.add(number_of_aperiodic_tasks_selector);
        panel.add(number_of_periodic_tasks_label);
        panel.add(number_of_aperiodic_tasks_label);

        // Window setup
        setTitle(title);
        setSize(420, 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }
}
