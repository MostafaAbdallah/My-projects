import java.util.ArrayList;
import java.util.Collections;

import javax.swing.text.TabableView;

import com.sun.org.apache.regexp.internal.recompile;


public class Huffman {

	
public  ArrayList<Info> coding(ArrayList<Info> chars) {
		
		ArrayList<Info> chars2 = new ArrayList();
		ArrayList<Info> chars3 = new ArrayList();
		boolean zero = false;
		
		if(chars.size() == 2){
			chars2.add(new Info(chars.get(0).theChar, chars.get(0).probability,"0"));
			chars2.add(new Info(chars.get(1).theChar, chars.get(1).probability,"1"));
			
			return chars2;
			
		}
		
		
		for (int i = 0; i < chars.size()-2; i++) {
			chars2.add(chars.get(i));
			
		}
		chars2.add(new Info(chars.get(chars.size()-1).theChar + chars.get(chars.size()-2).theChar,
							chars.get(chars.size()-1).probability + chars.get(chars.size()-2).probability,
																									""));
		
		Collections.sort(chars2);

		 chars3 = coding(chars2);
		 
		 /*System.out.println("Herrrrrrrrre"+ chars.size() );
		 	for (int j = 0; j < chars.size(); j++) {
		 		System.out.println(chars.get(j).probability);
			}*/
		 
		 for (int i = 0; i < chars.size(); i++) {
			for (int j = 0; j < chars3.size(); j++) {
				if(chars3.get(j).theChar.contains(chars.get(i).theChar) && chars3.get(j).theChar.length() > 1 ){
					if(zero == false){
						chars.get(i).code = chars3.get(j).code + "0";
						zero = true;
					}
					else
						chars.get(i).code += chars3.get(j).code + "1";
				}
				else if (chars3.get(j).theChar.contains(chars.get(i).theChar) && chars3.get(j).theChar.length() == 1){
					chars.get(i).code = chars3.get(j).code ;
				}
			}
		}
		 System.out.println("Herrrrrrrrre"+ chars.size() );
		 	for (int j = 0; j < chars.size(); j++) {
		 		System.out.println(chars.get(j).theChar + "-----" + chars.get(j).code);
			}
		 
		 
		return chars;
	}

public ArrayList<Info> GetChar(String Text) {
	
	ArrayList<Info> chars = new ArrayList<Info>();
	boolean found = false;

	for (int i = 0; i < Text.length(); i++) {
		found = false;
		for (int j = 0; j < chars.size(); j++) {
			if(Text.charAt(i) == chars.get(j).theChar.charAt(0)){
				chars.get(j).probability++;
				found = true;
				break;
			}
		}
		if(found == false){
			chars.add(new Info(Text.charAt(i), 1, ""));
		}
	}
	
	for (int i = 0; i < chars.size(); i++) {
		chars.get(i).probability = chars.get(i).probability / Text.length();
	}
	
	return chars;
}

public String compress(ArrayList<Info> chars, String Text) {
	
	String coding ="";
	
	for (int i = 0; i < Text.length(); i++) {
		for (int j = 0; j < chars.size(); j++) {
			if(Text.charAt(i) == chars.get(j).theChar.charAt(0)){
				coding += chars.get(j).code;
			}
		}
	}
	
	return coding;
	
}

public int binryToint(String coding) {
	int c = 0;
	c = Integer.parseInt(coding,2);
	return c;
}

public String decompress(ArrayList<Info> chars, int c) {
	
	String Text ="";
	String coding = Integer.toBinaryString(c);
	String subcode ="";
	
	System.out.print(coding);
	
	for (int i = 0; i < coding.length(); i++) {
		subcode += coding.charAt(i);
		for (int j = 0; j < chars.size(); j++) {
			if(chars.get(j).code.equals(subcode)){
				Text += chars.get(j).theChar;
				subcode = "";
				break;
			}
		}
	}
	
	return Text;
}

}
