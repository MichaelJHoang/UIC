import java.util.ArrayList;

// caretaker class, which is an actor in the memento design pattern
// manages the mementos
public class CareTaker
{
    private ArrayList<Memento> mementoList = new ArrayList<Memento>();

    public void add(Memento state)
    {
        mementoList.add(state);
    }

    public Memento get(int index)
    {
        if (!mementoList.isEmpty())
            return mementoList.get(index);
        return null;
    }

    public int mementoSize ()
    {
        return mementoList.size();
    }
}
