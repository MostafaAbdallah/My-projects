import java.io.File;
import java.util.*;
import java.lang.*;
import java.io.*;

public class WriteTagsFile {
	
	private Formatter create;
	
	public void createFile(String fileName){
		try {
			create = new Formatter(fileName);
		} catch (Exception e) {
			System.out.println("Error");
		}
	}
	
	public void addRecord(ArrayList <Integer> tags) {
		for (int i = 0; i < tags.size(); i++) {
			create.format("%d ",tags.get(i));
		}
		
	}
	
	public void closeFile() {
		create.close();
	}
}
