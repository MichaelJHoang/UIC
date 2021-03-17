import org.junit.Test;

import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

public class testCases
{
    ArrayList<queryResultContainer> queryList;
    CareTaker careTaker;
    String usernameInput = null;
    String repoInput = null;

    // tests whether or not the variables are actually null
    @Test
    public void nullTest ()
    {
        assert (queryList == null);
        assert (careTaker == null);
        assert (usernameInput == null);
        assert  (repoInput == null);
    }

    // tests storing a single query
    @Test
    public void requestAndStoreTest () throws UnsupportedEncodingException
    {
        queryList = new ArrayList<>();
        URL url = null;
        HttpURLConnection connection = null;

        try
        {
            url = new URL("https://api.github.com/graphql");
            connection = (HttpURLConnection) url.openConnection();

            connection.setRequestProperty("Authorization", "Bearer 2afd2aa2b7f677b408c2d0e249c3ba1aba532898");
            connection.setRequestProperty("Accept", "application/json");
            connection.setRequestMethod("POST");
            connection.setDoOutput(true);

            String input =  "{ repository(owner: " + (usernameInput = "MichaelJHoang") + ", name: " + (repoInput = "UIC") + ") { id name collaborators(first: 100, affiliation: ALL) { edges { permission node { id login name } } } object(expression: master) {... on Commit { history { totalCount } } } } }";
            String gqlReq = new String("{\"query\":\"" + input + "\"}");

            byte[] databytes = gqlReq.getBytes("UTF-8");

            queryList.add(main_driver.getOutputStream(connection, databytes));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        assert (queryList.size() == 1);
    }

    // tests the capability of the caretaker to handle large loads
    @Test
    public void careTaker_stressTest ()
    {
        careTaker = new CareTaker();

        for (int x = 1; x <= 12345; x++)
        {
            careTaker.add((new savedInput("Hello", "world")).saveInputToMemento());
            assert (careTaker.mementoSize() == x);
        }
    }

    // tests the querylist's capability of handling large loads
    @Test
    public void requestAndStore_stressTest ()
    {
        queryList = new ArrayList<>();
        for (int x = 0; x < 100; x++) {
            URL url = null;
            HttpURLConnection connection = null;

            try {
                url = new URL("https://api.github.com/graphql");
                connection = (HttpURLConnection) url.openConnection();

                connection.setRequestProperty("Authorization", "Bearer 2afd2aa2b7f677b408c2d0e249c3ba1aba532898");
                connection.setRequestProperty("Accept", "application/json");
                connection.setRequestMethod("POST");
                connection.setDoOutput(true);

                String input = "{ repository(owner: " + (usernameInput = "MichaelJHoang") + ", name: " + (repoInput = "UIC") + ") { id name collaborators(first: 100, affiliation: ALL) { edges { permission node { id login name } } } object(expression: master) {... on Commit { history { totalCount } } } } }";
                String gqlReq = new String("{\"query\":\"" + input + "\"}");

                byte[] databytes = gqlReq.getBytes("UTF-8");

                queryList.add(main_driver.getOutputStream(connection, databytes));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        assert (queryList.size() == 100);
    }

    // tests an enormous amount of loads - making 250 requests and storing them all
    @Test
    public void requestAndStore_SUPER_STRESS_TEST ()
    {
        queryList = new ArrayList<>();
        for (int x = 0; x < 250; x++) {
            URL url = null;
            HttpURLConnection connection = null;

            try {
                url = new URL("https://api.github.com/graphql");
                connection = (HttpURLConnection) url.openConnection();

                connection.setRequestProperty("Authorization", "Bearer 2afd2aa2b7f677b408c2d0e249c3ba1aba532898");
                connection.setRequestProperty("Accept", "application/json");
                connection.setRequestMethod("POST");
                connection.setDoOutput(true);

                String input = "{ repository(owner: " + (usernameInput = "MichaelJHoang") + ", name: " + (repoInput = "UIC") + ") { id name collaborators(first: 100, affiliation: ALL) { edges { permission node { id login name } } } object(expression: master) {... on Commit { history { totalCount } } } } }";
                String gqlReq = new String("{\"query\":\"" + input + "\"}");

                byte[] databytes = gqlReq.getBytes("UTF-8");

                queryList.add(main_driver.getOutputStream(connection, databytes));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        assert (queryList.size() == 250);
    }
}