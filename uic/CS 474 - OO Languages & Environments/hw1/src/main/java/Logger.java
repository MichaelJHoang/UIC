import java.util.logging.*;

// logger class
class myLogger
{
    private static Logger logger = Logger.getLogger(Logger.GLOBAL_LOGGER_NAME);

    myLogger()
    {
        this.testLog();
    }

    public void testLog()
    {
        logger.log(Level.INFO, "logger test");
    }
}