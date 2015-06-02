import java.util.ArrayList;
import java.util.Scanner;


public class Basic {
	
/*	public static int checkstring(String text,String str, int currpointer) {
		
		int rpointer = -1;
		//int rlength = str.length();
		String cStr ="";
		
		for (int it = 0; it < currpointer; it++) {
			
			cStr += text.charAt(it);	
		}
		
		rpointer = cStr.indexOf( str );
		
		return rpointer;
	}*/
	
	
	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		ReadTextFile readText = new ReadTextFile();
		ArrayList <Tag> tags = new ArrayList <Tag> ();
		LZ_77 lz = new LZ_77();
		
		String fileName = "";
		String Text = "";
		
		System.out.print("Please Enter file name: ");
		fileName = input.next();
		
		readText.openFile(fileName);
		Text = readText.readFile();
		readText.closeFile();
		
		tags = lz.compression(Text);
		
		for (int i = 0; i < tags.size(); i++) {
			System.out.printf("< %d %d %c > \n", tags.get(i).pointer, tags.get(i).length, tags.get(i).nextChar);
		}
		
		WriteTagsFile w = new WriteTagsFile();
		w.createFile(fileName);
		w.addRecord(tags);
		w.closeFile();
		ReadTagsFile rt = new ReadTagsFile();
		rt.openFile(fileName);
		tags = rt.readFile();
		rt.closeFile();
		
		String str = lz.decompression(tags);
		
		System.out.println(str);
		
		WriteTextFile wt = new WriteTextFile();
		wt.createFile(fileName);
		wt.addRecord(str);
		wt.closeFile();
		
	}
}
