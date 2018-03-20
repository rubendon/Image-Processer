package image.processing;

import java.io.*;
import java.util.TreeSet;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import static java.rmi.server.LogStream.log;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Hashtable;
import javax.activation.MimeType;
import javax.activation.MimetypesFileTypeMap;
import javax.imageio.*;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;

public class Demo extends Component implements ActionListener {

    static JTextField fileName;
    //************************************
    // List of the options(Original, Negative); correspond to the cases:
    //************************************


    int opIndex;  //option index for 
    int lastOp;
    boolean loaded;

    private BufferedImage bi, biFiltered;   // the input image saved as bi;//
    int w, h;

    public Demo() {
        loaded = false;
        de = this;
        shift = new JSlider(JSlider.VERTICAL);
        scale = new JSlider(JSlider.VERTICAL);
        choices = new JComboBox(getDescriptions());
        formats = new JComboBox(getFormats());
        panel = new JPanel();
        files = new JComboBox(de.getFiles());
        scaleLabels = new Hashtable();
        shiftLabels = new Hashtable();
        
        setSliderTables();
        GUI();
        setImage(files.getSelectedItem().toString());
        repaint();

    }
    
    public void setSliderTables(){
        //shift labels
        for(int i=-20;i<=20;i+=5){
            String str = "" + (double)i/10;
            scaleLabels.put(i, new JLabel(str));
        }
        
        //scale labels
        for(int i=-255;i<=255;i+=51){
            String str = "" + i;
            shiftLabels.put(i, new JLabel(str) );
        }
    }

    public void setImage(String name) {
        try {
            String imageName = "./src/Images/" + name;
            File input = new File(imageName);
            if (FileSystemView.getFileSystemView().getSystemTypeDescription(input).contains("RAW")) {
                bi = rawToBmp(imageName);
            } else {
                bi = ImageIO.read(input);
            }

            w = bi.getWidth(null);
            h = bi.getHeight(null);

            f.setSize(1000, 700);

            if (bi.getType() != BufferedImage.TYPE_INT_RGB) {
                BufferedImage bi2 = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
                Graphics big = bi2.getGraphics();
                big.drawImage(bi, 0, 0, null);
                biFiltered = bi = bi2;
            } else {
                System.out.println("here");
            }

            loaded = true;
            if(choices.getSelectedIndex()!=0)choices.setSelectedIndex(0);
            if(formats.getSelectedIndex()!=0)formats.setSelectedIndex(0);
            repaint();
            
        } catch (IOException e) {      // deal with the situation that th image has problem;/
            System.out.println("Image could not be read");
            System.exit(1);
        }
    }

    public Dimension getPreferredSize() {
        return new Dimension(w, h);
    }

    String[] getDescriptions() {
        return null;
        //return descs;
    }

    String[] getFiles() {
        File folder = new File("./src/Images/");
        File[] list = folder.listFiles();
        ArrayList<String> namelist = new ArrayList();

        System.out.println(list.length);

        for (int i = 0; i < list.length; i++) {
            if (list[i].isFile()) {
                String type = FileSystemView.getFileSystemView().getSystemTypeDescription(list[i]);
                namelist.add(list[i].getName());
                System.out.println(type);
            }
        }
        String[] ret = new String[namelist.size()];
        for (int i = 0; i < ret.length; i++) {
            ret[i] = namelist.get(i);
        }

        return ret;
    }

    // Return the formats sorted alphabetically and in lower case
    public String[] getFormats() {
        String[] formats = {"bmp", "gif", "jpeg", "jpg", "png"};
        TreeSet<String> formatSet = new TreeSet<String>();
        for (String s : formats) {
            formatSet.add(s.toLowerCase());
        }
        return formatSet.toArray(new String[0]);
    }

    void setOpIndex(int i) {
        opIndex = i;
    }

    public void paint(Graphics g) { //  Repaint will call this function so the image will change.
        filterImage();

        g.drawImage(biFiltered, 0, 0, null);
    }

    //************************************
    //  Convert the Buffered Image to Array
    //************************************
    private static int[][][] convertToArray(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();

        int[][][] result = new int[width][height][4];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int p = image.getRGB(x, y);
                int a = (p >> 24) & 0xff;
                int r = (p >> 16) & 0xff;
                int g = (p >> 8) & 0xff;
                int b = p & 0xff;

                result[x][y][0] = a;
                result[x][y][1] = r;
                result[x][y][2] = g;
                result[x][y][3] = b;
            }
        }
        return result;
    }

    //************************************
    //  Convert the  Array to BufferedImage
    //************************************
    public BufferedImage convertToBimage(int[][][] TmpArray) {

        int width = TmpArray.length;
        int height = TmpArray[0].length;

        BufferedImage tmpimg = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int a = TmpArray[x][y][0];
                int r = TmpArray[x][y][1];
                int g = TmpArray[x][y][2];
                int b = TmpArray[x][y][3];

                //set RGB value
                int p = (a << 24) | (r << 16) | (g << 8) | b;
                tmpimg.setRGB(x, y, p);

            }
        }
        return tmpimg;
    }

    //************************************
    //  Example:  Image Negative
    //************************************
    public BufferedImage ImageNegative(BufferedImage timg) {
        int width = timg.getWidth();
        int height = timg.getHeight();

        int[][][] ImageArray = convertToArray(timg);          //  Convert the image to array

        // Image Negative Operation:
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                ImageArray[x][y][1] = 255 - ImageArray[x][y][1];  //r
                ImageArray[x][y][2] = 255 - ImageArray[x][y][2];  //g
                ImageArray[x][y][3] = 255 - ImageArray[x][y][3];  //b
            }
        }

        return convertToBimage(ImageArray);  // Convert the array to BufferedImage
    }

    public void filterImage() {

        if (opIndex == lastOp) {
            return;
        }

        lastOp = opIndex;
        switch (opIndex) {
            case 0:
                biFiltered = bi;
                /* original */
                return;
            case 1:
                biFiltered = ImageNegative(bi);
                /* Image Negative */
                return;
            //************************************
            // case 2:
            //      return;
            //************************************

        }

    }

    public BufferedImage rescaleImage(BufferedImage image, float scale) {
        if (scale == 1) return image;
        //convert buffered image to array.
        int[][][] arr = convertToArray(image);
        //loop through all pixels.
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[1].length; j++) {
                //loop through red, blue and green.
                for (int k = 1; k < 4; k++) {
                    int color = arr[i][j][k];
                    color = (int) (color * scale); //multiply colour by scale.
                    if (color > 255) {
                        arr[i][j][k] = 255; //max colour value 255.
                    } else if (color < 0) {
                        arr[i][j][k] = 0; //min colour value 0.
                    } else {
                        arr[i][j][k] = color; //set new colour value.
                    }
                }
            }
        }
        return convertToBimage(arr); //return array
    }

    public BufferedImage shiftImage(BufferedImage image, int shift) {
        if (shift == 0) return image;
        //convert buffered image to array.
        int[][][] arr = convertToArray(image);
        //loop through all pixels.
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[0].length; j++) {
                //loop through red, blue and green.
                for (int num = 1; num < 4; num++) {
                    int color = arr[i][j][num];
                    color = color + shift; //shift colour by integer.
                    if (color > 255) {
                        arr[i][j][num] = 255; //max colour value 255.
                    } else if (color < 0) {
                        arr[i][j][num] = 0; //min colour value 0.
                    } else {
                        arr[i][j][num] = color; //set new colour value.
                    }
                }
            }
        }
        return convertToBimage(arr);
    }

    public void actionPerformed(ActionEvent e) {
        JComboBox cb = (JComboBox) e.getSource();

        if (cb.getActionCommand().equals("SetFilter")) {
            setOpIndex(cb.getSelectedIndex());
            repaint();
        } else if (cb.getActionCommand().equals("Formats")) {
            String format = (String) cb.getSelectedItem();
            File saveFile = new File("savedimage." + format);
            JFileChooser chooser = new JFileChooser();
            chooser.setSelectedFile(saveFile);
            int rval = chooser.showSaveDialog(cb);
            if (rval == JFileChooser.APPROVE_OPTION) {
                saveFile = chooser.getSelectedFile();
                try {
                    ImageIO.write(biFiltered, format, saveFile);
                } catch (IOException ex) {
                }
            }
        } else if (cb.getActionCommand().equals("SetFile")) {
            setImage((String) cb.getSelectedItem());
        }
    }

    public BufferedImage rawToBmp(String name) throws IOException {
        Path path = Paths.get(name);
        byte[] bytes = Files.readAllBytes(path);
        int guessX = 0, guessY = 0, diff = bytes.length;

        //guess height and width by the 2 closest factors
        for (int i = 2; i < bytes.length; i++) {
            if (bytes.length % i == 0) {
                int x = bytes.length / i;
                if (i > x) {
                    break;
                }

                if (Math.abs(x - i) < diff) {
                    diff = x - i;
                    guessX = i;
                    guessY = x;
                }
            }
        }
        //create array of x, y, a, r, g, b values
        int[][][] result = new int[guessX][guessY][4];
        int x = 0;
        int y = 0;
        for (int i = 0; i < bytes.length; i++) {
            if (x == guessX) {
                x = 0;
                y++;
            }
            int grey = bytes[i];
            result[x][y][0] = 255;
            result[x][y][1] = grey;
            result[x][y][2] = grey;
            result[x][y][3] = grey;
            x++;
        }

        //convert bytes to buffered image(bmp)
        BufferedImage tmpimg = new BufferedImage(guessX, guessY, BufferedImage.TYPE_USHORT_GRAY);
        for (int y1 = 0; y1 < guessX; y1++) {
            for (int x1 = 0; x1 < guessY; x1++) {
                int a = 255;
                int r = result[x1][y1][1];
                int g = result[x1][y1][2];
                int b = result[x1][y1][3];

                //set RGB value
                int p = (a << 24) | (r << 16) | (g << 8) | b;
                tmpimg.setRGB(x1, y1, p);

            }
        }
        return tmpimg;
    }

    private Demo de;
    private JFrame f;
    private JPanel panel;
    private JPanel sliders;
    private JComboBox files;
    private JComboBox choices;
    private JComboBox filters;
    private JComboBox formats;
    private JSlider shift;
    private JSlider scale;       
    Hashtable shiftLabels;
    Hashtable scaleLabels;

    public void GUI() {
        f = new JFrame("Image Processing Demo");
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        //adds new image
        f.add("Center", de);
        //combo box with files
        files.setActionCommand("SetFile");
        files.addActionListener(de);
        //slider for image shift
        shift.setMaximum(255);
        shift.setMinimum(-255);
        shift.setMajorTickSpacing(51);
        shift.setLabelTable(shiftLabels);
        shift.setPaintTicks(true);
        shift.setPaintLabels(true);
        //slider for scale
        scale.setMaximum(20);
        scale.setMinimum(-20);
        scale.setMajorTickSpacing(5);
        scale.setLabelTable(scaleLabels);
        scale.setPaintTicks(true);
        scale.setPaintLabels(true);
        //combo boxes with filters
        choices.setActionCommand("SetFilter");
        choices.addActionListener(de);
        //combo box with formats
        formats.setActionCommand("Formats");
        formats.addActionListener(de);
        //panel for options
        panel.add(new JLabel("Select File"));
        panel.add(files);
        panel.add(choices);
        panel.add(new JLabel("Save As"));
        panel.add(formats);
        //set frame
        f.add("North", panel);
        f.pack();
        f.setVisible(true);
        f.setResizable(false);
    }

    public void multiplyImage(BufferedImage image, BufferedImage image1) {
        int[][][] arr = convertToArray(image);
        int[][][] arr1 = convertToArray(image1);
        int[][][] result = convertToArray(image);

        //get width and heights of image
        int width = arr.length, height = arr[0].length;
        int width1 = arr1.length, height1 = arr1[0].length;

        //find portion to multiply
        int x = (width < width1) ? width : width1;
        int y = (height < height1) ? height : height1;

        //set all to 0
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int rgb= 1; rgb < 4; rgb++) {
                    result[i][j][rgb] = 0;
                }
            }
        }

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < y; k++) {
                    for(int rgb=1; rgb<4;rgb++){
                        result[i][j][rgb] += arr[i][k][rgb] * arr1[i][k][rgb];
                    }
                }
            }
        }

    }

    public void addImage(BufferedImage image, BufferedImage image1) {
        subadd(image, image1, 0);
    }

    public void subtractImage(BufferedImage image, BufferedImage image1) {
        subadd(image, image1, 1);
    }

    public void subadd(BufferedImage image, BufferedImage image1, int subadd) {
        int[][][] arr = convertToArray(image);
        int[][][] arr1 = convertToArray(image1);
        int width = arr.length, height = arr[0].length;
        int width1 = arr1.length, height1 = arr1[0].length;

        int x = (width < width1) ? width : width1;
        int y = (height < height1) ? height : height1;

        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                for (int k = 1; k < 4; k++) {
                    if (subadd == 0) {
                        arr[j][i][k] += arr1[j][i][k];
                        if (arr[j][i][k] > 255) {
                            arr[j][i][k] = 255;
                        }
                    } else {
                        arr[j][i][k] -= arr1[j][i][k];
                        if (arr[j][i][k] < 0) {
                            arr[j][i][k] = 0;
                        }
                    }
                }
            }
        }
    }
}
