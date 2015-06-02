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
	
	public ArrayList<Integer>  readFile() {
		 ArrayList<Integer> tag = new ArrayList<Integer>();
		
			int c = 0;
		 while (input.hasNext()) {
				c = input.nextInt();
				tag.add(c);
				
			}
		 
		return tag;
	}
	
	public void closeFile() {
		input.close();
	}
}
