import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import java.util.*;

// class that encapsulates the results of the queries made by the user
public class queryResultContainer
{
    // inner class that encapsulates all the
    private class collaborator
    {
        JsonArray collabArray;
        String id = null;
        String login = null;
        String name = null;
        String permission = null;

        // these constructors are private to enforce the idea that outsiders cannot construct this object.
        // only queryResultContainer can make instances of collaborators
        private collaborator(JsonArray collabArray)
        {
            this.collabArray = collabArray;
        }

        // helper constructor for the getCollabMap
        private collaborator(String id, String login, String name, String permission)
        {
            this.id = id;
            this.login = login;
            this.name = name;
            this.permission = permission;
        }

        // given a jsonarray from the constructor, construct a list of all the collaborators in a given repo
        // by extracting info from the jsonarray
        protected ArrayList<collaborator> getCollabList()
        {
            ArrayList<collaborator> tempList = new ArrayList<>();

            for (int x = 0; x < collabArray.size(); x++)
            {
                String tempId = null, tempLogin = null, tempName = null, tempPermit = null;

                tempId = collabArray.get(x).getAsJsonObject().get("node").getAsJsonObject().get("id").getAsString();
                tempLogin = collabArray.get(x).getAsJsonObject().get("node").getAsJsonObject().get("login").getAsString();
                tempName =  collabArray.get(x).getAsJsonObject().get("node").getAsJsonObject().get("name").toString();
                tempPermit = collabArray.get(x).getAsJsonObject().get("permission").getAsString();

                // make a call to the helper constructor
                tempList.add(new collaborator(tempId, tempLogin, tempName, tempPermit));
            }

            return tempList;
        }
    }

    // basic definitions that compose a query
    private JsonObject jsonObject;
    private String repoId = null;
    private String repoName = null;
    private int commitCount = 0;
    private ArrayList<collaborator> collabList = null;

    // constructor
    queryResultContainer(JsonObject jsonObject)
    {
        this.jsonObject = jsonObject;
        this.repoId = jsonObject.get("data").getAsJsonObject().get("repository").getAsJsonObject().get("id").getAsString();
        this.repoName = jsonObject.get("data").getAsJsonObject().get("repository").getAsJsonObject().get("name").getAsString();
        this.commitCount = jsonObject.get("data").getAsJsonObject().get("repository").getAsJsonObject().get("object").getAsJsonObject().get("history").getAsJsonObject().get("totalCount").getAsInt();

        // try/catch block that extracts the collaborators
        try
        {
            collabList = (new collaborator(jsonObject.get("data").getAsJsonObject()
                    .get("repository").getAsJsonObject()
                    .get("collaborators").getAsJsonObject()
                    .get("edges").getAsJsonArray()))
                    .getCollabList();
        }
        catch (Exception e)
        {

        }

    }

    // basic getters
    public JsonObject getJsonObject()
    {
        return jsonObject;
    }

    public String getRepoName ()
    {
        return repoName;
    }

    public String getRepoId ()
    {
        return repoId;
    }

    public int getCommitCount()
    {
        return commitCount;
    }

    public ArrayList<collaborator> getCollabList()
    {
        return collabList;
    }

    // debugging function to test whether or not the list of collaborators will actually get printed
    public void printCollabList()
    {
        if (collabList != null)
            for (int x = 0; x < collabList.size(); x++)
            {
                System.out.println(collabList.get(x).login + " - " + collabList.get(x).permission);
            }
        else
            System.out.println("No collaborators.");


        return;
    }

    // printed as the result of the user's input.
    // running this function successfully means that the query object was successfully created
    public void printQuery ()
    {
        System.out.println("\nRepository: " + this.repoName +
                           "\nRepository ID: " + this.repoId +
                           "\nOwner: " + (collabList == null ? "No specified owner (name likely not set or null)" : collabList.get(0).name) +
                           "\nNumber of commits made to this repository: " + this.commitCount);

        System.out.println("\nCollaborators: ");
        this.printCollabList();
    }
}