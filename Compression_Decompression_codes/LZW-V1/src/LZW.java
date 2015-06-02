import java.util.ArrayList;


public class LZW {
	
	private int searchInVector(ArrayList<String> Dictionary,String str){
			
			int rpointer = -1;
			
			
			for (int it = 0; it < Dictionary.size(); it++) {
				
				if(str.equals(Dictionary.get(it))){
					
					rpointer = it;
					break;
				}
			}
			
			return rpointer;
		}

	public ArrayList <Integer> compression(String text){
	
		ArrayList <Integer> tags = new ArrayList <Integer> ();
		ArrayList <String> Dictionary = new ArrayList <String> ();
	
		String myChar = "";
		int pointer = -1;
		int p = 0;
		
		//System.out.printf("& %s & \n",text);
		for (int i = 0; i < text.length(); i++){
			myChar += text.charAt(i);
			//System.out.printf("* %s * \n", myChar);
			p =searchInVector(Dictionary, myChar);
		
			if(p == -1){
				if(myChar.length() == 1){
					pointer = myChar.charAt(0);
				}
				else{
					System.out.printf("* %s * \n", myChar);
					Dictionary.add(myChar);
					if(myChar.length() > 2)
						pointer +=128;
					tags.add(pointer);
					i--;
					myChar = "";
				}
			}
			else if(i+1 < text.length()){
				pointer = p;
			}
			else{
				Dictionary.add(myChar);
				p +=128;
				tags.add(p);
			}
		
		}
		
		/*for (int i = 0; i < Dictionary.size(); i++) {
			System.out.printf("< %s > \n", Dictionary.get(i));
		}*/
	
		return tags;
		}
	
	private String searchInVector(int index, ArrayList<String> Dictionary) {
		String str ="";
		if(index < Dictionary.size()-1){
			str = Dictionary.get(index);
		}
		return str;
	}
	
	public String decompression(ArrayList <Integer> tags){
		String Text = "";
		String str = "";
		String AddToDictoinary = "";
		String previousTag = "";
		char c;
		int x;
		int index = 0;
		ArrayList <String> Dictionary = new ArrayList <String> ();

		
		for(int i = 0; i < tags.size(); i++){
			 AddToDictoinary = "";
			if(tags.get(i) < 128){
				x = tags.get(i);
				c = (char)x;
				Text += c;
				//System.out.printf("< %s > \n", Text);
				AddToDictoinary += previousTag + c;
				previousTag = "";
				previousTag += c;
				if(AddToDictoinary.length() > 1)
					Dictionary.add(AddToDictoinary);
				
			}
			else{
				index = tags.get(i)-128;
				str = searchInVector(index, Dictionary);
				if(str.length() > 0){
					Text += str;
					AddToDictoinary += previousTag + str.charAt(0);
					Dictionary.add(previousTag + str.charAt(0));
					previousTag = "";
					previousTag += str;
					
				}
				else{
					Text += previousTag + previousTag.charAt(0);
					Dictionary.add(previousTag + previousTag.charAt(0));
					previousTag = previousTag + previousTag.charAt(0);
				}
			}
		}
		for (int i = 0; i < Dictionary.size(); i++) {
		System.out.printf("< %s > \n", Dictionary.get(i));
	}
		return Text;
	}
}
