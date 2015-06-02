import java.io.File;
import java.util.*;
import java.lang.*;
import java.io.*;

public class WriteTextFile {
	
	private Formatter create;
	
	public void createFile(String fileName){
		try {
			create = new Formatter(fileName);
		} catch (Exception e) {
			System.out.println("Error");
		}
	}
	
	public void addRecord(String text) {
		for (int i = 0; i < text.length(); i++) {
			create.format("%c",text.charAt(i));
		}
		
		
		
	}
	
	public void closeFile() {
		create.close();
	}
}
