import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.Socket;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JToolBar;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;

/**
 * Step 3 window.
 * This is a small remote control for my C plus plus server.
 * I can send all server commands and I display the server response in the text area.
 */
public class MainWindow extends JFrame {

    private static final long serialVersionUID = 1L;

    private final JTextArea output = new JTextArea(14, 55);

    private final JTextField hostField = new JTextField("localhost", 12);
    private final JTextField portField = new JTextField("3331", 6);

    private final JTextField nameField = new JTextField(16);
    private final JTextField typeField = new JTextField("Group", 10);
    private final JTextField pathField = new JTextField(26);

    private final TcpClient client = new TcpClient();

    private final Action searchAction = new SearchAction();
    private final Action playAction = new PlayAction();
    private final Action saveAction = new SaveAction();
    private final Action loadAction = new LoadAction();

    private final Action showGroupsAction = new SimpleCommandAction("Show groups", "SHOW GROUP");
    private final Action showMediaAction = new SimpleCommandAction("Show media", "SHOW MEDIA");
    private final Action helpAction = new SimpleCommandAction("Help", "HELP");

    private final Action pickFileAction = new PickFileAction();
    private final Action clearAction = new ClearAction();
    private final Action exitAction = new ExitAction();

    /**
     * Builds the interface.
     */
    public MainWindow() {
        super("TP Etape 3");

        setLayout(new BorderLayout());

        output.setEditable(false);
        add(new JScrollPane(output), BorderLayout.CENTER);

        add(createTopPanel(), BorderLayout.NORTH);
        add(createBottomPanel(), BorderLayout.SOUTH);

        setJMenuBar(createMenuBar());

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    /**
     * Top panel contains tool bar and input fields.
     *
     * @return panel for the north area
     */
    private JPanel createTopPanel() {
        JPanel top = new JPanel(new BorderLayout());
        top.add(createToolBar(), BorderLayout.NORTH);
        top.add(createFieldsPanel(), BorderLayout.SOUTH);
        return top;
    }

    /**
     * Creates the tool bar with all main commands.
     *
     * @return tool bar
     */
    private JToolBar createToolBar() {
        JToolBar tb = new JToolBar();

        tb.add(searchAction);
        tb.add(playAction);
        tb.addSeparator();
        tb.add(saveAction);
        tb.add(loadAction);
        tb.addSeparator();
        tb.add(showGroupsAction);
        tb.add(showMediaAction);
        tb.addSeparator();
        tb.add(helpAction);
        tb.add(clearAction);
        tb.addSeparator();
        tb.add(exitAction);

        return tb;
    }

    /**
     * Creates the menu bar.
     * Menu items reuse the same actions as the tool bar.
     *
     * @return menu bar
     */
    private JMenuBar createMenuBar() {
        JMenuBar bar = new JMenuBar();

        JMenu menu = new JMenu("Menu");
        menu.add(new JMenuItem(searchAction));
        menu.add(new JMenuItem(playAction));
        menu.addSeparator();
        menu.add(new JMenuItem(saveAction));
        menu.add(new JMenuItem(loadAction));
        menu.addSeparator();
        menu.add(new JMenuItem(showGroupsAction));
        menu.add(new JMenuItem(showMediaAction));
        menu.addSeparator();
        menu.add(new JMenuItem(helpAction));
        menu.add(new JMenuItem(clearAction));
        menu.addSeparator();
        menu.add(new JMenuItem(exitAction));

        bar.add(menu);
        return bar;
    }

    /**
     * Fields panel where I type host port name type and path.
     *
     * @return panel with inputs
     */
    private JPanel createFieldsPanel() {
        JPanel p = new JPanel(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.insets = new Insets(4, 6, 4, 6);
        c.fill = GridBagConstraints.HORIZONTAL;

        c.gridx = 0;
        c.gridy = 0;
        p.add(new JLabel("Host"), c);

        c.gridx = 1;
        p.add(hostField, c);

        c.gridx = 2;
        p.add(new JLabel("Port"), c);

        c.gridx = 3;
        p.add(portField, c);

        c.gridx = 0;
        c.gridy = 1;
        p.add(new JLabel("Name"), c);

        c.gridx = 1;
        p.add(nameField, c);

        c.gridx = 2;
        p.add(new JLabel("Type"), c);

        c.gridx = 3;
        p.add(typeField, c);

        c.gridx = 0;
        c.gridy = 2;
        p.add(new JLabel("Path"), c);

        c.gridx = 1;
        c.gridwidth = 2;
        p.add(pathField, c);

        c.gridx = 3;
        c.gridwidth = 1;
        p.add(new JButton(pickFileAction), c);

        return p;
    }

    /**
     * Bottom panel is just a second way to click the commands.
     *
     * @return bottom panel
     */
    private JPanel createBottomPanel() {
        JPanel p = new JPanel();
        p.add(new JButton(searchAction));
        p.add(new JButton(playAction));
        p.add(new JButton(saveAction));
        p.add(new JButton(loadAction));
        p.add(new JButton(showGroupsAction));
        p.add(new JButton(showMediaAction));
        p.add(new JButton(helpAction));
        p.add(new JButton(clearAction));
        p.add(new JButton(exitAction));
        return p;
    }

    /**
     * Reads the port safely.
     *
     * @return port value
     */
    private int getPort() {
        try {
            return Integer.parseInt(portField.getText().trim());
        } catch (NumberFormatException ex) {
            return 3331;
        }
    }

    /**
     * Adds a line to the output and keeps the scroll at the bottom.
     *
     * @param s text to show
     */
    private void addOut(String s) {
        output.append(s);
        if (!s.endsWith("\n")) output.append("\n");
        output.setCaretPosition(output.getDocument().getLength());
    }

    /**
     * Sends one command to the server without freezing the UI.
     *
     * @param command command line sent to the server
     */
    private void sendCommandAsync(String command) {
        final String host = hostField.getText().trim();
        final int port = getPort();

        addOut(">> " + command);

        new Thread(() -> {
            try {
                String response = client.send(host, port, command);
                SwingUtilities.invokeLater(() -> addOut("<< " + response));
            } catch (IOException ex) {
                SwingUtilities.invokeLater(() -> addOut("<< ERROR " + ex.getMessage()));
            }
        }).start();
    }

    /**
     * Action for SEARCH name.
     */
    private class SearchAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        SearchAction() {
            super("Search");
            putValue(ACCELERATOR_KEY, KeyStroke.getKeyStroke("control F"));
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String name = nameField.getText().trim();
            if (name.isEmpty()) {
                addOut("<< Please type a name first");
                return;
            }
            sendCommandAsync("SEARCH " + name);
        }
    }

    /**
     * Action for PLAY name.
     */
    private class PlayAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        PlayAction() {
            super("Play");
            putValue(ACCELERATOR_KEY, KeyStroke.getKeyStroke("control P"));
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String name = nameField.getText().trim();
            if (name.isEmpty()) {
                addOut("<< Please type a name first");
                return;
            }
            sendCommandAsync("PLAY " + name);
        }
    }

    /**
     * Action for SAVE name type.
     * Example SAVE Group1 Group or SAVE P1 Photo
     */
    private class SaveAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        SaveAction() {
            super("Save");
            putValue(ACCELERATOR_KEY, KeyStroke.getKeyStroke("control S"));
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String name = nameField.getText().trim();
            String type = typeField.getText().trim();

            if (name.isEmpty() || type.isEmpty()) {
                addOut("<< Please fill name and type");
                return;
            }
            sendCommandAsync("SAVE " + name + " " + type);
        }
    }

    /**
     * Action for LOAD path.
     * I let the user type it or pick it with the file chooser.
     */
    private class LoadAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        LoadAction() {
            super("Load");
            putValue(ACCELERATOR_KEY, KeyStroke.getKeyStroke("control O"));
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String path = pathField.getText().trim();
            if (path.isEmpty()) {
                addOut("<< Please choose a file path first");
                return;
            }
            sendCommandAsync("LOAD " + path);
        }
    }

    /**
     * Simple action when I just need to send a fixed command.
     */
    private class SimpleCommandAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        private final String command;

        SimpleCommandAction(String name, String command) {
            super(name);
            this.command = command;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            sendCommandAsync(command);
        }
    }

    /**
     * Opens a file chooser and puts the selected file in the path field.
     */
    private class PickFileAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        PickFileAction() {
            super("Browse");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            JFileChooser chooser = new JFileChooser();
            int result = chooser.showOpenDialog(MainWindow.this);
            if (result == JFileChooser.APPROVE_OPTION) {
                pathField.setText(chooser.getSelectedFile().getAbsolutePath());
            }
        }
    }

    /**
     * Clears the output area.
     */
    private class ClearAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        ClearAction() {
            super("Clear");
            putValue(ACCELERATOR_KEY, KeyStroke.getKeyStroke("control L"));
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            output.setText("");
        }
    }

    /**
     * Exits the program.
     * It also sends EXIT to the server so the server can close the connection cleanly.
     */
    private class ExitAction extends AbstractAction {
        private static final long serialVersionUID = 1L;

        ExitAction() {
            super("Exit");
            putValue(ACCELERATOR_KEY, KeyStroke.getKeyStroke("control Q"));
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            String host = hostField.getText().trim();
            int port = getPort();

            new Thread(() -> {
                try {
                    client.send(host, port, "EXIT");
                } catch (IOException ex) {
                    // ignore here, we are exiting anyway
                }
                System.exit(0);
            }).start();
        }
    }

    /**
     * Starts the interface.
     *
     * @param args not used
     */
    public static void main(String[] args) {
        System.setProperty("apple.laf.useScreenMenuBar", "true");
        SwingUtilities.invokeLater(MainWindow::new);
    }
}

/**
 * Small TCP client for my Swing interface.
 * It sends one line and reads one line back.
 */
class TcpClient {

    /**
     * Sends a command to the server and returns the response line.
     *
     * @param host server host
     * @param port server port
     * @param request request sent to the server
     * @return server response
     * @throws IOException when the connection fails
     */
    public String send(String host, int port, String request) throws IOException {
        try (Socket socket = new Socket()) {
            socket.connect(new InetSocketAddress(host, port), 2000);
            socket.setSoTimeout(4000);

            try (PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                 BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

                out.println(request);

                String response = in.readLine();
                if (response == null) return "ERROR empty response";
                return response;
            }
        }
    }
}
