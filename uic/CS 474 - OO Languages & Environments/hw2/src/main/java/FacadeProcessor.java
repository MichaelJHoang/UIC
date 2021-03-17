import java.lang.reflect.Field;
import java.util.Set;
import java.util.logging.LogManager;
import java.util.logging.Logger;
import javax.annotation.processing.AbstractProcessor;
import javax.annotation.processing.Messager;
import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.RoundEnvironment;
import javax.annotation.processing.SupportedAnnotationTypes;
import javax.annotation.processing.SupportedSourceVersion;
import javax.lang.model.SourceVersion;
import javax.lang.model.element.Element;
import javax.lang.model.element.ElementKind;
import javax.lang.model.element.ExecutableElement;
import javax.lang.model.element.Modifier;
import javax.lang.model.element.TypeElement;
import javax.tools.Diagnostic;

@SupportedAnnotationTypes({"annotation.FacadeAnnotation"})
@SupportedSourceVersion(SourceVersion.RELEASE_8)
public class FacadeProcessor extends AbstractProcessor
{
    // logger
    myLogger MYLOGGER = new myLogger();
    static LogManager logManager = LogManager.getLogManager();
    static Logger log = logManager.getLogger(Logger.GLOBAL_LOGGER_NAME);
    private Messager messager;

    private void printError (Element element, String message)
    {
        messager.printMessage(Diagnostic.Kind.ERROR, message, element);
    }

    private void checkMethod(ExecutableElement method)
    {
        // check for valid name
        String name = method.getSimpleName().toString();

        if (!name.toLowerCase().startsWith("facade"))
        {
            printError(method, "Annotation is not FacadeAnnotation (it's case sensitive, btw)");
        }
    }

    @Override
    public boolean process(Set<? extends TypeElement> annotations, RoundEnvironment roundEnv)
    {
        log.info("Processing annotations...");

        // get all the elements annotated with @FacadeAnnotation annotation
        Set<? extends Element> annotatedElements = roundEnv.getElementsAnnotatedWith(FacadeAnnotation.class);

        log.info("Going through annotated elements...");
        for (Element element: annotatedElements)
        {
            // only handle methods as targets
            checkMethod((ExecutableElement) element);

            // ensure that the client is the client
            for (Field f : Client.class.getFields())
            {
                FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

                if (facadeAnnotation != null)
                {
                    // check if the annotation is tagged to a facade
                    if (facadeAnnotation.name().toLowerCase().startsWith("facade") && facadeAnnotation.clientAccessible() == true)
                    {
                        continue;
                    }
                    // print error provided that it is not
                    else
                    {
                        log.severe("CLIENT IS NOT CLIENT???");
                        printError(element, "ANNOTATED CLASS NOT A FACADE");
                    }
                }
            }

            // for each annotated field within the class, make sure that all but the facade are accessed by the client
            for (Field f : CoordinateFacade.class.getFields())
            {
                FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

                if (facadeAnnotation != null)
                {
                    // check if the annotation is tagged to a facade
                    if (facadeAnnotation.name().toLowerCase().startsWith("facade") && facadeAnnotation.clientAccessible() == true)
                    {
                        continue;
                    }
                    // print error provided that it is not
                    else
                    {
                        log.severe("ANNOTATED CLASS NOT A FACADE - BREAKING DESIGN PATTERN RULES");
                        printError(element, "ANNOTATED CLASS NOT A FACADE");
                    }
                }
            }

            // for each annotated field within the class, make sure that all but the facade are accessed by the client
            for (Field f : ShapeFacade.class.getFields())
            {
                FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

                if (facadeAnnotation != null)
                {
                    // check if the annotation is tagged to a facade
                    if (facadeAnnotation.name().toLowerCase().startsWith("facade") && facadeAnnotation.clientAccessible() == true)
                    {
                        continue;
                    }
                    // print error provided that it is not
                    else
                    {
                        log.severe("ANNOTATED CLASS NOT A FACADE - BREAKING DESIGN PATTERN RULES");
                        printError(element, "ANNOTATED CLASS NOT A FACADE");
                    }
                }
            }

            // for each annotated field within the class, make sure that all but the facade are accessed by the client
            for (Field f : MediaFacade.class.getFields())
            {
                FacadeAnnotation facadeAnnotation = f.getAnnotation(FacadeAnnotation.class);

                if (facadeAnnotation != null)
                {
                    // check if the annotation is tagged to a facade
                    if (facadeAnnotation.name().toLowerCase().startsWith("facade") && facadeAnnotation.clientAccessible() == true)
                    {
                        continue;
                    }
                    // print error provided that it is not
                    else
                    {
                        log.severe("ANNOTATED CLASS NOT A FACADE - BREAKING DESIGN PATTERN RULES");
                        printError(element, "ANNOTATED CLASS NOT A FACADE");
                    }
                }
            }

        }

        // don't claim annotations to allow other processors to process them
        return false;
    }

    @Override
    public void init (ProcessingEnvironment processingEnvironment)
    {
        super.init(processingEnv);

        // get the messager for printing errors
        messager = processingEnvironment.getMessager();
    }
}