import java.io.File;
import java.util.*;
import java.lang.*;
import java.io.*;

public class writeTag {
	
	private Formatter create;
	
	public void createFile(String fileName){
		try {
			create = new Formatter(fileName);
		} catch (Exception e) {
			System.out.println("Error");
		}
	}
	
	public void addRecord(ArrayList <Integer> tags, int level) {
		
		//int num = 0;
		create.format("%d ",level);
		//create.format("%d ",4);
		for (int i = 0; i < tags.size(); i++) {
			
			//num = Integer.parseInt(tags.get(i),2);
			//System.out.println(num);
			create.format("%d ",tags.get(i));
		}
		
		
	}
	
	public void closeFile() {
		create.close();
	}
}
