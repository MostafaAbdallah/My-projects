import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;


public class uniform {

	public void Compressed(int nlvls) {

		String b;
		String str = "";
		int it =0;
		int[][] pixels;
		ImageRW image = new ImageRW();
		writeTag w = new writeTag();
		int range = 0;
		ArrayList<Integer> tag = new ArrayList<Integer>();
		Map<Integer, Integer> q;
		
//		Scanner input = new Scanner(System.in); 
		String fileName = "lena.jpg";
		int nLevels = nlvls;
		int k = (int) (Math.log10(nLevels)/Math.log10(2));
		
		pixels = image.readImage(fileName);
		
		range = 256/nLevels;
		ArrayList<Byte> B = new ArrayList<Byte>();
		for (int i = 0; i < image.height; i++) {
			for (int j = 0; j < image.width; j++) {
				int r = pixels[i][j]/range;
				tag.add(r);
				
			}
			
		}
		w.createFile("image.txt");
		w.addRecord(tag, nLevels);
		w.closeFile();
	}
	
	public void Decompressed() {
		
		ReadTagsFile r = new ReadTagsFile();
		ArrayList<Integer> tag = new ArrayList<Integer>();
		ArrayList<Integer> midpoint = new ArrayList<Integer>();
		ImageRW image = new ImageRW();
		int[][] pixels= new int[image.height][image.width];
		r.openFile("image.txt");
		
		tag = r.readFile();
		r.closeFile();
		int nLevel = tag.get(0);
		int range = 256/nLevel;
		int mid = 0;
        int low = 0, up = range - 1;
		
		 for (int i = 0; i < nLevel; i++) {
             
             mid = (low + up) / 2;
             midpoint.add(mid);
           
             low = up + 1;
             up += range;
         }
		 int it = 1;
		 for (int i = 0; i < image.height; i++) {
				for (int j = 0; j < image.width; j++) {
					
					pixels[i][j] = midpoint.get(tag.get(it));
					it++;
				}
		 }
		
		
		image.writeImage(pixels, "lena2.jpg");
		
	}

}
