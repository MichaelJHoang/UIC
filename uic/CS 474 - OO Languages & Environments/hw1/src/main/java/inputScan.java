import java.util.*;

// singleton design pattern to make sure there is only one instance of the scanner
public final class inputScan
{
    private static inputScan singleton = null;

    private Scanner scanner;

    private inputScan()
    {
        scanner = new Scanner (System.in);
    }

    public static inputScan getInstance()
    {
        return singleton = new inputScan();
    }

    public int nextInt()
    {
        return scanner.nextInt();
    }

    public String nextLine()
    {
        return scanner.nextLine();
    }
}