	

	
public class test01 {	
	
	
	
	
	public static void main(String[] args) {
	

		//init testOutput object
		testOutput tObject = new testOutput();
		
		//init urlString and testNumber
		String urlString;
		int testNumber = 0;
		
		//good protocols
		String[] gProto = {
			"http://",
			"ftp://"
		};
		
		//bad protocols
		String[] bProto = {
			"http:///",
			"badProtocol",
			"pikachu://"
		};
		
		//good domains
		String[] gDomain = {
			"google",
			"foo.bar",
			"amazon"
		};
		
		//good suffixes
		String[] gSuffix = {
			".com",
			".com/maps",
			".com/maps/:1300",
			".com/maps/:1300/options",
			".gov/"
		};
		
		//good queries
		String[] gQuery = {
			//"?id=1234", //known bug
			""
		};
		
		//bad queries
		String[] bQuery = {
			"?abc()",
			"?badQuer////yString"
		};
		
		
		System.out.println("------------");
		
		//Default Constructor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//init default uvObject
		UrlValidator uvObj01 = new UrlValidator();
		
		
		//Should all be true
		for(int i=0; i<gProto.length; i++){
			for(int j=0; j<gDomain.length; j++){
				for(int r=0; r<gSuffix.length; r++){
					for(int q=0; q<gQuery.length; q++){
		
			testNumber += 1;
			urlString = gProto[i] + gDomain[j] + gSuffix[r] + gQuery[q];
			tObject.testIsValid(uvObj01, urlString, true, testNumber);
		
		}}}}
		
		//Should all be false (bad Proto)
		for(int i=0; i<bProto.length; i++){
			for(int j=0; j<gDomain.length; j++){
				for(int r=0; r<gSuffix.length; r++){
					for(int q=0; q<gQuery.length; q++){
		
			testNumber += 1;
			urlString = bProto[i] + gDomain[j] + gSuffix[r] + gQuery[q];
			tObject.testIsValid(uvObj01, urlString, false, testNumber);
		
		}}}}
		
		//Should all be false (bad Domain)
		for(int i=0; i<bProto.length; i++){
			for(int j=0; j<gDomain.length; j++){
				for(int r=0; r<gSuffix.length; r++){
					for(int q=0; q<gQuery.length; q++){
		
			testNumber += 1;
			urlString = bProto[i] + gDomain[j] + gSuffix[r] + gQuery[q];
			tObject.testIsValid(uvObj01, urlString, false, testNumber);
		
		}}}}
		
		//Should all be false (bad Suffix)
		for(int i=0; i<bProto.length; i++){
			for(int j=0; j<gDomain.length; j++){
				for(int r=0; r<gSuffix.length; r++){
					for(int q=0; q<gQuery.length; q++){
		
			testNumber += 1;
			urlString = bProto[i] + gDomain[j] + gSuffix[r] + gQuery[q];
			tObject.testIsValid(uvObj01, urlString, false, testNumber);
		
		}}}}
		
		//Should all be false (bad Query)
		for(int i=0; i<gProto.length; i++){
			for(int j=0; j<gDomain.length; j++){
				for(int r=0; r<gSuffix.length; r++){
					for(int q=0; q<bQuery.length; q++){
		
			testNumber += 1;
			urlString = gProto[i] + gDomain[j] + gSuffix[r] + bQuery[q];
			tObject.testIsValid(uvObj01, urlString, false, testNumber);
		
		}}}}
		
		
		testNumber += 1;
		urlString = "http://www.google.com";
		tObject.testIsValid(uvObj01, urlString, true, testNumber);
		
		testNumber += 1;
		urlString = "https://stuff.amazon.com/main";
		tObject.testIsValid(uvObj01, urlString, true, testNumber);
		
		testNumber += 1;
		urlString = "ftp://oregonstate.edu/";
		tObject.testIsValid(uvObj01, urlString, true, testNumber);
		
		testNumber += 1;
		urlString = "http://myWebSite.net/login?id=1234";
		tObject.testIsValid(uvObj01, urlString, true, testNumber);
		
		testNumber += 1;
		urlString = "http://myWebSite.net?id=1234";
		tObject.testIsValid(uvObj01, urlString, true, testNumber);
		
		testNumber += 1;
		urlString = "http://nike.com/shoes:1300";
		tObject.testIsValid(uvObj01, urlString, true, testNumber);
		
		testNumber += 1;
		urlString = "http:///www.google.com";
		tObject.testIsValid(uvObj01, urlString, false, testNumber);
		
		testNumber += 1;
		urlString = "httpz://amazon.net";
		tObject.testIsValid(uvObj01, urlString, false, testNumber);
		
		testNumber += 1;
		urlString = "ftp://oregonstate.skoolz";
		tObject.testIsValid(uvObj01, urlString, false, testNumber);
		
		testNumber += 1;
		urlString = "http://mySite.net/login?theQuery////isBad()";
		tObject.testIsValid(uvObj01, urlString, false, testNumber);
	
		
		System.out.println("Testing finished.");
		
	
	}
	
	
}

