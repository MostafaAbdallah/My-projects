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
	
	public ArrayList<Tag> readFile() {
		
		ArrayList<Tag> tags = new ArrayList<Tag>();
		int pointer = 0;
		int length = 0;
		String nextChar = "";
		
		while (input.hasNext()) {
			pointer = input.nextInt();
			length = input.nextInt();
			if(input.hasNext()){
				nextChar = input.next();
				tags.add(new Tag(pointer, length, nextChar.charAt(0)));
			}
			else
				tags.add(new Tag(pointer, length, ' '));
			
		}
		return tags;
	}
	
	public void closeFile() {
		input.close();
	}
}
