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
	
	public void addRecord(ArrayList <Tag> tags) {
		for (int i = 0; i < tags.size(); i++) {
			create.format("%d %d %c ",tags.get(i).pointer, tags.get(i).length, tags.get(i).nextChar);
		}
		
	}
	
	public void closeFile() {
		create.close();
	}
}
