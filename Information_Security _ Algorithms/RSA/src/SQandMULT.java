
public class SQandMULT {
	
	long squaerAndMultiply(long base , long power, long n){
		
		String binaryPower = Long.toBinaryString(power);
		//System.out.println("binary: "+binaryPower);
		long result = 0L;
		for(int i=0 ; i<binaryPower.length() ; i++){
			//initial
			if(i == 0){
				result = base;
			}else{
				//squares the equation(result) and then multiplies by the base
				if(binaryPower.charAt(i) == '1'){
					result = (result*result*base) % n;
				//squares the equation(result)
				}else if(binaryPower.charAt(i) == '0'){
					result = (result*result) % n;
				}
			}
		}
		return result;
	}
	
	
}
