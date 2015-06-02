import java.io.*;
import java.util.*;

public class ReadTextFile {
	
	private Scanner input;
	
	public void openFile(String fileName) {
		try {
			input = new Scanner(new File(fileName));
		} catch (Exception e) {
			System.out.println("Error to open the File");
		}
	}
	
	public String readFile() {
		String text = "";
		while (input.hasNext()) {
			text += input.nextLine();
			
		}
		return text;
	}
	
	public void closeFile() {
		input.close();
	}
}
