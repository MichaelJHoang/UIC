// class that encapsulates the user's saved input
// an actor in the Memento design pattern
public class savedInput
{
    String usernameInput;
    String repoInput;

    public savedInput(String usernameInput, String repoInput)
    {
        this.usernameInput = usernameInput;
        this.repoInput = repoInput;
    }

    // setters and getters
    public void setUsernameInput(String string)
    {
        usernameInput = string;
    }

    public void setRepoInput(String string)
    {
        repoInput = string;
    }

    public Memento saveInputToMemento()
    {
        return new Memento(this);
    }

    public void getSaveFromMemento(Memento memento)
    {
        this.usernameInput = memento.getState().usernameInput;
        this.repoInput = memento.getState().repoInput;
    }
}