
public class main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		MixColumn m = new MixColumn();
		ShiftRow r = new ShiftRow();
		String str[][] = new String [][]{
				
				{"e3",  "32",  "f4",  "b0"},
				{"49",  "b0",  "9f",  "58"},
				{"05",  "7c",  "01",  "f2"},
				{"60",  "33",  "bd",  "a9"},
				
		};
		
		String str1[][] = new String [][]{
				
				{"63",  "e0",  "f5",  "c8"},
				{"1e",  "fe",  "6f",  "a4"},
				{"00",  "2f",  "b5",  "f7"},
				{"b2",  "fc",  "f8",  "28"},
				
		};
		
		
		  
		
		
		str = m.mixColumn(str, true);
		//String E = "1000010";
		//String B = "00101111";
		//String str1 = m.Multiplication(E, B);
		//str = r.shiftRowEncryption(str);
		//str = r.shiftRowDecryption(str);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j <4; j++) {
				System.out.print(str[i][j] + " ");
			}
			System.out.println();
		}
		
	}

}
