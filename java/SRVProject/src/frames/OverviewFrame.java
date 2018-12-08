package frames;

import util.Constants;

import javax.swing.*;
import java.util.List;

class OverviewFrame extends JFrame{

    OverviewFrame(List<Integer> periodic_task_durations, List<Integer> periodic_task_periods,
                  List<Integer> aperiodic_task_durations) {
//        initUI(periodic_task_durations,periodic_task_periods,aperiodic_task_durations);
        initUI();
        this.setVisible(true);
    }

    private void initUI() {

        // Panel setup
        JPanel panel = new JPanel();
        getContentPane().add(panel);
        panel.setLayout(null);

        // Labels
        JLabel duration_of_periodic_task_label = new JLabel(Constants.DURATION, JLabel.LEFT);
        duration_of_periodic_task_label.setBounds(20, 10, 200, 30);
        JLabel period_of_periodic_task_label = new JLabel(Constants.PERIOD, JLabel.LEFT);
        period_of_periodic_task_label.setBounds(220, 10, 200, 30);
        JLabel duration_of_aperiodic_task = new JLabel(Constants.DURATION, JLabel.LEFT);
        duration_of_aperiodic_task.setBounds(20, 100, 200, 30);
        JLabel number_of_periodic_task_label = new JLabel("#", JLabel.LEFT);
        number_of_periodic_task_label.setBounds(20, 200, 200, 30);
        panel.add(duration_of_periodic_task_label);
        panel.add(period_of_periodic_task_label);
        panel.add(duration_of_aperiodic_task);
        panel.add(number_of_periodic_task_label);


        // Number selectors
        JSpinner periodic_task_duration_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_PERIODIC_TASKS, 1));
        periodic_task_duration_selector.setBounds(80, 10, 50, 30);
        JSpinner periodic_task_period_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_APERIODIC_TASKS, 1));
        periodic_task_period_selector.setBounds(270, 10, 50, 30);
        JSpinner aperiodic_task_duration_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_APERIODIC_TASKS, 1));
        aperiodic_task_duration_selector.setBounds(80, 100, 50, 30);
        JSpinner number_of_periodic_task_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_APERIODIC_TASKS, 1));
        number_of_periodic_task_selector.setBounds(50, 200, 50, 30);
        panel.add(periodic_task_duration_selector);
        panel.add(periodic_task_period_selector);
        panel.add(aperiodic_task_duration_selector);
        panel.add(number_of_periodic_task_selector);

        // Buttons

        JButton add_periodic_task_button = new JButton(Constants.ADD_PERIODIC_TASK);
        add_periodic_task_button.setBounds(370, 10, 200, 30);
        add_periodic_task_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame
        });
        panel.add(add_periodic_task_button);

        JButton add_aperiodic_task_button = new JButton(Constants.ADD_APERIODIC_TASK);
        add_aperiodic_task_button.setBounds(170, 100, 200, 30);
        add_aperiodic_task_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame
        });
        panel.add(add_aperiodic_task_button);

        JButton stop_periodic_task_button = new JButton(Constants.STOP_PERIODIC_TASK);
        stop_periodic_task_button.setBounds(120, 200, 200, 30);
        stop_periodic_task_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame
        });
        panel.add(stop_periodic_task_button);

        JButton batch_mode_button = new JButton(Constants.BATCH_MODE);
        batch_mode_button.setBounds(1300, 200, 200, 30);
        batch_mode_button.addActionListener(event -> {
            setVisible(false); // Hide this frame
            dispose(); // End this frame
        });
        panel.add(batch_mode_button);


        // Window setup
        setTitle(Constants.TASK_OVERVIEW);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }

}
