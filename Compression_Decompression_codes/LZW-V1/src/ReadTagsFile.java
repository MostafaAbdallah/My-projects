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
	
	public ArrayList<Integer> readFile() {
		
		ArrayList<Integer> tags = new ArrayList<Integer>();
		int pointer = 0;
		
		while (input.hasNext()) {
			pointer = input.nextInt();
			
			tags.add(pointer);
			
		}
		return tags;
	}
	
	public void closeFile() {
		input.close();
	}
}
