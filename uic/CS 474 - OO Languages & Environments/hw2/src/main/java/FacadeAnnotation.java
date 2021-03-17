import java.lang.annotation.*;

@Retention(RetentionPolicy.RUNTIME)
@Target({ElementType.CONSTRUCTOR,
        ElementType.ANNOTATION_TYPE,
        ElementType.METHOD,
        ElementType.TYPE})
public @interface FacadeAnnotation
{
    String name();
    boolean clientAccessible();
}
