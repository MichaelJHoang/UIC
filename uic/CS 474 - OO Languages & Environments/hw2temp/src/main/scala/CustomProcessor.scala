import java.util

import javax.annotation.processing.{AbstractProcessor, RoundEnvironment}
import javax.lang.model.element.TypeElement

class CustomProcessor extends AbstractProcessor
{
    override def process(annotations: util.Set[_ <: TypeElement], roundEnv: RoundEnvironment): Boolean = ???
}
