// an actor in the Memento design pattern that allows the user's saved inputs
// to be saved
public class Memento
{
    private savedInput state;

    public Memento (savedInput state)
    {
        this.state = state;
    }

    public savedInput getState()
    {
        return state;
    }
}
