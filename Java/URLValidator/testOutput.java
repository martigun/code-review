

public class testOutput{

		protected double theValue;
		
		public testOutput(){
			
			theValue = 17;
			
			
		}
		
		
		public boolean testIsValid(UrlValidator UrlObject, String urlString, boolean expected, int tNbr){
			
			
			//get value of test returned
			boolean testReturned = UrlObject.isValid(urlString);
			//boolean returnValue;
			
			// System.out.println("testReturned: " + testReturned);
			// System.out.println("expected: " + expected);			
			// System.out.println("returnValue: " + returnValue);
			
			if(testReturned == expected){
				
				//returnValue = true;
				return true;
			} else {
				
				System.out.println("Test #" + tNbr + " failed:");
				System.out.println(urlString);
				System.out.println("Expected: " + expected);
				System.out.println("Received: " + testReturned);
				System.out.println("------------");
				//returnValue = false;
				return false;
			}
				
			//return returnValue;
			
		}
		

		



}