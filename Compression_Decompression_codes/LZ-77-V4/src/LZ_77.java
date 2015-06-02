import java.util.ArrayList;

import com.sun.org.apache.xml.internal.resolver.helpers.PublicId;


public class LZ_77 {
	
	public ArrayList <Tag> compression(String text){
		
		ArrayList <Tag> tags = new ArrayList <Tag> ();
		
		String myChar = "";
		int currPointer = 0;
		int pointer = -1;
		int length = 0;
		int p = 0;
		
		for (int i = 0; i < text.length(); i++){
			myChar += text.charAt(i);
			
			p =searchInString(text, myChar, currPointer);
			
			if(p == -1){
				if(pointer != -1){
					length = myChar.length()-1;
					pointer = currPointer-pointer;
				}
				tags.add(new Tag(pointer, length,text.charAt(i)));
				
				myChar = "";
				currPointer = i+1;
				pointer = -1;
				length = 0;
			}
			else if(p != -1 && i+1 < text.length()){
				pointer = p;
			}
			else{
				tags.add(new Tag(currPointer-p, myChar.length(),' '));
			}
		}
		
		return tags;
	}
	
	private int searchInString(String text,String str, int currpointer){
		
		int rpointer = -1;
		
		String cStr ="";
		
		for (int it = 0; it < currpointer; it++) {
			
			cStr += text.charAt(it);	
		}
		
		rpointer = cStr.indexOf( str );
		
		return rpointer;
	}

	public String decompression(ArrayList <Tag> tags) {
		String Text = "";
		
		for (int i = 0; i < tags.size(); i++) {
			
			if(tags.get(i).pointer == -1){
				Text += tags.get(i).nextChar;
			}
			else{
				Text = tagToString(Text, tags.get(i));
			}
		}
		
		return Text;
	}
	
	private String tagToString(String text, Tag tag){
		
		int pointer =text.length()- tag.pointer;
		for (int i = pointer; i < pointer + tag.length; i++) {
			text += text.charAt(i);
		}
		
		text += tag.nextChar;
		return text;
	}
}
