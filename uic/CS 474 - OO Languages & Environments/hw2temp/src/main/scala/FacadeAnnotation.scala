import scala.annotation.StaticAnnotation

class FacadeAnnotation extends StaticAnnotation
{
    def macroTransform(annottees : Any*) : Any = macro ???
}

