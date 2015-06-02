import java.io.*;
import java.util.*;

public class ReadTagsFile {
	
	private Scanner input;
	
	public void openFile(String fileName) {
		try {
			input = new Scanner(new File(fileName));
		} catch (Exception e) {
			System.out.println("Error to open the File");
		}
	}
	
	public String readFile() {
		
		ArrayList<Info> tags = new ArrayList<Info>();
		Huffman huff = new Huffman();
		int c = 0;
		String Text ="";
		int size = input.nextInt();
		int num;
		String str;
		for (int i = 0; i < size; i++) {
			str = input.next();
			num = input.nextInt();
			tags.add(new Info(str, 0, Integer.toBinaryString(num)));
		}
		
			c = input.nextInt();
			
			Text = huff.decompress(tags, c);
			
		return Text;
	}
	
	public void closeFile() {
		input.close();
	}
}
