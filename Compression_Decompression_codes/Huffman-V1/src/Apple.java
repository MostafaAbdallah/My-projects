import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;


public class Apple {

	
	public static void main(String[] args) {
		
		ArrayList<Info> chars = new ArrayList();
		ArrayList<Info> chars2 = new ArrayList();
		
		String fileName = "";
		String Text = "";
		
		Scanner input = new Scanner(System.in);
		ReadTextFile readText = new ReadTextFile();
		Huffman huff = new Huffman();
		
		System.out.print("Please Enter file name: ");
		fileName = input.next();
		
		readText.openFile(fileName);
		Text = readText.readFile();
		readText.closeFile();
		
		chars = huff.GetChar(Text);
		
		for (int j = 0; j < chars.size(); j++) {
			System.out.println(chars.get(j).theChar + "-----" + chars.get(j).probability);
		}
		
		chars2 = huff.coding(chars);
		String coding = huff.compress(chars2, Text);
		int c = huff.binryToint(coding);
		
		System.out.print(coding);
		
		
		WriteTagsFile wt = new WriteTagsFile();
		wt.createFile("cmyfile.txt");
		wt.addRecord(chars2, c);
		wt.closeFile();
		
			for (int j = 0; j < chars2.size(); j++) {
				System.out.println(chars2.get(j).theChar + "-----" + chars2.get(j).code);
		}
		String t;
		ReadTagsFile rt = new ReadTagsFile();
		rt.openFile("cmyfile.txt");
		t = rt.readFile();
		rt.closeFile();
		System.out.print(t);

	}
	
	
}
