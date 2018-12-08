package frames;

import util.Constants;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

import static java.lang.Integer.max;

class BatchTasksSetupFrame extends JFrame {


    BatchTasksSetupFrame(int number_of_periodic_tasks, int number_of_aperiodic_tasks) {
        initUI(number_of_periodic_tasks, number_of_aperiodic_tasks);
        this.setVisible(true);
    }

    private void initUI(int number_of_periodic_tasks, int number_of_aperiodic_tasks) {

        // Panel setup
        JPanel panel = new JPanel();
        getContentPane().add(panel);
        panel.setLayout(null);

        // Labels - set the strings, set the position and add them to the panel
        JLabel number_of_periodic_tasks_label = new JLabel(Constants.PERIODIC_TASKS_INFORMATION, JLabel.LEFT);
        number_of_periodic_tasks_label.setBounds(20, 10, 200, 30);
        JLabel periodic_task_duration_label = new JLabel(Constants.DURATION, JLabel.LEFT);
        periodic_task_duration_label.setBounds(60, 40, 200, 30);
        JLabel period_label = new JLabel(Constants.PERIOD, JLabel.LEFT);
        period_label.setBounds(120, 40, 200, 30);
        JLabel number_of_aperiodic_tasks_label = new JLabel(Constants.APERIODIC_TASKS_INFORMATION, JLabel.LEFT);
        number_of_aperiodic_tasks_label.setBounds(370, 10, 200, 30);
        JLabel aperiodic_task_duration_label = new JLabel(Constants.DURATION, JLabel.LEFT);
        aperiodic_task_duration_label.setBounds(410, 40, 200, 30);
        panel.add(number_of_periodic_tasks_label);
        panel.add(periodic_task_duration_label);
        panel.add(period_label);
        panel.add(number_of_aperiodic_tasks_label);
        panel.add(aperiodic_task_duration_label);


        List<JSpinner> periodic_task_durations_input = new ArrayList<>();
        List<JSpinner> periodic_task_periods_input = new ArrayList<>();
        List<JSpinner> aperiodic_task_durations_input = new ArrayList<>();
        List<Integer> periodic_task_durations = new ArrayList<>();
        List<Integer> periodic_task_periods = new ArrayList<>();
        List<Integer> aperiodic_task_durations = new ArrayList<>();

        // Add labels and input field for each periodic task
        for (int i = 0; i < number_of_periodic_tasks; i++) {
            JLabel number_of_task_label = new JLabel("#" + String.valueOf(i + 1), JLabel.LEFT);
            number_of_task_label.setBounds(20, i * 50 + 70, 200, 30);
            panel.add(number_of_task_label);

            JSpinner periodic_task_info_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_PERIODIC_TASKS, 1)); // Make a new spinner for task duration selection
            periodic_task_info_selector.setBounds(60, i * 50 + 70, 50, 30); // Set the bounds for it
            panel.add(periodic_task_info_selector); // Add it to the panel
            periodic_task_durations_input.add(periodic_task_info_selector); // Add the selector to the list
            periodic_task_info_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_PERIODIC_TASKS, 1)); // Selector for the task period
            periodic_task_info_selector.setBounds(120, i * 50 + 70, 50, 30); // Set bounds for it
            panel.add(periodic_task_info_selector); // Add it to the panel
            periodic_task_periods_input.add(periodic_task_info_selector); // Add the period information selector to the list
        }

        // Add labels and input field for each aperiodic task
        for (int i = 0; i < number_of_aperiodic_tasks; i++) {
            JLabel number_of_task_label = new JLabel("#" + String.valueOf(i + 1), JLabel.LEFT);
            number_of_task_label.setBounds(370, i * 50 + 70, 200, 30);
            panel.add(number_of_task_label);

            JSpinner aperiodic_task_info_selector = new JSpinner(new SpinnerNumberModel(1, 0, Constants.MAXIMUM_NUMBER_OF_APERIODIC_TASKS, 1)); // Create a selector for aperiodic task durations
            aperiodic_task_info_selector.setBounds(410, i * 50 + 70, 50, 30); // Set its bounds
            panel.add(aperiodic_task_info_selector); // Add the selector to the panel
            aperiodic_task_durations_input.add(aperiodic_task_info_selector); // Add the duration selector to the list
        }

        // Next button
        JButton ok_button = new JButton(Constants.OK);
        ok_button.setBounds(200, (max(number_of_aperiodic_tasks, number_of_periodic_tasks) * 50) + 100, 200, 30);
        ok_button.addActionListener(event -> {

            // We iterate over the lists of the selectors and add their values to lists of integer values
            for (int i = 0; i < periodic_task_durations_input.size();i++){
                periodic_task_durations.add(i, (Integer)periodic_task_durations_input.get(i).getValue());
                periodic_task_periods.add(i, (Integer)periodic_task_periods_input.get(i).getValue());
            }
            for (int i = 0; i < aperiodic_task_durations_input.size();i++){
                aperiodic_task_durations.add(i, (Integer)aperiodic_task_durations_input.get(i).getValue());
            }

            new OverviewFrame(periodic_task_durations,periodic_task_periods,aperiodic_task_durations);

        });
        panel.add(ok_button);


        // Window setup
        setTitle(Constants.BATCH_TASK_SETUP);
        setSize(620, max(number_of_aperiodic_tasks, number_of_periodic_tasks) * 50 + 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }
}



