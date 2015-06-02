import java.util.ArrayList;
import java.util.Collections;


public class ShiftRow {
	
	public String [][]shiftRowEncryption(String [][] P){
		String [][] shifted = new String [4][4];
		ArrayList<String> row = new ArrayList<String>();
		 for (int i = 0; i < 4; i++) {
			 
			 row.clear();
			
			 for (int j = 0; j < 4; j++) {
				row.add(P[i][j]);
			}
			if( i != 0)
				Collections.rotate(row, 4 - i);
			
			for (int j = 0; j < shifted.length; j++) {
				shifted[i][j] = row.get(j);
			}
		}
		
		return shifted;
	}
	
	public String [][]shiftRowDecryption(String [][] P){
		String [][] shifted = new String [4][4];
		ArrayList<String> row = new ArrayList<String>();
		 for (int i = 0; i < 4; i++) {
			 
			 row.clear();
			
			 for (int j = 0; j < 4; j++) {
				row.add(P[i][j]);
			}
			if( i != 0)
				Collections.rotate(row, 4 + i);
			
			for (int j = 0; j < shifted.length; j++) {
				shifted[i][j] = row.get(j);
			}
		}
		
		return shifted;
	}
	
}
