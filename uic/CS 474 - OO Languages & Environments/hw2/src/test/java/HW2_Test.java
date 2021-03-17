
import org.junit.Test;

import java.lang.reflect.Field;
import java.util.ArrayList;

public class HW2_Test
{
    Client client = null;
    CoordinateFacade coordinateFacade = null;
    ShapeFacade shapeFacade = null;
    MediaFacade mediaFacade = null;

    // tests whether or not they are actually null
    @Test
    public void objectNullTest()
    {
        assert (client == null);
        assert (coordinateFacade == null);
        assert  (shapeFacade == null);
        assert  (mediaFacade == null);
    }

    @Test
    public void instanceEquivalencyTest()
    {
        client = new Client();
        coordinateFacade = new CoordinateFacade();
        shapeFacade = new ShapeFacade();
        mediaFacade = new MediaFacade();

        assert(client instanceof Client);
        assert (coordinateFacade instanceof  CoordinateFacade);
        assert (shapeFacade instanceof ShapeFacade);
        assert (mediaFacade instanceof MediaFacade);
    }

    // tests the annotations within this test document
    @Test
    @FacadeAnnotation(name = "test", clientAccessible = false)
    public void HW2_Test_annotationTest()
    {
        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : MediaFacade.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            assert (facadeAnnotation.name().equalsIgnoreCase("test"));
            assert (facadeAnnotation.clientAccessible() == false);
        }
    }

    // tests to see whether or not the annotations throughout this program are null
    @Test
    public void nonNullAnnotations()
    {
        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : Client.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            assert(f != null);
        }

        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : CoordinateFacade.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            assert(f != null);
        }

        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : ShapeFacade.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            assert(f != null);
        }

        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : MediaFacade.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            assert(f != null);
        }
    }

    // tests putting the annotations in a container and making sure they're there
    @Test
    public void annotationStressStore()
    {
        ArrayList<FacadeAnnotation> annotations = new ArrayList<>();

        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : Client.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            annotations.add(facadeAnnotation);
        }

        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : CoordinateFacade.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            annotations.add(facadeAnnotation);
        }

        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : ShapeFacade.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            annotations.add(facadeAnnotation);
        }

        // for each annotated field within the class, make sure that all but the facade are accessed by the client
        for (Field f : MediaFacade.class.getFields())
        {
            FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

            annotations.add(facadeAnnotation);
        }

        for (FacadeAnnotation FA : annotations)
        {
            assert(FA != null);
        }
    }
}
