//PACKAGE
package image.processing;

//IMPORTS
import java.io.*;
import java.awt.*;
import java.awt.image.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import javax.imageio.*;
import javax.swing.filechooser.FileSystemView;

//PROCESSOR - 
//CLASS FOR STORING BUFFERED IMAGE AND CALLING OPERATIONS ON AN IMAGE FOR DISPLAY
//METHODS ORDERED BY LAB
public class Processor extends Component {

    private BufferedImage ROI = null;

    public BufferedImage setROI(BufferedImage image, BufferedImage roi) {
        int height = roi.getHeight();
        int width = roi.getWidth();
        int height1 = image.getHeight();
        int width1 = image.getWidth();
        BufferedImage newROI = new BufferedImage(width1, height1, BufferedImage.TYPE_INT_ARGB);
        for (int y = 0; y < height1; y++) {
            for (int x = 0; x < width1; x++) {
                int p = roi.getRGB(x, y);
                int a = (p >> 24) & 0xff;
                int r = (p >> 16) & 0xff;
                int g = (p >> 8) & 0xff;
                int b = p & 0xff;

                int p1 = image.getRGB(x, y);
                int a1 = (p1 >> 24) & 0xff;
                int r1 = (p1 >> 16) & 0xff;
                int g1 = (p1 >> 8) & 0xff;
                int b1 = p1 & 0xff;

                if (r == 0) {
                    a1 = 0;
                } else {
                    a1 = 255;
                }
                int p2 = (a1 << 24) | (r1 << 16) | (g1 << 8) | b1;
                newROI.setRGB(x, y, p2);
            }
        }
        return newROI;
    }

    public BufferedImage flipROI(BufferedImage roi) {
        if (roi != null) {
            int height = roi.getHeight();
            int width = roi.getWidth();
            BufferedImage newROI = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int p = roi.getRGB(x, y);
                    int a = (p >> 24) & 0xff;
                    int r = (p >> 16) & 0xff;
                    int g = (p >> 8) & 0xff;
                    int b = p & 0xff;

                    if (r == 255) {
                        a = 0;
                        r = 0;
                        g = 0;
                        b = 0;
                    } else {
                        a = 255;
                        r = 255;
                        g = 255;
                        b = 255;
                    }
                    int p2 = (a << 24) | (r << 16) | (g << 8) | b;
                    newROI.setRGB(x, y, p2);
                }
            }
            return newROI;
        }
        return null;
    }

    //DEFAULT METHODS
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

    public BufferedImage addToImage(BufferedImage image, BufferedImage roi) {
        int width = image.getWidth(), height = image.getHeight();
        int width1 = roi.getWidth(), height1 = roi.getHeight();

        int[][][] original = convertToArray(image);

        int maxw = (width < width1) ? width : width1; //get area to add
        int maxh = (height < height1) ? height : height1;

        BufferedImage result = new BufferedImage(width, height, 1);
        //loop through all pixels.
        int min = 255;
        int max = 0;
        for (int y = 0; y < maxh; y++) {
            for (int x = 0; x < maxw; x++) {
                int p = image.getRGB(x, y);
                int a = (p >> 24) & 0xff;
                int r = (p >> 16) & 0xff;
                int g = (p >> 8) & 0xff;
                int b = p & 0xff;

                int p1 = roi.getRGB(x, y);
                int a1 = (p1 >> 24) & 0xff;
                int r1 = (p1 >> 16) & 0xff;
                int g1 = (p1 >> 8) & 0xff;
                int b1 = p1 & 0xff;

                if (a1 == 0) { //if black ignore
                    original[x][y][1] = r;
                    original[x][y][2] = g;
                    original[x][y][3] = b;
                } else { //if white add filter
                    original[x][y][1] = r1;
                    original[x][y][2] = g1;
                    original[x][y][3] = b1;
                }

            }
        }
        return convertToBimage(original);
    }

    public BufferedImage convertToBimage(int[][][] TmpArray) {

        int width = TmpArray.length;
        int height = TmpArray[0].length;

        BufferedImage tmpimg = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int a = TmpArray[x][y][0];
                int r = TmpArray[x][y][1];
                int g = TmpArray[x][y][2];
                int b = TmpArray[x][y][3];

                if (r > 255) {
                    r = 255;
                }
                if (g > 255) {
                    g = 255;
                }
                if (b > 255) {
                    b = 255;
                }

                if (r < 0) {
                    r = 0;
                }
                if (g < 0) {
                    g = 0;
                }
                if (b < 0) {
                    b = 0;
                }

                //set RGB value
                int p = (a << 24) | (r << 16) | (g << 8) | b;
                tmpimg.setRGB(x, y, p);

            }
        }
        return tmpimg;
    }

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

    //LAB 1
    public BufferedImage rawToBI(String name) throws IOException {
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
            int grey = bytes[i] & 0xff;
            result[x][y][0] = 255;
            result[x][y][1] = grey;
            result[x][y][2] = grey;
            result[x][y][3] = grey;
            x++;
        }

        //convert bytes to buffered image(bmp)
        BufferedImage tmpimg = new BufferedImage(guessX, guessY, BufferedImage.TYPE_INT_RGB);
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
    } //LAB 1 - PROCESS A RAW IMAGE

    public int[][][] rescaleImage(int[][][] image, float scale) {
        int height = image[0].length;
        int width = image.length;
        BufferedImage result = new BufferedImage(width, height, 1);
        //loop through all pixels.
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int a = image[x][y][0];
                int r = image[x][y][1];
                int g = image[x][y][2];
                int b = image[x][y][3];

                r = (int) (r * scale);
                g = (int) (g * scale);
                b = (int) (b * scale);

                image[x][y][0] = a;
                image[x][y][1] = r;
                image[x][y][2] = g;
                image[x][y][3] = b;
            }
        }
        return image; //return array
    } //LAB 2 - RESCALE IMAGE

    //LAB 2
    public BufferedImage rescaleImage(BufferedImage image, float scale) {
        int[][][] arr = convertToArray(image);
        return convertToBimage(rescaleImage(arr, scale));//return array
    } //LAB 2 - RESCALE IMAGE

    public int[][][] shiftImage(int[][][] arr, int shift) {
        int height = arr[0].length;
        int width = arr.length;
        BufferedImage result = new BufferedImage(width, height, 1);
        //loop through all pixels.
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int a = arr[x][y][0];
                int r = arr[x][y][1];
                int g = arr[x][y][2];
                int b = arr[x][y][3];

                r += shift;
                g += shift;
                b += shift;

                arr[x][y][0] = a;
                arr[x][y][1] = r;
                arr[x][y][2] = g;
                arr[x][y][3] = b;
            }
        }
        return arr; //return array
    }

    public BufferedImage shiftImage(BufferedImage image, int shift) {
        int[][][] arr = convertToArray(image);
        return convertToBimage(shiftImage(arr, shift));
    } //LAB 2 - SHIFT IMAGE

    public BufferedImage arithmetic(BufferedImage image, BufferedImage image1, int type) {
        int width = image.getWidth(), height = image.getHeight();
        int width1 = image1.getWidth(), height1 = image1.getHeight();

        int[][][] original = convertToArray(image);
        int[][][] arr = convertToArray(image);

        int x = (width < width1) ? width : width1; //get area to add
        int y = (height < height1) ? height : height1;

        BufferedImage result = new BufferedImage(width, height, 1);
        //loop through all pixels.
        int min = 255;
        int max = 0;
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                int p = image.getRGB(j, i);
                int a = (p >> 24) & 0xff;
                int r = (p >> 16) & 0xff;
                int g = (p >> 8) & 0xff;
                int b = p & 0xff;
                int p1 = image1.getRGB(j, i);
                int a1 = (p1 >> 24) & 0xff;
                int r1 = (p1 >> 16) & 0xff;
                int g1 = (p1 >> 8) & 0xff;
                int b1 = p1 & 0xff;

                int r2;
                int g2;
                int b2;

                if (type == 0) { //add
                    r2 = r + r1;
                    g2 = g + g1;
                    b2 = b + b1;
                } else if (type == 1) {
                    r2 = r - r1;
                    g2 = g - g1;
                    b2 = b - b1;
                } else if (type == 2) {
                    r2 = r * r1;
                    g2 = g * g1;
                    b2 = b * b1;
                } else {
                    r2 = (r1 != 0) ? r / r1 : 510;
                    g2 = (g1 != 0) ? g / g1 : 510;
                    b2 = (b1 != 0) ? b / b1 : 510;
                }

                if (r2 < min) {
                    min = r2;
                }
                if (r2 > max) {
                    max = r2;
                }
                if (g2 < min) {
                    min = g2;
                }
                if (g2 > max) {
                    max = g2;
                }
                if (b2 < min) {
                    min = b2;
                }
                if (b2 > max) {
                    max = b2;
                }

                arr[j][i][0] = a;
                arr[j][i][1] = r2;
                arr[j][i][2] = g2;
                arr[j][i][3] = b2;
            }
        }
        int diff = max - min;
        float scale = (255 / (float) diff);
        arr = shiftImage(arr, -min);
        if (diff == 0) {
            diff = 1;
        }
        System.out.println(255 / diff);
        arr = rescaleImage(arr, scale); // multiple by 255 and divide by difference

        return convertToBimage(arr); //return array
    } //LAB 3 - SUBTRACT/ADD IMAGE

    public BufferedImage bitwiseNOT(BufferedImage image) {
        //convert buffered image to array.
        int[][][] arr = convertToArray(image);
        //loop through all pixels.
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[0].length; j++) {
                arr[j][i][1] = ~arr[j][i][1] & 0xff;
                arr[j][i][2] = ~arr[j][i][2] & 0xff;
                arr[j][i][3] = ~arr[j][i][3] & 0xff;
            }
        }
        return convertToBimage(arr);
    } //LAB 3 - BITWISE NOT

    public BufferedImage bitwiseAND(BufferedImage image, BufferedImage image1) {
        int[][][] arr = convertToArray(image);
        int[][][] arr1 = convertToArray(image1);

        int width = arr.length, height = arr[0].length;
        int width1 = arr1.length, height1 = arr1[0].length;

        int x = (width < width1) ? width : width1; //get area to add
        int y = (height < height1) ? height : height1;

        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                arr[j][i][1] = arr[j][i][1] & arr1[j][i][1] & 0xff;
                arr[j][i][2] = arr[j][i][2] & arr1[j][i][2] & 0xff;
                arr[j][i][3] = arr[j][i][3] & arr1[j][i][3] & 0xff;
            }
        }
        return convertToBimage(arr);
    } //LAB 3 - BITWISE AND

    public BufferedImage bitwiseOR(BufferedImage image, BufferedImage image1) {
        int[][][] arr = convertToArray(image);
        int[][][] arr1 = convertToArray(image1);

        int width = arr.length, height = arr[0].length;
        int width1 = arr1.length, height1 = arr1[0].length;

        int x = (width < width1) ? width : width1; //get area to add
        int y = (height < height1) ? height : height1;

        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                arr[j][i][1] = arr[j][i][1] | arr1[j][i][1] & 0xff;
                arr[j][i][2] = arr[j][i][2] | arr1[j][i][2] & 0xff;
                arr[j][i][3] = arr[j][i][3] | arr1[j][i][3] & 0xff;
            }
        }
        return convertToBimage(arr);
    } //LAB 3 - BITWISE OR

    public BufferedImage bitwiseXOR(BufferedImage image, BufferedImage image1) {
        int[][][] arr = convertToArray(image);
        int[][][] arr1 = convertToArray(image1);

        int width = arr.length, height = arr[0].length;
        int width1 = arr1.length, height1 = arr1[0].length;

        int x = (width < width1) ? width : width1; //get area to add
        int y = (height < height1) ? height : height1;

        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                arr[j][i][1] = arr[j][i][1] ^ arr1[j][i][1] & 0xff;
                arr[j][i][2] = arr[j][i][2] ^ arr1[j][i][2] & 0xff;
                arr[j][i][3] = arr[j][i][3] ^ arr1[j][i][3] & 0xff;
            }
        }
        return convertToBimage(arr);
    } //LAB 3 - BITWISE XOR

    //NEED TO DO - ROI REGION OF INTEREST LAB 3.
    //LAB 4
    public BufferedImage logarithm(BufferedImage image, int c) {
        //convert buffered image to array.
        int[][][] arr = convertToArray(image);
        //loop through all pixels.
        for (int i = 0; i < arr[0].length; i++) {
            for (int j = 0; j < arr.length; j++) {
                arr[j][i][1] = (int) (c * Math.log(1 + arr[j][i][1]));
                arr[j][i][2] = (int) (c * Math.log(1 + arr[j][i][2]));
                arr[j][i][3] = (int) (c * Math.log(1 + arr[j][i][3]));
            }
        }
        return convertToBimage(arr); //return array
    } //LAB 4 - LOGARITH FUNCTION

    public BufferedImage powerLaw(BufferedImage image, float c, double p) {
        //convert buffered image to array.
        int[][][] arr = convertToArray(image);
        //loop through all pixels.
        for (int i = 0; i < arr[0].length; i++) {
            for (int j = 0; j < arr.length; j++) {
                arr[j][i][1] = (int) (c * Math.pow(arr[j][i][1], p));
                arr[j][i][2] = (int) (c * Math.pow(arr[j][i][2], p));
                arr[j][i][3] = (int) (c * Math.pow(arr[j][i][3], p));
            }
        }
        return convertToBimage(arr); //return array
    } //LAB 4 - POWER LAW FUNCTION

    public BufferedImage randomLookupTable(BufferedImage image) {
        //convert buffered image to array.
        int[][][] arr = convertToArray(image);
        //set random table values
        int[] random = new int[256];
        Random r = new Random();
        for (int i = 0; i < random.length; i++) {
            random[i] = r.nextInt(255); //random from 0-255
        }
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[1].length; j++) {
                //loop through red, blue and green.
                for (int k = 1; k < 4; k++) {
                    int color = arr[i][j][k]; //set values to lookup table values
                    color = random[color];
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
    } //LAB 4 - RANDOM LOOKUP TABLE

    public BufferedImage bitPlaneSlicing(BufferedImage image, int bit) {
        int[][][] arr = convertToArray(image);
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                arr[x][y][1] = (arr[x][y][1] >> bit) & 1;
                arr[x][y][2] = (arr[x][y][2] >> bit) & 1;
                arr[x][y][3] = (arr[x][y][3] >> bit) & 1;
                if (arr[x][y][1] == 1) {
                    arr[x][y][1] = 255;
                }
                if (arr[x][y][2] == 1) {
                    arr[x][y][2] = 255;
                }
                if (arr[x][y][3] == 1) {
                    arr[x][y][3] = 255;
                }
            }
        }
        return convertToBimage(arr);
    } //LAB 4 - BIT-PLANE SLICING

    //LAB 5
    public double[][] getHistogram(BufferedImage image) {
        int[][][] arr = convertToArray(image);
        double[][] rgbCount = new double[3][256];
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                rgbCount[0][arr[x][y][1]]++;
                rgbCount[1][arr[x][y][2]]++;
                rgbCount[2][arr[x][y][3]]++;
            }
        }
        return rgbCount;
    } //LAB 5 - FINDING HISTOGRAM

    public double[][] normalisedHistogram(BufferedImage image) {
        double[][] rgbCount = getHistogram(image);
        int size = image.getHeight() * image.getWidth();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j <= 255; j++) {
                rgbCount[i][j] /= size; //normalise
            }
        }
        return rgbCount;
    } //LAB 5 - NORMALISING HISTOGRAM

    public BufferedImage equalizedHistogram(BufferedImage image) {
        int height = image.getHeight();
        int width = image.getWidth();
        int[][][] arr = convertToArray(image);
        double[][] rgbCount = normalisedHistogram(image);
        double[][] lookup = new double[rgbCount.length][rgbCount[0].length];
        //create cumulative frequency
        lookup[0][0] = rgbCount[0][0];
        lookup[1][0] = rgbCount[1][0];
        lookup[2][0] = rgbCount[2][0];
        for (int i = 1; i < rgbCount[0].length; i++) {
            for (int col = 0; col < 3; col++) {
                lookup[col][i] = lookup[col][i - 1] + rgbCount[col][i]; //adds last frequency and current frequency
            }
        }
        for (int i = 1; i < rgbCount[0].length; i++) {
            for (int col = 0; col < 3; col++) {
                lookup[col][i] = (int) (lookup[col][i] * 255); //multiply by max value
            }
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int i = 1; i < 4; i++) {
                    arr[x][y][i] = (int) lookup[i - 1][arr[x][y][i]]; //set value to the lookup table value for that color
                }
            }
        }
        return convertToBimage(arr);
    } //LAB 5 - EQUALISING HISTOGRAM

    //LAB 6
    public BufferedImage ImageConvolution(BufferedImage image, String type) {
        int[][] template = getTemplate(type); //gets template we are using
        int[][] template1 = new int[3][3];
        if (type == "Roberts") {
            template1 = getTemplate("Roberts1");
        }
        int height = image.getHeight();
        int width = image.getWidth();
        int sum = 0;
        for (int i = 0; i < template.length; i++) {
            for (int j = 0; j < template.length; j++) {
                sum += template[i][j]; //get sum of kernel for division
            }
        }
        if (sum == 0) {
            sum = 1; //if sum is 0 set to 1
        }

        int[][][] original = convertToArray(image);
        int[][][] padded = new int[width + 2][height + 2][4];
        int[][][] tempPadded = new int[width + 2][height + 2][4];
        //add padding
        for (int y = 0; y < height + 2; y++) {
            for (int x = 0; x < width + 2; x++) {
                for (int i = 0; i < 4; i++) {
                    if (x == 0 || y == 0 || x == width + 1 || y == height + 1) { //if an edge pixel
                        padded[x][y][i] = 0; //set edge to 0 for padding
                        tempPadded[x][y][i] = 255;
                    } else {
                        padded[x][y][i] = original[x - 1][y - 1][i]; //-1 to ignore padding
                        tempPadded[x][y][i] = original[x - 1][y - 1][i];
                    }
                }
            }
        }

        //loop through all pixels ignoring edge pixels (padding)
        for (int y = 1; y < height + 1; y++) {
            for (int x = 1; x < width + 1; x++) {
                int count[] = new int[]{0, 0, 0};
                for (int i = 0; i < template.length; i++) //loop through 3x3 kernel, return count of multiplying by kernel.
                {
                    for (int j = 0; j < template.length; j++) {
                        count[0] += tempPadded[x + i - 1][y + j - 1][1] * template[i][j]; //multiply 0,0 by 0,0 in the kernel and add to count
                        count[1] += tempPadded[x + i - 1][y + j - 1][2] * template[i][j]; //multiply 0,0 by 0,0 in the kernel and add to count
                        count[2] += tempPadded[x + i - 1][y + j - 1][3] * template[i][j]; //multiply 0,0 by 0,0 in the kernel and add to count
                    }
                }
                for (int i = 0; i < 3; i++) {
                    if (type == "Sobel X" || type == "Sobel Y") {
                        original[x - 1][y - 1][i + 1] = Math.abs(count[i] / sum); //sets colour value to count / sum of the kernel
                    } else {
                        original[x - 1][y - 1][i + 1] = count[i] / sum; //sets colour value to count / sum of the kernel
                    }
                }
            }
        }
        //if roberts
        if (type == "Roberts") {
            for (int y = 1; y < height + 1; y++) {
                for (int x = 1; x < width + 1; x++) {
                    int count[] = new int[]{0, 0, 0};
                    for (int i = 0; i < template.length; i++) //loop through 3x3 kernel, return count of multiplying by kernel.
                    {
                        for (int j = 0; j < template.length; j++) {
                            count[0] += tempPadded[x + i - 1][y + j - 1][1] * template1[i][j]; //multiply 0,0 by 0,0 in the kernel and add to count
                            count[1] += tempPadded[x + i - 1][y + j - 1][2] * template1[i][j]; //multiply 0,0 by 0,0 in the kernel and add to count
                            count[2] += tempPadded[x + i - 1][y + j - 1][3] * template1[i][j]; //multiply 0,0 by 0,0 in the kernel and add to count
                        }
                    }
                    for (int i = 0; i < 3; i++) {
                        original[x - 1][y - 1][i + 1] = Math.abs(count[i] / sum); //sets colour value to count / sum of the kernel
                    }
                }
            }
        }
        return convertToBimage(original);
    } //LAB 6 - IMAGE CONVOLUTION

    public int[][] getTemplate(String name) {
        String[] filters = linearFilters();
        switch (name) {
            case "Averaging":
                return new int[][]{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
            case "Weighted Averaging":
                return new int[][]{{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
            case "4-neighbour Laplacian":
                return new int[][]{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
            case "8-neighbour Laplacian":
                return new int[][]{{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
            case "4-neighbour Laplacian Enhancement":
                return new int[][]{{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
            case "8-neighbour Laplacian Enhancement":
                return new int[][]{{-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}};
            case "Roberts":
                return new int[][]{{0, 0, 0}, {0, 0, -1}, {0, 1, 0}};
            case "Roberts1":
                return new int[][]{{0, 0, 0}, {0, -1, 0}, {0, 0, 1}};
            case "Sobel X":
                return new int[][]{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            case "Sobel Y":
                return new int[][]{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
        }
        return null;
    } //LAB 6 - GET KERNEL TEMPLATE

    public String[] linearFilters() {
        return new String[]{
            "Averaging", "Weighted Averaging",
            "4-neighbour Laplacian", "8-neighbour Laplacian",
            "4-neighbour Laplacian Enhancement", "8-neighbour Laplacian Enhancement",
            "Roberts", "Roberts1",
            "Sobel X", "Sobel Y"
        };
    }

    //LAB 7
    public BufferedImage addSaltAndPepper(BufferedImage image) {
        int[][][] arr = convertToArray(image);
        int height = image.getHeight();
        int width = image.getWidth();
        Random r = new Random();

        int noise = height * width / 10;
        for (int i = 0; i < noise; i++) { //loop through n times
            int x = r.nextInt(width); //get random x and y coordinate
            int y = r.nextInt(height);
            int type = r.nextInt(5); //get chance of being salt or pepper
            if (type == 1) {
                for (int colour = 1; colour < 4; colour++) {
                    arr[x][y][colour] = 255; //set to salt
                }
            } else if (type == 3) {
                for (int colour = 1; colour < 4; colour++) {
                    arr[x][y][colour] = 0; //set to pepper
                }
            }
        }
        return convertToBimage(arr);
    } //LAB 7 - ADD SALT AND PEPPER NOISE

    public BufferedImage orderStatistic(BufferedImage image, int type) {
        int[][][] original = convertToArray(image);
        int width = image.getWidth();
        int height = image.getHeight();
        int size = 3;
        int[][][] array = convertToArray(image);

        //loop through all pixels ignoring edge pixels (padding)
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                ArrayList<Integer> reds = new ArrayList<>();
                ArrayList<Integer> greens = new ArrayList<>();
                ArrayList<Integer> blues = new ArrayList<>();
                for (int mx = -1; mx < size - 1; mx++) //loop through 3x3 kernel, return count of multiplying by kernel.
                {
                    for (int my = -1; my < size - 1; my++) {
                        if (x + mx != -1 && y + my != -1 && x + mx != width && y + my != height) {
                            reds.add(array[x + mx][y + my][1]);
                            greens.add(array[x + mx][y + my][2]);
                            blues.add(array[x + mx][y + my][3]);
                        }
                    }
                }
                if (type == 0) { //if min
                    original[x][y][1] = getMin(reds);
                    original[x][y][2] = getMin(greens);
                    original[x][y][3] = getMin(blues);
                } else if (type == 1) { //if max
                    original[x][y][1] = getMax(reds);
                    original[x][y][2] = getMax(greens);
                    original[x][y][3] = getMax(blues);
                } else if (type == 2) { //if mid
                    original[x][y][1] = (getMax(reds) + getMin(reds)) / 2;
                    original[x][y][2] = (getMax(greens) + getMin(greens)) / 2;
                    original[x][y][3] = (getMax(blues) + getMin(blues)) / 2;;
                } else if (type == 3) { //if median
                    original[x][y][1] = getMedian(reds);
                    original[x][y][2] = getMedian(greens);
                    original[x][y][3] = getMedian(blues);
                }
            }
        }
        return convertToBimage(original);
    } //LAB 7 - MIN FILTERING NEEDS FIXING

    public int getMin(ArrayList<Integer> values) {
        int min = 10000;
        for (int i = 0; i < values.size(); i++) {
            if (values.get(i) < min) {
                min = values.get(i);
            }
        }
        return min;
    }

    public int getMax(ArrayList<Integer> values) {
        int max = -255;
        for (int i = 0; i < values.size(); i++) {
            if (values.get(i) > max) {
                max = values.get(i);
            }
        }
        return max;
    }

    public int getMedian(ArrayList<Integer> values) {
        int median = 0;
        Collections.sort(values); //sort values
        median = values.get((int) (values.size() / 2)); //find centre
        return median;
    }

    public BufferedImage simpleThreshold(BufferedImage image, int threshold) {
        int height = image.getHeight();
        int width = image.getWidth();
        int[][][] arr = convertToArray(image);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (((arr[x][y][1] + arr[x][y][2] + arr[x][y][3]) / 3) > threshold) {
                    arr[x][y][1] = 255;
                    arr[x][y][2] = 255;
                    arr[x][y][3] = 255;

                } else {
                    arr[x][y][1] = 0;
                    arr[x][y][2] = 0;
                    arr[x][y][3] = 0;
                }
            }
        }
        return convertToBimage(arr);
    }

    public BufferedImage automatedThreshold(BufferedImage image) {
        int height = image.getHeight();
        int width = image.getWidth();
        int[][][] arr = convertToArray(image);
        double[][] rgbCount = getHistogram(image);
        int threshold = getThreshold(rgbCount[0], 130);
        int threshold1 = getThreshold(rgbCount[1], 130);
        int threshold2 = getThreshold(rgbCount[2], 130);
        double t = (threshold + threshold1 + threshold2) / 3;
        return simpleThreshold(image, (int) t);
    }

    public int getThreshold(double[] histogram, int threshold) {
        double[] set = new double[threshold];
        double[] set1 = new double[histogram.length - threshold];

        double mean = 0;
        double mean1 = 0;
        double count = 0;
        double count1 = 0;
        for (int i = 0; i < histogram.length; i++) { //set below and above
            if (i < threshold) {
                count += histogram[i];
                mean += histogram[i] * i;
            } else {
                count1 += histogram[i];
                mean1 += histogram[i] * i;
            }
        }
        mean /= count;
        mean1 /= count1;
        System.out.println(mean);
        double avg = (float) (mean + mean1) / 2;
        System.out.println(avg);
        int newThreshold = (int) avg; //get average of two means
        if (Math.abs(newThreshold - threshold) < 1) { //predefined difference
            return newThreshold;
        } else {
            return getThreshold(histogram, newThreshold);
        }
    }
}
