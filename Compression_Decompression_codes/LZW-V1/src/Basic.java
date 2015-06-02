import java.util.ArrayList;
import java.util.Scanner;


public class Basic {
	
	
	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		ReadTextFile readText = new ReadTextFile();
		ArrayList <Integer> tags = new ArrayList <Integer> ();
		LZW lzw = new LZW();
		String fileName = "";
		String Text = "";
		
		System.out.print("Please Enter file name: ");
		fileName = input.next();
		
		readText.openFile(fileName);
		Text = readText.readFile();
		readText.closeFile();
		
		
		tags = lzw.compression(Text);
		
		for (int i = 0; i < tags.size(); i++) {
			System.out.printf("< %d > \n", tags.get(i));
		}
		
		WriteTagsFile w = new WriteTagsFile();
		w.createFile(fileName);
		w.addRecord(tags);
		w.closeFile();
		
		ReadTagsFile rt = new ReadTagsFile();
		rt.openFile(fileName);
		tags = rt.readFile();
		rt.closeFile();
		
		String str = lzw.decompression(tags);
		
		System.out.println(str);
		
		WriteTextFile wt = new WriteTextFile();
		wt.createFile(fileName);
		wt.addRecord(str);
		wt.closeFile();
		
	}
}
