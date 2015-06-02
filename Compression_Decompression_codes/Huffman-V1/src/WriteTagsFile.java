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
	
	public void addRecord(ArrayList <Info> tags, int c) {
		int num=0;
		create.format("%d ",tags.size());
		for (int i = 0; i < tags.size(); i++) {
			
			num = Integer.parseInt(tags.get(i).code,2);
			create.format("%s %d ",tags.get(i).theChar,num);
		}
		create.format("%d ",c);
		
	}
	
	public void closeFile() {
		create.close();
	}
}
