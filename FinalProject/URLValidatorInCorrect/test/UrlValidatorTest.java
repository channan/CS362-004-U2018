

import junit.framework.Assert;
import junit.framework.TestCase;
import org.junit.Test;

import java.util.*;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   @Test
   public void testManualTest()
   {
//You can use this function to implement your manual testing
	   UrlValidator url = new UrlValidator();
	   UrlValidator urlAllowAll = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);

       ArrayList<String> urls = new ArrayList<>(Arrays.asList(
               "http://www.googl.com",
               "www.google.com",
               "google.com",
               "https://www.google.com",
               "ftp://www.google.com",
               "www.google.com/",
               "https://oregonstate.edu/",
               "http://oregonstate.edu/about",
               "http://oregonstate.edu/about?",
               "oregonstate.edu/",
               "oregonstate.edu/about",
               "oregonstate.edu/about?",
               "as;dfja;lskdjf;aldjf;lksjf;laksj;lfja;ls",
               "http://209.191.122.70/",
               "http://www.amazon.com/?action=delete",
               "http://1.2.3.400/", //No digit in an ip address should be above 255
               "1.1.1.1", //Lower bounds should be a valid IP address
               "1.1.1.255", //Should be a valid IP address
               "3.3.3.100", //Should be a valid IP address
               "3.3.3.255", //Should be a valid IP address
               "3.3.3.256" //Invalid IP address
       ));

       ArrayList<String> fails = new ArrayList<>();
       ArrayList<String> passes = new ArrayList<>();

       System.out.println("Testing using default url validator...");
       for(String entry : urls){
           try{
               assertTrue(url.isValid(entry));
               passes.add(entry);
           }catch(Error e){
               fails.add(entry);
           }
       }

       System.out.println("Passing urls:");
       for(String entry : passes){
           System.out.println(entry);
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(String entry : fails){
           System.out.println(entry);
       }

       System.out.println(" ");

       passes.clear();
       fails.clear();

       System.out.println("Testing using url validator that allows all schemes...");
       for(String entry : urls){
           try{
               assertTrue(urlAllowAll.isValid(entry));
               passes.add(entry);
           }catch(Error e){
               fails.add(entry);
           }
       }

       System.out.println("Passing urls:");
       for(String entry : passes){
           System.out.println(entry);
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(String entry : fails){
           System.out.println(entry);
       }
   }

   //schemes
    @Test
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing
       UrlValidator url = new UrlValidator();
       UrlValidator urlAllowAll = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);

       ArrayList<String> urls = new ArrayList<>(Arrays.asList(
               "http://www.google.com",
               "ftp://www.google.com",
               "h3t://www.google.com",
               "3ht://www.google.com",
               "http:/www.google.com",
               "http:www.google.com",
               "http/www.google.com",
               "://www.google.com",
               "www.google.com",
               "http://foo.com/blah_blah", //valid scheme
               "foo.com" //no scheme
       ));

       ArrayList<String> fails = new ArrayList<>();
       ArrayList<String> passes = new ArrayList<>();

       System.out.println("Testing schemes using default url validator...");
       for(String entry : urls){
           try{
               assertTrue(url.isValid(entry));
               passes.add(entry);
           }catch(Error e){
               fails.add(entry);
           }
       }

       System.out.println("Passing urls:");
       for(String entry : passes){
           System.out.println(entry);
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(String entry : fails){
           System.out.println(entry);
       }

       System.out.println(" ");

       passes.clear();
       fails.clear();

       System.out.println("Testing schemes using url validator that allows all schemes...");
       for(String entry : urls){
           try{
               assertTrue(urlAllowAll.isValid(entry));
               passes.add(entry);
           }catch(Error e){
               fails.add(entry);
           }
       }

       System.out.println("Passing urls:");
       for(String entry : passes){
           System.out.println(entry);
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(String entry : fails){
           System.out.println(entry);
       }

   }

   //authority
    @Test
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing
       UrlValidator url = new UrlValidator();
       UrlValidator urlAllowAll = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);

       ArrayList<String> urls = new ArrayList<>(Arrays.asList(
               "http://www.google.com",
               "http://go.com",
               "http://go.au",
               "http://0.0.0.0",
               "http://255.255.255.255",
               "http://256.256.256.256",
               "http://255.com",
               "http://1.2.3.4.5",
               "http://1.2.3.4.",
               "http://1.2.3",
               "http://.1.2.3.4",
               "http://go.a",
               "http://go.a1a",
               "http://go.cc",
               "http://go.1aa",
               "http://aaa.",
               "http://.aaa",
               "http://aaa",
               "http://",
               "http://fo o.bar", //invalid authority
               "http://foo.bar" //valid authority
       ));

       ArrayList<String> fails = new ArrayList<>();
       ArrayList<String> passes = new ArrayList<>();

       System.out.println("Testing authorities using default url validator...");
       for(String entry : urls){
           try{
               assertTrue(url.isValid(entry));
               passes.add(entry);
           }catch(Error e){
               fails.add(entry);
           }
       }

       System.out.println("Passing urls:");
       for(String entry : passes){
           System.out.println(entry);
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(String entry : fails){
           System.out.println(entry);
       }

       System.out.println(" ");

       passes.clear();
       fails.clear();

       System.out.println("Testing authorities using url validator that allows all schemes...");
       for(String entry : urls){
           try{
               assertTrue(urlAllowAll.isValid(entry));
               passes.add(entry);
           }catch(Error e){
               fails.add(entry);
           }
       }

       System.out.println("Passing urls:");
       for(String entry : passes){
           System.out.println(entry);
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(String entry : fails){
           System.out.println(entry);
       }
   }
   //You need to create more test cases for your Partitions if you need to

    //port
    @Test
    public void testYourThirdPartition(){
        //You can use this function to implement your Second Partition testing
        UrlValidator url = new UrlValidator();
        UrlValidator urlAllowAll = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);

        ArrayList<String> urls = new ArrayList<>(Arrays.asList(
                "http://www.google.com:65535",
                "http://www.google.com:0",
                "http://www.google.com",
                "http://www.google.com:-1",
                "http://www.google.com:65636",
                "http://www.google.com:65a",
                "http://www.google.com:80"
        ));

        ArrayList<String> fails = new ArrayList<>();
        ArrayList<String> passes = new ArrayList<>();

        System.out.println("Testing ports using default url validator...");
        for(String entry : urls){
            try{
                assertTrue(url.isValid(entry));
                passes.add(entry);
            }catch(Error e){
                fails.add(entry);
            }
        }

        System.out.println("Passing urls:");
        for(String entry : passes){
            System.out.println(entry);
        }

        System.out.println("");
        System.out.println("Failing urls:");
        for(String entry : fails){
            System.out.println(entry);
        }

        System.out.println(" ");

        passes.clear();
        fails.clear();

        System.out.println("Testing ports using url validator that allows all schemes...");
        for(String entry : urls){
            try{
                assertTrue(urlAllowAll.isValid(entry));
                passes.add(entry);
            }catch(Error e){
                fails.add(entry);
            }
        }

        System.out.println("Passing urls:");
        for(String entry : passes){
            System.out.println(entry);
        }

        System.out.println("");
        System.out.println("Failing urls:");
        for(String entry : fails){
            System.out.println(entry);
        }
    }

    //path
    @Test
    public void testYourFourthPartition(){
        //You can use this function to implement your Second Partition testing
        UrlValidator url = new UrlValidator();
        UrlValidator urlAllowAll = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);

        ArrayList<String> urls = new ArrayList<>(Arrays.asList(
                "http://www.google.com/test1",
                "http://www.google.com/t123",
                "http://www.google.com/$23",
                "http://www.google.com/..",
                "http://www.google.com/../",
                "http://www.google.com/test1/",
                "http://www.google.com",
                "http://www.google.com/test1/file",
                "http://www.google.com/..//file",
                "http://www.google.com/test1//file"
        ));

        ArrayList<String> fails = new ArrayList<>();
        ArrayList<String> passes = new ArrayList<>();

        System.out.println("Testing paths using default url validator...");
        for(String entry : urls){
            try{
                assertTrue(url.isValid(entry));
                passes.add(entry);
            }catch(Error e){
                fails.add(entry);
            }
        }

        System.out.println("Passing urls:");
        for(String entry : passes){
            System.out.println(entry);
        }

        System.out.println("");
        System.out.println("Failing urls:");
        for(String entry : fails){
            System.out.println(entry);
        }

        System.out.println(" ");

        passes.clear();
        fails.clear();

        System.out.println("Testing paths using url validator that allows all schemes...");
        for(String entry : urls){
            try{
                assertTrue(urlAllowAll.isValid(entry));
                passes.add(entry);
            }catch(Error e){
                fails.add(entry);
            }
        }

        System.out.println("Passing urls:");
        for(String entry : passes){
            System.out.println(entry);
        }

        System.out.println("");
        System.out.println("Failing urls:");
        for(String entry : fails){
            System.out.println(entry);
        }
    }

    //query
    @Test
    public void testYourFifthPartition(){
        //You can use this function to implement your Second Partition testing
        UrlValidator url = new UrlValidator();
        UrlValidator urlAllowAll = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);

        ArrayList<String> urls = new ArrayList<>(Arrays.asList(
                "http://www.google.com/test1?action=view",
                "http://www.google.com/test1?action=edit&mode=up",
                "http://www.google.com/test1",
                "http://example.com/foo/foo/foo?bar/bar/bar", //with query
                "http://example.com/foo/foo/foo?ba r/bar/bar" //invalid query
        ));

        ArrayList<String> fails = new ArrayList<>();
        ArrayList<String> passes = new ArrayList<>();

        System.out.println("Testing queries using default url validator...");
        for(String entry : urls){
            try{
                assertTrue(url.isValid(entry));
                passes.add(entry);
            }catch(Error e){
                fails.add(entry);
            }
        }

        System.out.println("Passing urls:");
        for(String entry : passes){
            System.out.println(entry);
        }

        System.out.println("");
        System.out.println("Failing urls:");
        for(String entry : fails){
            System.out.println(entry);
        }

        System.out.println(" ");

        passes.clear();
        fails.clear();

        System.out.println("Testing queries using url validator that allows all schemes...");
        for(String entry : urls){
            try{
                assertTrue(urlAllowAll.isValid(entry));
                passes.add(entry);
            }catch(Error e){
                fails.add(entry);
            }
        }

        System.out.println("Passing urls:");
        for(String entry : passes){
            System.out.println(entry);
        }

        System.out.println("");
        System.out.println("Failing urls:");
        for(String entry : fails){
            System.out.println(entry);
        }
    }

    @Test
   public void testIsValidRandom()
   {
	   //You can use this function for programming based testing
       UrlValidator url = new UrlValidator();
       UrlValidator urlAllowAll = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);

       int numTests=10000;
       int i=0;
       LinkedHashMap<String, Boolean> urls = new LinkedHashMap<>();
       //ArrayList<String> urls = new ArrayList<>();
       Random rand = new Random();

       while(i<numTests){
           //System.out.println(i);
           int pos = rand.nextInt(testUrlScheme().size());
           String schemeString = (new ArrayList<>(testUrlScheme().keySet())).get(pos);
           Boolean schemeBool = (new ArrayList<>(testUrlScheme().values())).get(pos);

           pos = rand.nextInt(testUrlAuthority().size());
           String authorityString = (new ArrayList<>(testUrlAuthority().keySet())).get(pos);
           Boolean authorityBool = (new ArrayList<>(testUrlAuthority().values())).get(pos);

           pos = rand.nextInt(testUrlPort().size());
           String portString = (new ArrayList<>(testUrlPort().keySet())).get(pos);
           Boolean portBool = (new ArrayList<>(testUrlPort().values())).get(pos);

           pos = rand.nextInt(testUrlPath().size());
           String pathString = (new ArrayList<>(testUrlPath().keySet())).get(pos);
           Boolean pathBool = (new ArrayList<>(testUrlPath().values())).get(pos);

           pos = rand.nextInt(testUrlQuery().size());
           String queryString = (new ArrayList<>(testUrlQuery().keySet())).get(pos);
           Boolean queryBool = (new ArrayList<>(testUrlQuery().values())).get(pos);

           String urlString = schemeString + authorityString + portString + pathString + queryString;
           Boolean expected = schemeBool & authorityBool & portBool & pathBool & queryBool;

           urls.put(urlString,expected);
           //urls.put("http://www.google.com",true);
           i++;
       }

//       ArrayList<String> fails = new ArrayList<>();
//       ArrayList<String> passes = new ArrayList<>();

       LinkedHashMap<String, String> passes = new LinkedHashMap<>();
       LinkedHashMap<String, String> fails = new LinkedHashMap<>();

       System.out.println("Testing urls using default url validator...");
       for(Map.Entry<String, Boolean> entry : urls.entrySet()){
           try{
               assertEquals(entry.getValue().booleanValue(),url.isValid(entry.getKey()));
               passes.put(entry.getKey()," --> " + entry.getValue().toString());
           }catch(Error e){
               fails.put(entry.getKey()," --> " + entry.getValue().toString());
           }
       }

       System.out.println("Passing urls:");
       for(Map.Entry<String, String> entry : passes.entrySet()){
           System.out.println(entry.getKey()+entry.getValue());
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(Map.Entry<String, String> entry : fails.entrySet()){
           System.out.println(entry.getKey()+entry.getValue());
       }

       System.out.println(" ");

       passes.clear();
       fails.clear();

       System.out.println("Testing urls using url validator that allows all schemes...");
       for(Map.Entry<String, Boolean> entry : urls.entrySet()){
           try{
               assertEquals(entry.getValue().booleanValue(),urlAllowAll.isValid(entry.getKey()));
               passes.put(entry.getKey()," --> " + entry.getValue().toString());
           }catch(Error e){
               fails.put(entry.getKey()," --> " + entry.getValue().toString());
           }
       }

       System.out.println("Passing urls:");
       for(Map.Entry<String, String> entry : passes.entrySet()){
           System.out.println(entry.getKey()+entry.getValue());
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(Map.Entry<String, String> entry : fails.entrySet()){
           System.out.println(entry.getKey()+entry.getValue());
       }

   }

    public void testIsValid()
    {
        //You can use this function for programming based testing

        UrlValidator url1 = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
        UrlValidator url2 = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        UrlValidator url = new UrlValidator();

        String testurl;
        Boolean result;

        for(Map.Entry<String, Boolean> scheme : testUrlScheme().entrySet()){
            for(Map.Entry<String, Boolean> authority : testUrlAuthority().entrySet()){
                for(Map.Entry<String, Boolean> port : testUrlPort().entrySet()){
                    for(Map.Entry<String, Boolean> path : testUrlPath().entrySet()){
                        for(Map.Entry<String, Boolean> query : testUrlQuery().entrySet()){
                            testurl = scheme.getKey() + authority.getKey() + port.getKey() + path.getKey() + query.getKey();
                            result = scheme.getValue() & authority.getValue() & port.getValue() & path.getValue() & query.getValue();
                            assertEquals(testurl,result.booleanValue(),url.isValid(testurl));
                            assertEquals(testurl,result.booleanValue(),url1.isValid(testurl));
                            assertEquals(testurl,result.booleanValue(),url2.isValid(testurl));
                        }
                    }
                }
            }
        }
    }

   public LinkedHashMap<String,Boolean> testUrlScheme() {
       LinkedHashMap<String, Boolean> map = new LinkedHashMap<>();
       map.put("http://", true);
       map.put("ftp://", true);
       map.put("h3t://", true);
       map.put("3ht://", false);
       map.put("http:/", false);
       map.put("http:", false);
       map.put("http/", false);
       map.put("://", false);
       map.put("", true);

       return map;
   }

    public LinkedHashMap<String,Boolean> testUrlAuthority() {
        LinkedHashMap<String, Boolean> map = new LinkedHashMap<>();
        map.put("go.com", true);
        map.put("go.au", true);
        map.put("0.0.0.0", true);
        map.put("255.255.255.255", true);
        map.put("256.256.256.256", false);
        map.put("255.com", true);
        map.put("1.2.3.4.5", false);
        map.put("1.2.3.4.", false);
        map.put("1.2.3", false);
        map.put(".1.2.3.4", false);
        map.put("go.a", false);
        map.put("go.a1a", false);
        map.put("go.cc", true);
        map.put("go.1aa", false);
        map.put("aaa.", false);
        map.put(".aaa", false);
        map.put("aaa", false);
        map.put("", false);
        map.put("www.google.com", true);

        return map;
    }

    public LinkedHashMap<String,Boolean> testUrlPort() {
        LinkedHashMap<String, Boolean> map = new LinkedHashMap<>();
        map.put(":65535", true);
        map.put(":0", true);
        map.put("", true);
        map.put(":-1", false);
        map.put(":65636", true);
        map.put(":65a", false);
        map.put(":80", true);

        return map;
    }

    public LinkedHashMap<String,Boolean> testUrlPath() {
        LinkedHashMap<String, Boolean> map = new LinkedHashMap<>();
        map.put("/t123", true);
        map.put("/$23", true);
        map.put("/..", false);
        map.put("/../", false);
        map.put("/test1/", true);
        map.put("", true);
        map.put("/test1/file", true);
        map.put("/..//file", false);
        map.put("/test1//file", false);

        return map;
    }

    public LinkedHashMap<String,Boolean> testUrlQuery() {
        LinkedHashMap<String, Boolean> map = new LinkedHashMap<>();
        map.put("?action=view", true);
        map.put("?action=edit&mode=up", true);
        map.put("",true);

        return map;
    }
   


}
