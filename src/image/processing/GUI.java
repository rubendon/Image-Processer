/*
 * To change this license heapr, choose License Heaprs in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package image.processing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.ComponentOrientation;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.LayoutManager;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.TreeSet;
import javax.imageio.ImageIO;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTabbedPane;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.filechooser.FileSystemView;
import javax.swing.plaf.FontUIResource;

/**
 *
 * @author Your Name <Ruben Donovan QMUL>
 */
public final class GUI implements ActionListener {

    // <editor-fold defaultstate="collapsed" desc="GUI Variables">
    private Processor p;
    private JFrame f;
    GridBagLayout grid = new GridBagLayout();
    private JMenuBar menuBar;
    private JMenu file;
    private JMenu newProject;
    private JMenuItem singleImage;
    private JMenuItem twoImage;
    private JMenu load;
    private JMenuItem save;
    private JMenu filters;
    private JButton undo;
    private JTabbedPane tabbedPane;

    final static boolean shouldFill = true;
    final static boolean shouldWeightX = true;
    final static boolean RIGHT_TO_LEFT = false;

    final static Color MenuText = Color.white;
    final static Color MenuBackground = new Color(105, 105, 105);
    final static Color background = new Color(66, 66, 66);
    final static Color selected = new Color(77, 77, 77);

    private int currentPanel = 0;
    private ArrayList<ImageTab> panels;
    private JMenu second;
    private JMenu twoImg;

// </editor-fold>
    public GUI() {
        panels = new ArrayList<>();
        initiateElements(); //initialize elements
        makeGUI(); //make starting gui
    }

    String[] getROI() {
        File folder = new File("./src/ROI/");
        File[] list = folder.listFiles();
        ArrayList<String> namelist = new ArrayList();

        for (int i = 0; i < list.length; i++) {
            if (list[i].isFile()) {

                String type = FileSystemView.getFileSystemView().getSystemTypeDescription(list[i]);
                namelist.add(list[i].getName());
            }
        }
        String[] ret = new String[namelist.size()];
        for (int i = 0; i < ret.length; i++) {
            ret[i] = namelist.get(i);
        }
        return ret;
    }

    String[] getFiles() {
        File folder = new File("./src/Images/");
        File[] list = folder.listFiles();
        ArrayList<String> namelist = new ArrayList();

        for (int i = 0; i < list.length; i++) {
            if (list[i].isFile()) {

                String type = FileSystemView.getFileSystemView().getSystemTypeDescription(list[i]);
                namelist.add(list[i].getName());
            }
        }
        String[] ret = new String[namelist.size()];
        for (int i = 0; i < ret.length; i++) {
            ret[i] = namelist.get(i);
        }
        return ret;
    }

    String[] getDescriptions() {
        String descs[] = {
            "Original",
            "Negative",};
        return descs;
    }

    public String[] getFormats() {
        String[] formats = {"bmp", "gif", "jpeg", "jpg", "png"};
        TreeSet<String> formatSet = new TreeSet<String>();
        for (String s : formats) {
            formatSet.add(s.toLowerCase());
        }
        return formatSet.toArray(new String[0]);
    }

    public String[] getFilters() {
        String[] filters = {
            "Rescale", "Shift", "Add Random",
            "Bitwise NOT", "ROI", "Negative",
            "Logarithm", "Power-Law",
            "Random Lookup", "BitPlane Slice", "Equalised Histogram",
            "Salt and Pepper", "Min", "Max", "Midpoint", "Median",
            "Simple Threshold", "Automated Threshold"
        };

        return filters;
    }

    public String[] getSecondFilters() {
        String[] filters = {"Add Image", "Subtract Image", "Multiply Image", "Divide Image", "Bitwise AND", "Bitwise OR", "Bitwise XOR"};

        return filters;
    }

    public BufferedImage getImage(String name) {
        String imageName = "./src/Images/" + name;
        try {
            File input = new File(imageName);
            if (FileSystemView.getFileSystemView().getSystemTypeDescription(input).contains("RAW")) {
                BufferedImage bi = p.rawToBI(imageName);
                return bi;
            } else {
                BufferedImage bi = ImageIO.read(input);
                return bi;
            }
        } catch (IOException e) {      // deal with the situation that th image has problem;/
            System.out.println("Image could not be read");
            System.exit(1);
        }
        return null;
    }

    public void actionPerformed(ActionEvent e) {
        String[] fileNames = getFiles();
        String[] roiNames = getROI();
        String command = e.getActionCommand();
        if (command.contains("file")) {
            for (int i = 0; i < fileNames.length; i++) {
                if (command.equals("file" + i)) {
                    ImageTab current = panels.get(currentPanel);
                    if (current.getType() == 0) {
                        current.setImage(getImage(fileNames[i]), getImage(fileNames[i]));
                    } else {
                        current.setImage(getImage(fileNames[i]), getImage(fileNames[i]), current.getSecond());
                    }
                    current.setStack();
                    tabbedPane.remove(currentPanel);
                    currentPanel = tabbedPane.getSelectedIndex() + 1;
                    if (currentPanel == tabbedPane.getTabCount()) {
                        tabbedPane.addTab(current.getName(), null, current.getPanel(), "");
                    } else {
                        tabbedPane.insertTab(current.getName(), null, current.getPanel(), "", currentPanel);
                    }
                    tabbedPane.setSelectedIndex(currentPanel);
                }
            }
        } else if (command.contains("Second")) {
            for (int i = 0; i < fileNames.length; i++) {
                if (command.equals("Second" + fileNames[i])) {
                    ImageTab current = panels.get(currentPanel);
                    current.addSecond(getImage(fileNames[i]));
                    tabbedPane.remove(currentPanel);
                    currentPanel = tabbedPane.getSelectedIndex() + 1;
                    if (currentPanel == tabbedPane.getTabCount()) {
                        tabbedPane.addTab(current.getName(), null, current.getPanel(), "");
                    } else {
                        tabbedPane.insertTab(current.getName(), null, current.getPanel(), "", currentPanel);
                    }
                    tabbedPane.setSelectedIndex(currentPanel);
                }
            }
        } else if (command.contains("ROI")) {
            for (int i = 0; i < roiNames.length; i++) {
                if (command.equals("ROI" + i)) {
                    ImageTab current = panels.get(currentPanel);
                    BufferedImage roiShape = getImage(roiNames[i]);
                    current.setROIShape(roiShape);
                    tabbedPane.remove(currentPanel);
                    currentPanel = tabbedPane.getSelectedIndex() + 1;
                    if (currentPanel == tabbedPane.getTabCount()) {
                        tabbedPane.addTab(current.getName(), null, current.getPanel(), "");
                    } else {
                        tabbedPane.insertTab(current.getName(), null, current.getPanel(), "", currentPanel);
                    }
                    tabbedPane.setSelectedIndex(currentPanel);
                }
            }
        } else if (command.equals("single")) {
            if (addPane(false, 0)) {
                tabbedPane.setSelectedIndex(currentPanel);
            }
        } else if (command.equals("double")) {
            if (addPane(false, 1)) {
                tabbedPane.setSelectedIndex(currentPanel);
            }
        } else if (command.contains("save")) {
            String[] formats = getFormats();
            for (int i = 0; i < formats.length; i++) {
                if (command.contains(formats[i])) {
                    ImageTab current = panels.get(currentPanel);
                    String format = formats[i];
                    File saveFile = new File("./src/Images/" + current.getName() + "." + format);
                    JFileChooser chooser = new JFileChooser();
                    chooser.setSelectedFile(saveFile);
                    saveFile = chooser.getSelectedFile();
                    try {
                        ImageIO.write(current.getFilteredBI(), format, saveFile);
                    } catch (IOException ex) {
                        JOptionPane.showMessageDialog(null, "Name/Type already in use.");
                    }
                }
            }
        } else if (command.equals("flip")) {
            ImageTab current = panels.get(currentPanel);
            current.setROIShape(p.flipROI(current.getROIShape()));
            tabbedPane.remove(currentPanel);
            currentPanel = tabbedPane.getSelectedIndex() + 1;
            if (currentPanel == tabbedPane.getTabCount()) {
                tabbedPane.addTab(current.getName(), null, current.getPanel(), "");
            } else {
                tabbedPane.insertTab(current.getName(), null, current.getPanel(), "", currentPanel);
            }
            tabbedPane.setSelectedIndex(currentPanel);
        } else {
            addFilter(command);
        }
    }

    public void addFilter(String filter) {
        String[] singlef = getFilters();
        String[] doublef = getSecondFilters();
        String[] linearf = p.linearFilters();
        if (panels.size() != 0) {
            ImageTab current = panels.get(currentPanel);
            if (filter.equals(singlef[0])) { //rescale
                float value = 10000;
                try {
                    String str = JOptionPane.showInputDialog("Choose a scale from -2 to 2");
                    if (str == null) {
                        return;
                    }
                    value = Float.parseFloat(str);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(null, "Must be a number between -2 and 2");
                    addFilter(filter);
                    return;
                }
                if (value > 2 || value < -2) {
                    JOptionPane.showMessageDialog(null, "Must be a number between -2 and 2");
                    addFilter(filter);
                    return;
                } else if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.rescaleImage(current.getROI(), value)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());

                } else {
                    current.setFiltered(p.rescaleImage(current.getFilteredBI(), value));
                }
            } else if (filter.equals(singlef[1])) {
                int value = 10000;
                try {
                    String str = JOptionPane.showInputDialog("Choose an integer from -255 to 255");
                    if (str == null) {
                        return;
                    }
                    value = Integer.parseInt(str);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(null, "Must be a number between -255 and 255");
                    addFilter(filter);
                    return;
                }
                if (value > 255 || value < -255) {
                    JOptionPane.showMessageDialog(null, "Must be a number between -255 and 255");
                    addFilter(filter);
                    return;
                } else if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.shiftImage(current.getROI(), value)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.shiftImage(current.getFilteredBI(), value));
                }
            } else if (filter.equals(singlef[3])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.bitwiseNOT(current.getROI())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.bitwiseNOT(current.getFilteredBI()));
                }
            } else if (filter.equals(singlef[5])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.ImageNegative(current.getROI())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.ImageNegative(current.getFilteredBI()));
                }
            } else if (filter.equals(singlef[6])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.logarithm(current.getROI(), 100)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.logarithm(current.getFilteredBI(), 1));
                }
            } else if (filter.equals(singlef[7])) {
                float value = 10000;
                try {
                    String str = JOptionPane.showInputDialog("Choose an power from 0 to 25");
                    if (str == null) {
                        return;
                    }
                    value = Float.parseFloat(str);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(null, "Must be a number between 0 and 25");
                    addFilter(filter);
                    return;
                }
                if (value > 25 || value <= 0) {
                    JOptionPane.showMessageDialog(null, "Must be a number between 0 and 25");
                    addFilter(filter);
                    return;
                } 
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.powerLaw(current.getROI(), 1, value)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.powerLaw(current.getFilteredBI(), 0.5f, value));
                }
            } else if (filter.equals(singlef[8])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.randomLookupTable(current.getROI())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.randomLookupTable(current.getFilteredBI()));
                }
            } else if (filter.equals(singlef[9])) {
                int value = 10000;
                try {
                    String str = JOptionPane.showInputDialog("Choose a bit from 0-7");
                    if (str == null) {
                        return;
                    }
                    value = Integer.parseInt(str);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(null, "Must be a number between 0 and 7");
                    addFilter(filter);
                    return;
                }
                if (value > 7 || value < 0) {
                    JOptionPane.showMessageDialog(null, "Must be a number between 0 and 7");
                    addFilter(filter);
                    return;
                } else if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.bitPlaneSlicing(current.getROI(), value)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.bitPlaneSlicing(current.getFilteredBI(), value));
                }
            } else if (filter.equals(singlef[10])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.equalizedHistogram(current.getROI())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.equalizedHistogram(current.getFilteredBI()));
                }
            } else if (filter.equals(singlef[11])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.addSaltAndPepper(current.getROI())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.addSaltAndPepper(current.getFilteredBI()));
                }
            } else if (filter.equals(singlef[12])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.orderStatistic(current.getROI(), 0)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.orderStatistic(current.getFilteredBI(), 0));
                }
            } else if (filter.equals(singlef[13])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.orderStatistic(current.getROI(), 1)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.orderStatistic(current.getFilteredBI(), 1));
                }
            } else if (filter.equals(singlef[14])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.orderStatistic(current.getROI(), 2)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.orderStatistic(current.getFilteredBI(), 2));
                }
            } else if (filter.equals(singlef[15])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.orderStatistic(current.getROI(), 3)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.orderStatistic(current.getFilteredBI(), 3));
                }
            } else if (filter.equals(singlef[16])) {
                int value = 10000;
                try {
                    String str = JOptionPane.showInputDialog("Choose a theshold from 1-254");
                    if (str == null) {
                        return;
                    }
                    value = Integer.parseInt(str);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(null, "Must be a number between 1 and 254");
                    addFilter(filter);
                    return;
                }
                if (value > 254 || value < 1) {
                    JOptionPane.showMessageDialog(null, "Must be a number between 1 and 254");
                    addFilter(filter);
                    return;
                } else if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.simpleThreshold(current.getROI(), value)));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.simpleThreshold(current.getFilteredBI(), value));
                }
            } else if (filter.equals(singlef[17])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.automatedThreshold(current.getROI())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.automatedThreshold(current.getFilteredBI()));
                }
            }
            for (int i = 0; i < linearf.length; i++) {
                if (filter.equals(linearf[i])) {
                    if (current.getROI() != null) {
                        current.setFiltered(p.addToImage(current.getFilteredBI(), p.ImageConvolution(current.getROI(), linearf[i])));
                        BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                        current.setROIShape(current.getROIShape());
                    } else {
                        current.setFiltered(p.ImageConvolution(current.getFilteredBI(), linearf[i]));
                    }
                }
            }
            if (filter.equals("undo")) {
                current.undoFilter(current.undo());
            }
            String[] secondFilters = getSecondFilters();
            for (int i = 0; i < 4; i++) {
                if (filter.equals(secondFilters[i])) {
                    if (current.getROI() != null) {
                        current.setFiltered(p.addToImage(current.getFilteredBI(), p.arithmetic(current.getROI(), current.getSecond(), i)));
                        BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                        current.setROIShape(current.getROIShape());
                    } else {
                        current.setFiltered(p.arithmetic(current.getFilteredBI(), current.getSecond(), i));
                    }
                }
            }
            if (filter.equals(secondFilters[4])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.bitwiseAND(current.getROI(), current.getSecond())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.bitwiseAND(current.getFilteredBI(), current.getSecond()));
                }
            }
            if (filter.equals(secondFilters[5])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.bitwiseOR(current.getROI(), current.getSecond())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.bitwiseOR(current.getFilteredBI(), current.getSecond()));
                }
            }
            if (filter.equals(secondFilters[6])) {
                if (current.getROI() != null) {
                    current.setFiltered(p.addToImage(current.getFilteredBI(), p.bitwiseXOR(current.getROI(), current.getSecond())));
                    BufferedImage roi = p.setROI(current.getFilteredBI(), current.getROIShape());
                    current.setROIShape(current.getROIShape());
                } else {
                    current.setFiltered(p.bitwiseXOR(current.getFilteredBI(), current.getSecond()));
                }
            }

            tabbedPane.remove(currentPanel);
            currentPanel = tabbedPane.getSelectedIndex() + 1;
            if (currentPanel == tabbedPane.getTabCount()) {
                tabbedPane.addTab(current.getName(), null, current.getPanel(), "");
            } else {
                tabbedPane.insertTab(current.getName(), null, current.getPanel(), "", currentPanel);
            }
            tabbedPane.setSelectedIndex(currentPanel);
        }
    }
    // <editor-fold defaultstate="collapsed" desc=" Initiating Variables ">

    private void initiateElements() {
        p = new Processor();
    }

    private void makeFrame() {
        f = new JFrame("Image Processor");

        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        // on ESC key close frame
        f.getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(
                KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "Cancel"); //$NON-NLS-1$
        f.getRootPane().getActionMap().put("Cancel", new AbstractAction() {

            public void actionPerformed(ActionEvent e) {
                System.exit(0);
                //framename.setVisible(false);
            }
        });
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Already there
        f.setUndecorated(true);
        FrameDragListener frameDragListener = new FrameDragListener(f);
        f.addMouseListener(frameDragListener);
        f.addMouseMotionListener(frameDragListener);
        f.setLocationRelativeTo(null);

        f.setSize(1280, 720);
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        f.setLocation((dim.width / 2) - (f.getSize().width / 2), dim.height / 2 - f.getSize().height / 2);

        Container pane = f.getContentPane();
        pane.setLayout(grid);
        pane.setBackground(background);
        GridBagConstraints c = new GridBagConstraints();

        if (RIGHT_TO_LEFT) {
            pane.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
        }
        if (shouldFill) {
            //natural height, maximum width
            c.fill = GridBagConstraints.HORIZONTAL;
        }
        UIManager.put("TabbedPane.selected", new Color(150, 150, 150));
        tabbedPane = new JTabbedPane();
        tabbedPane.setBackground(background);
        tabbedPane.setForeground(MenuText);
        tabbedPane.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                currentPanel = tabbedPane.getSelectedIndex();
                if (panels.size() != 0 && currentPanel >= 0) {
                    ImageTab current = panels.get(currentPanel);
                    if (current.getType() == 1) {
                        second.setEnabled(true);
                        twoImg.setEnabled(true);
                    } else {
                        second.setEnabled(false);
                        twoImg.setEnabled(false);
                    }
                }
            }
        });
        if (shouldWeightX) {
            c.weightx = 0.5;
        }
        c.ipady = 40;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 0;
        pane.add(tabbedPane, c);

        menuBar = new JMenuBar();

        //file menu
        file = new JMenu("FILE");
        file.setMnemonic(KeyEvent.VK_A);
        file.getAccessibleContext().setAccessibleDescription(
                "File Options");
        menuBar.add(file);

        newProject = new JMenu("New Project");
        newProject.setMnemonic(KeyEvent.VK_N);

        singleImage = new JMenuItem("Single Image");
        singleImage.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_2, ActionEvent.ALT_MASK));
        singleImage.setActionCommand("single");
        singleImage.addActionListener(this);
        newProject.add(singleImage);

        twoImage = new JMenuItem("Double Image");
        singleImage.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_2, ActionEvent.ALT_MASK));
        twoImage.setActionCommand("double");
        twoImage.addActionListener(this);
        newProject.add(twoImage);

        file.add(newProject);
        file.addSeparator();

        JMenu ROI = new JMenu("Add ROI");
        ROI.setMnemonic(KeyEvent.VK_L);
        String[] roiNames = getROI();
        for (int i = 0; i < roiNames.length; i++) {
            JMenuItem fileName = new JMenuItem(roiNames[i]);
            fileName.setActionCommand("ROI" + i);
            fileName.addActionListener(this);
            ROI.add(fileName);
        }
        file.add(ROI);

        setLoads(false);

        save = new JMenu("Save Image");
        String[] formats = getFormats();
        for (int i = 0; i < formats.length; i++) {
            JMenuItem format = new JMenuItem(formats[i]);
            format.setActionCommand("save" + formats[i]);
            format.addActionListener(this);
            save.add(format);
        }
        file.add(save);

        JMenuItem flip = new JMenuItem("Flip ROI");
        flip.setActionCommand("flip");
        flip.addActionListener(this);
        file.add(flip);

        //filters menu
        filters = new JMenu("FILTERS");
        filters.setMnemonic(KeyEvent.VK_A);
        filters.getAccessibleContext().setAccessibleDescription(
                "The only menu in this program that has menu items");

        filters.setForeground(MenuText);

        JMenu def = new JMenu("Default");
        String[] filterStrings = getFilters();

        for (int i = 0; i < 5; i++) {
            JMenuItem filt = new JMenuItem(filterStrings[i]);
            filt.setActionCommand(filterStrings[i]);
            filt.addActionListener(this);
            def.add(filt);
        }
        filters.add(def);

        JMenu point = new JMenu("Point Processing");

        for (int i = 5; i < 10; i++) {
            JMenuItem filt = new JMenuItem(filterStrings[i]);
            filt.setActionCommand(filterStrings[i]);
            filt.addActionListener(this);
            point.add(filt);
        }
        filters.add(point);

        JMenu linear = new JMenu("Linear Filters");
        String[] linears = p.linearFilters();
        for (int i = 0; i < linears.length; i++) {
            if (i != 7) {
                JMenuItem filt = new JMenuItem(linears[i]);
                filt.setActionCommand(linears[i]);
                filt.addActionListener(this);
                filt.setEnabled(true);
                linear.add(filt);
            }
        }
        filters.addSeparator();
        filters.add(linear);

        filters.addSeparator();
        JMenu order = new JMenu("Order Statistic");
        for (int i = 11; i < 16; i++) {
            JMenuItem filt = new JMenuItem(filterStrings[i]);
            filt.setActionCommand(filterStrings[i]);
            filt.addActionListener(this);
            order.add(filt);
        }
        filters.add(order);

        twoImg = new JMenu("Arithmetic and Boolean");
        String[] secondFilters = getSecondFilters();
        for (int i = 0; i < secondFilters.length; i++) {
            JMenuItem filt = new JMenuItem(secondFilters[i]);
            filt.setActionCommand(secondFilters[i]);
            filt.addActionListener(this);
            twoImg.add(filt);
        }
        twoImg.setEnabled(false);
        filters.add(twoImg);

        filters.addSeparator();
        JMenuItem hist = new JMenuItem(filterStrings[10]);
        hist.setActionCommand(filterStrings[10]);
        hist.addActionListener(this);
        filters.add(hist);

        JMenuItem simple = new JMenuItem(filterStrings[16]);
        simple.setActionCommand(filterStrings[16]);
        simple.addActionListener(this);
        filters.add(simple);

        JMenuItem auto = new JMenuItem(filterStrings[17]);
        auto.setActionCommand(filterStrings[17]);
        auto.addActionListener(this);
        filters.add(auto);

        menuBar.add(filters);

        JMenuItem exit = new JMenuItem("CLOSE");
        exit.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
        exit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        undo = new JButton("UNDO");
        undo.setOpaque(false);
        undo.setContentAreaFilled(false);
        undo.setBorderPainted(false);
        undo.setActionCommand("undo");
        undo.addActionListener(this);
        menuBar.add(undo);
        menuBar.add(exit);
        menuBar.setBackground(MenuBackground);
        file.setForeground(MenuText);
        undo.setForeground(MenuText);

        f.setJMenuBar(menuBar);

        addPane(true, 0);

        f.pack();

        if (shouldFill) {
            c.fill = GridBagConstraints.HORIZONTAL;
        }

        f.setVisible(true);
        f.setResizable(false);
    }

    private boolean addPane(boolean initial, int type) {
        String name;
        if (initial == true) {
            name = "Default";
        } else {
            name = JOptionPane.showInputDialog("Please Choose a name:");
            if (name.equals("")) {
                JOptionPane.showMessageDialog(null, "Name cannot be empty");
                return addPane(initial, type);
            } else {
                boolean taken = false;
                for (int i = 0; i < panels.size(); i++) {
                    if (panels.get(i).getName().equals(name)) {
                        taken = true;
                        JOptionPane.showMessageDialog(null, "Name already in use");
                        return addPane(initial, type);
                    }
                }
            }
            if (name == null) {
                return false;
            }
        }
        ImageTab tab;
        if (type == 0) {
            tab = new ImageTab(name, getImage("Baboon.bmp"), getImage("Baboon.bmp")); //create new tab set to default
            second.setEnabled(false);
            twoImg.setEnabled(false);
        } else {
            tab = new ImageTab(name, getImage("Barbara.raw"), getImage("Barbara.raw"), getImage("Baboon.bmp")); //create new tab set to default
            second.setEnabled(true);
            twoImg.setEnabled(true);
        }

        tabbedPane.addTab(name, null, tab.getPanel(), "");
        tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
        panels.add(tab);
        currentPanel = panels.size() - 1;
        f.pack();
        return true;
    }

    private void setLoads(boolean loaded) {
        load = new JMenu("Load new Image");
        load.setMnemonic(KeyEvent.VK_L);
        String[] fileNames = getFiles();
        for (int i = 0; i < fileNames.length; i++) {
            JMenuItem fileName = new JMenuItem(fileNames[i]);
            fileName.setActionCommand("file" + i);
            fileName.addActionListener(this);
            load.add(fileName);
        }
        file.add(load);

        second = new JMenu("Load Second Image");
        second.setMnemonic(KeyEvent.VK_L);

        for (int i = 0; i < fileNames.length; i++) {
            JMenuItem fileName = new JMenuItem(fileNames[i]);
            fileName.setActionCommand("Second" + fileNames[i]);
            fileName.addActionListener(this);
            second.add(fileName);
        }
        second.setEnabled(false);
        file.add(second);
    }

    private void makeGUI() {
        makeFrame();
    }
}
