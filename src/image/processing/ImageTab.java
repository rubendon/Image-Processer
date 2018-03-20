/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package image.processing;

import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Stack;
import javax.swing.border.Border;
import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.filechooser.FileSystemView;

/**
 *
 * @author Your Name <Ruben Donovan QMUL>
 */
public class ImageTab {

    private BufferedImage original;
    private BufferedImage filtered;
    private BufferedImage second;
    private Stack stack;
    private ArrayList<BufferedImage> states;
    int w;
    int h;
    Processor p;
    private JPanel panel;
    private JLabel originalImage;
    private JLabel filteredImage;
    private JLabel secondImage;
    private String name;
    private Border paddingBorder;
    private int type;
    private int height;
    private int width;
    private BufferedImage ROI;
    private BufferedImage ROIShape;

    public ImageTab(String name, BufferedImage o, BufferedImage f) {
        p = new Processor();
        ROI = null;
        stack = new Stack();
        type = 0;
        height = 500;
        width = 500;
        this.name = name;
        setImage(o, f);
    }

    public ImageTab(String name, BufferedImage o, BufferedImage f, BufferedImage s) {
        p = new Processor();
        ROI = null;
        stack = new Stack();
        type = 1;
        height = 333;
        width = 333;
        this.name = name;
        setImage(o, f, s);
    }

    public void removeROI() {
        ROIShape = null;
        ROI = null;
    }

    public void setROIShape(BufferedImage roi) {
        if (roi != null) {
            ROIShape = roi;
            ROI = p.setROI(filtered, roi);
        }
    }

    public BufferedImage getROI() {
        return ROI;
    }

    public BufferedImage getROIShape() {
        return ROIShape;
    }

    public JPanel getPanel() {
        return panel;
    }

    public BufferedImage getFilteredBI() {
        return filtered;
    }

    public String getName() {
        return name;
    }

    public void addSecond(BufferedImage s) {
        setImage(original, filtered, s);
    }
    
    public void setStack(){
        stack = new Stack();
    }

    public void setImage(BufferedImage o, BufferedImage f) {
        panel = new JPanel(false);
        original = o;
        filtered = f;
        paddingBorder = BorderFactory.createEmptyBorder(10, 10, 10, 10);
        originalImage = new JLabel("Original");
        int h = original.getHeight();
        int w = original.getWidth();
        if (w > h) {
            float scale = (float) w / (float) width;
            h = (int) (h / scale);
            w = (int) (w / scale);
        } else {
            float scale = (float) h / (float) height;
            h = (int) (h / scale);
            w = (int) (w / scale);
        }

        originalImage.setIcon(new ImageIcon(original.getScaledInstance(w, h, 1)));
        originalImage.setHorizontalTextPosition(JLabel.CENTER);
        originalImage.setVerticalTextPosition(JLabel.TOP);
        originalImage.setFont(new Font("Calibri", Font.BOLD, 20));
        originalImage.setHorizontalAlignment(JLabel.CENTER);
        originalImage.setBorder(BorderFactory.createEmptyBorder((height - h) / 2, (width - w) / 2, (height - h) / 2, (width - w) / 2));

        filteredImage = new JLabel("Filtered");
        filteredImage.setIcon(new ImageIcon(filtered.getScaledInstance(w, h, 1)));
        filteredImage.setHorizontalTextPosition(JLabel.CENTER);
        filteredImage.setVerticalTextPosition(JLabel.TOP);
        filteredImage.setFont(new Font("Calibri", Font.BOLD, 20));
        filteredImage.setHorizontalAlignment(JLabel.CENTER);
        filteredImage.setBorder(paddingBorder);
        panel.setLayout(new GridLayout(1, 2));
        panel.add(originalImage);
        panel.add(filteredImage);
    }

    public void setImage(BufferedImage o, BufferedImage f, BufferedImage s) {
        panel = new JPanel(false);
        original = o;
        filtered = f;
        second = s;
        paddingBorder = BorderFactory.createEmptyBorder(10, 10, 10, 10);
        originalImage = new JLabel("Original");
        int h = original.getHeight();
        int w = original.getWidth();
        if (w > h) {
            float scale = (float) w / (float) width;
            h = (int) (h / scale);
            w = (int) (w / scale);
        } else {
            float scale = (float) h / (float) height;
            h = (int) (h / scale);
            w = (int) (w / scale);
        }

        originalImage.setIcon(new ImageIcon(original.getScaledInstance(w, h, 1)));
        originalImage.setHorizontalTextPosition(JLabel.CENTER);
        originalImage.setVerticalTextPosition(JLabel.TOP);
        originalImage.setFont(new Font("Calibri", Font.BOLD, 20));
        originalImage.setHorizontalAlignment(JLabel.CENTER);
        originalImage.setBorder(BorderFactory.createEmptyBorder((height - h) / 2, (width - w) / 2, (height - h) / 2, (width - w) / 2));

        filteredImage = new JLabel("Filtered");
        filteredImage.setIcon(new ImageIcon(filtered.getScaledInstance(w, h, 1)));
        filteredImage.setHorizontalTextPosition(JLabel.CENTER);
        filteredImage.setVerticalTextPosition(JLabel.TOP);
        filteredImage.setFont(new Font("Calibri", Font.BOLD, 20));
        filteredImage.setHorizontalAlignment(JLabel.CENTER);
        filteredImage.setBorder(paddingBorder);

        h = second.getHeight();
        w = second.getWidth();
        if (w > h) {
            float scale = (float) w / (float) width;
            h = (int) (h / scale);
            w = (int) (w / scale);
        } else {
            float scale = (float) h / (float) height;
            h = (int) (h / scale);
            w = (int) (w / scale);
        }
        secondImage = new JLabel("Second");
        secondImage.setIcon(new ImageIcon(second.getScaledInstance(w, h, 1)));
        secondImage.setHorizontalTextPosition(JLabel.CENTER);
        secondImage.setVerticalTextPosition(JLabel.TOP);
        secondImage.setFont(new Font("Calibri", Font.BOLD, 20));
        secondImage.setHorizontalAlignment(JLabel.CENTER);
        secondImage.setBorder(paddingBorder);

        panel.setLayout(new GridLayout(1, 3));
        panel.add(originalImage);
        panel.add(secondImage);
        panel.add(filteredImage);
    }

    public BufferedImage getSecond() {
        return second;
    }

    public void setFiltered(BufferedImage f) {
        stack.add(filtered);
        if (type == 0) {
            setImage(original, f);
        } else {
            setImage(original, f, second);
        }

    }

    public int getType() {
        return type;
    }

    public void setPanel(BufferedImage o, BufferedImage f) {
        original = o;
        filtered = f;
        originalImage = new JLabel(new ImageIcon(original));
        originalImage.setHorizontalAlignment(JLabel.LEFT);
        filteredImage = new JLabel(new ImageIcon(filtered));
        filteredImage.setHorizontalAlignment(JLabel.RIGHT);
        panel.setLayout(new GridLayout(1, 2));
        panel.add(originalImage);
        panel.add(filteredImage);
    }

    public BufferedImage undo() {
        if (stack.size() == 0) {
            return filtered;
        }
        return (BufferedImage) stack.pop();
    }

    public void undoFilter(BufferedImage f) {
        if (type == 0) {
            setImage(original, f);
            if (ROI != null) {
                ROI = p.setROI(f, ROI);
            }
        } else {
            setImage(original, f, second);
            if (ROI != null) {
                ROI = p.setROI(f, ROI);
            }
        }
    }

}
