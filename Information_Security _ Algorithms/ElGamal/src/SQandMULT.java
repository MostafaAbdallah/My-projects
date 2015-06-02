import java.math.BigInteger;


public class SQandMULT {
	
	BigInteger squaerAndMultiply(BigInteger base , BigInteger power, BigInteger n){
		String binaryPower =power.toString(2) ;
		//System.out.println("binary: "+binaryPower);
		BigInteger result = null;
		for(int i=0 ; i<binaryPower.length() ; i++){
			//initial
			if(i == 0){
				result = base;
			}else{
				//squares the equation(result) and then multiplies by the base
				if(binaryPower.charAt(i) == '1'){
					result=( result.multiply(result).multiply(base) ).mod(n);
				//squares the equation(result)
				}else if(binaryPower.charAt(i) == '0'){
					result=( result.multiply(result)).mod(n);
				}
			}
		}
		return result;
		
	}
	
	
}
