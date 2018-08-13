

import junit.framework.Assert;
import junit.framework.TestCase;
import org.junit.Test;

import java.util.*;

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

    @Test
   public void testIsValidRandomDefault() {
        UrlValidator url = new UrlValidator();

        int numTests = 10000;
        int i = 0;
        int inconsistency = 0;
        LinkedHashMap<String, Boolean> urls = new LinkedHashMap<>();
        Random rand = new Random();

        while (i < numTests) {
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

            urls.put(urlString, expected);
            i++;
        }

        LinkedHashMap<String, Boolean> passes = new LinkedHashMap<>();
        LinkedHashMap<String, Boolean> fails = new LinkedHashMap<>();

        System.out.println("Testing urls using default url validator...");
        for (Map.Entry<String, Boolean> entry : urls.entrySet()) {
            try {
                assertEquals(entry.getValue().booleanValue(), url.isValid(entry.getKey()));
                passes.put(entry.getKey(), entry.getValue());
            } catch (Error e) {
                fails.put(entry.getKey(), entry.getValue());
            }
        }

        System.out.println("Passing urls:");
        for (Map.Entry<String, Boolean> entry : passes.entrySet()) {
            System.out.println(entry.getKey() + " --> " + entry.getValue());
        }

        System.out.println("");
        System.out.println("Failing urls:");
        for (Map.Entry<String, Boolean> entry : fails.entrySet()) {
            System.out.println(entry.getKey() + " --> " + entry.getValue());
        }

        System.out.println("");
        System.out.println("Inconsistencies:");
        for (Map.Entry<String, Boolean> entry : passes.entrySet()) {
            if (!entry.getValue()) {
                System.out.println(entry.getKey() + " --> " + entry.getValue());
                inconsistency++;
            }
        }
        for (Map.Entry<String, Boolean> entry : fails.entrySet()) {
            if (entry.getValue()) {
                System.out.println(entry.getKey() + " --> " + entry.getValue());
                inconsistency++;
            }
        }

        System.out.println("");
        System.out.println("There were " + inconsistency + " wrong validations of " + numTests + "!");
    }

    @Test
    public void testIsValidRandomAllowAllSchemes() {
        UrlValidator urlAllowAll = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        int numTests = 10000;
        int i = 0;
        int inconsistency = 0;
        LinkedHashMap<String, Boolean> urls = new LinkedHashMap<>();
        Random rand = new Random();

        while (i < numTests) {
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

            urls.put(urlString, expected);
            i++;
        }

        LinkedHashMap<String, Boolean> passes = new LinkedHashMap<>();
        LinkedHashMap<String, Boolean> fails = new LinkedHashMap<>();

       System.out.println("Testing urls using url validator that allows all schemes...");
       for(Map.Entry<String, Boolean> entry : urls.entrySet()){
           try{
               assertEquals(entry.getValue().booleanValue(),urlAllowAll.isValid(entry.getKey()));
               passes.put(entry.getKey(),entry.getValue());
           }catch(Error e){
               fails.put(entry.getKey(),entry.getValue());
           }
       }

       System.out.println("Passing urls:");
       for(Map.Entry<String, Boolean> entry : passes.entrySet()){
           System.out.println(entry.getKey()+ " --> " + entry.getValue());
       }

       System.out.println("");
       System.out.println("Failing urls:");
       for(Map.Entry<String, Boolean> entry : fails.entrySet()){
           System.out.println(entry.getKey()+ " --> " + entry.getValue());
       }

       System.out.println("");
       System.out.println("Inconsistencies:");
       for(Map.Entry<String, Boolean> entry : passes.entrySet()){
           if(!entry.getValue()){
               System.out.println(entry.getKey()+ " --> " + entry.getValue());
               inconsistency++;
           }
       }
       for(Map.Entry<String, Boolean> entry : fails.entrySet()){
           if(entry.getValue()){
               System.out.println(entry.getKey()+ " --> " + entry.getValue());
               inconsistency++;
           }
       }

       System.out.println("");
       System.out.println("There were " + inconsistency + " wrong validations of " + numTests + "!");

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
