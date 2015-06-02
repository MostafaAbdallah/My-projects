import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;


public class ReadImage {
	public int[][] seeBMPImage(String BMPFileName) throws IOException {
	    BufferedImage image = ImageIO.read(getClass().getResource(BMPFileName));

	    int[][] array2D = new int[image.getWidth()][image.getHeight()];

	    for (int xPixel = 0; xPixel < image.getWidth(); xPixel++)
	        {
	            for (int yPixel = 0; yPixel < image.getHeight(); yPixel++)
	            {
	                int color = image.getRGB(xPixel, yPixel);
	                color = (color >> 16) & 0xff;
	               // System.out.print(color);
	                if (color >= 1) {
	                    array2D[xPixel][yPixel] = 1;
	                } else {
	                    array2D[xPixel][yPixel] = 0; 
	                }
	            }
	            //System.out.println();
	        }
	    	return array2D;
	    }
	
	public  void writeImage(int[][] pixels,String outputFilePath)
    {
		int width = pixels.length;
		int height = pixels[0].length;
        File fileout=new File(outputFilePath);
        BufferedImage image2=new BufferedImage(width,height,BufferedImage.TYPE_BYTE_GRAY);
        int color = 0;
        for(int x=0;x<width ;x++)
        {
            for(int y=0;y<height;y++)
            {	color = pixels[x][y];
            	if(color > 0)
            		color = -255;
            	else
            		color = 255;
                image2.setRGB(x,y,color);
            }
        }
        try
        {
            ImageIO.write(image2, "bmp", fileout);
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
	
	public ArrayList<String> toVector(int [][]x){
		ArrayList<String> v = new ArrayList<String>();
		String str = "";
		int count = 0;
		for (int i = 0; i < x.length; i++) {
			for (int j = 0; j < x[i].length; j++) {
				str = str + x[i][j];
				count++;
				if(count == 128){
					v.add(str);
					str ="";
					count =0;
				}
			}
		}
		if(count != 0){
			for (int i = count; i < 128; i++) {
				
				str = str + 0;
			}
			v.add(str);
		}
		
		return v;
	}
	
	public int [][] toArray(ArrayList<String> v, int width, int height){
		int [][] x = new int[width][height];
		int count = 0;
		int it = 0;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				x[i][j] = v.get(count).charAt(it) - 48;
				
				it++;
				if(it == 128){
					it = 0;
					count++;
				}
			}
			
		}
		
		
		return x;
	}

}
