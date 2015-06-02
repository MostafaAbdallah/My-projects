


public class Info implements Comparable<Info> {
	public String theChar = "";
	public float probability = 0.0f;
	public String code ="";
	
	public Info(String t, float p, String c) {
		theChar = t;
		probability = p;
		code = c;
	}
	public Info(char t, float p, String c) {
		theChar += t;
		probability = p;
		code = c;
	}
	
	 
	    public int compareTo(Info comparestu) {
		 	float compareage=comparestu.probability * 10;
	        // For Ascending order
	        //return this.probability-compareage;

	        // For Descending order do like this 
	        return (int) ((int)compareage-this.probability * 10);
	    }
	    
	   
}
 